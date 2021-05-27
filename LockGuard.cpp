#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include "ScopedThread.h"
#include <mutex>

std::mutex data_mutex;

void printout(const std::vector<int>& data)
{
    std::for_each(data.begin(), data.end(), [](auto item){
            std::cout << item << "\t";
            });
    std::cout << std::endl;
}

void func1(std::vector<int>& data)
{
    std::lock_guard<std::mutex> lock(data_mutex);

    std::cout << "Thread " << std::this_thread::get_id() << ":" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        data.push_back(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    printout(data);
}

void func2(std::vector<int>& data)
{
    std::lock_guard<std::mutex> lock(data_mutex);

    std::cout << "Thread " << std::this_thread::get_id() << ":" << std::endl;
    for (int i = 100; i < 110; i++)
    {
        data.push_back(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    printout(data);
}

int main()
{
    std::vector<int> coll;
    std::thread t1(func1, std::ref(coll));
    std::thread t2(func2, std::ref(coll));

    ScopedThread st1(std::move(t1));
    ScopedThread st2(std::move(t2));

    std::cout << "MainThread " << std::this_thread::get_id() << ":" << std::endl;
    printout(coll);

    return 0;
}
