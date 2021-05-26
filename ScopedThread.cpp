#include <iostream>
#include <thread>
#include <chrono>
#include "ScopedThread.h"

void func()
{
    std::cout << std::this_thread::get_id() << ": calling func()" << std::endl;
}

int main()
{
    std::thread t(func);
    // if (t.joinable())
    //     t.join();

    ScopedThread st(std::move(t));
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
