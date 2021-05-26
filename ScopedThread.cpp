#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>

void func()
{
    std::cout << std::this_thread::get_id() << ": calling func()" << std::endl;
}

class ScopedThread
{
    public:
        ScopedThread(std::thread t) : _t(std::move(t))
        {
            if (!_t.joinable())
            {
                assert(false);
            }
        }
        ~ScopedThread()
        {
            std::cout << std::this_thread::get_id() << ": waiting for _t to finish." << std::endl;
            _t.join();
        }
        ScopedThread(ScopedThread const&) = delete;
        ScopedThread& operator=(ScopedThread const&) = delete;
    private:
        std::thread _t;

};

int main()
{
    std::thread t(func);
    // if (t.joinable())
    //     t.join();

    ScopedThread st(std::move(t));
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
