#include <thread>
#include <mutex>
#include "Table.h"

int main()
{
    Table t1(1);
    Table t2(2);

    std::lock(t1.m, t2.m);
    std::lock_guard<std::mutex> guard1(t1.m, std::adopt_lock);
    std::lock_guard<std::mutex> guard2(t2.m, std::adopt_lock);

    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;

    return 0;
}
