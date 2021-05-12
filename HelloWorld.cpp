#include <iostream>
#include <thread>

void func()
{
    std::cout << std::this_thread::get_id << ": Hello Concurrent World!" << std::endl;
}

int main(void)
{
    std::thread th(func);
    th.join();

    return 0;
}
