#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ScopedThread.h"
#include <queue>
#include <stdlib.h>
// #include <time.h>

std::mutex mtx;
std::condition_variable cond;
std::queue<int> collection;

void producer()
{
    for (int i = 0; i < 100; i++)
    {
        std::lock_guard<std::mutex> guard(mtx);

        int data = rand() % 100;
        collection.push(data);
        std::cout << "Producer: enqueue " << data << std::endl;
        cond.notify_one();
    }
}

void consumer()
{
    int counter = 0;
    while(counter < 100)
    {
        std::unique_lock<std::mutex> ulock(mtx);

        cond.wait(ulock, [](){
                return !collection.empty();
        });

        int data = collection.front();
        collection.pop();

        ulock.unlock();
        std::cout << "****Consumer: process " << data << std::endl;
        counter++;
    }
}


int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    ScopedThread st1(std::move(t1));
    ScopedThread st2(std::move(t2));
}
