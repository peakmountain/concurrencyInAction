#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> x, y;
std::atomic<int> z;

void write()
{
    x.store(true, std::memory_order_relaxed);
    x.store(false, std::memory_order_relaxed);
    x.store(true, std::memory_order_relaxed);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    y.store(true, std::memory_order_relaxed);
}

void read()
{
    while(!y.load(std::memory_order_relaxed));
    if (x.load(std::memory_order_relaxed))
        z++;
}

int main()
{
    x = false;
    y = false;
    z = 0;

    std::thread t1(write);
    std::thread t2(read);

    t1.join();
    t2.join();

    std::cout << "z = " << z << std::endl;
}
