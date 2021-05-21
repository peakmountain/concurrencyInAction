#include <iostream>
#include <thread>
#include <chrono>

class ThreadGuard
{
    public:
        ThreadGuard(std::thread& p) : _p(p)
        {}
        ~ThreadGuard()
        {
            if (_p.joinable())
            {
                std::cout << std::this_thread::get_id() << ": waiting for the thread." << std::endl;
                _p.join();
            }
        }
        ThreadGuard(ThreadGuard const&) = delete;
        ThreadGuard& operator=(ThreadGuard const&) = delete;
    private:
        std::thread& _p;
};

void func()
{
    std::cout << std::this_thread::get_id() << ": invoking func()" << std::endl;
}

int main()
{
    std::thread t(func);
    ThreadGuard guard(t);
    // t.join();

    std::this_thread::sleep_for(std::chrono::seconds(2));
}
