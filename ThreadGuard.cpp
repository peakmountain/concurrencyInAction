#include <iostream>
#include <thread>

class ThreadGuard
{
    public:
        ThreadGuard(std::thread& p) : _p(p)
        {}
        ~ThreadGuard()
        {
            std::cout << std::this_thread::get_id() << ": waiting for the thread." << std::endl;
            _p.join();
        }
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
}
