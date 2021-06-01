#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex mtx;
bool completed = false;
std::condition_variable cond;
int sum = 0;

void background_task()
{
    std::cout << "background_task: sleeping for 5 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    for (int i = 0; i < 1000; i++)
    {
        sum += i;
    }
    std::cout << "background_task: sum = " << sum << std::endl;

    std::lock_guard<std::mutex> guard(mtx);
    completed = true;
    cond.notify_one();
}

int main()
{
    std::thread bg(background_task);
    bg.detach();

    std::unique_lock<std::mutex> lk(mtx);
    cond.wait(lk, []() {
            return completed;});

    std::cout << "main: sum = " << sum << std::endl;
}
