#include "ThreadSafeQueue.h"

int main()
{
    ThreadSafeQueue<int> coll;

    for (int i = 0; i < 9; i++)
    {
        int data = (i + 1) * 11;
        coll.push(data);
    }

    for (int i = 0; i < 9; i++)
    {
        if (i != 0 )
        {
            std::cout << ", ";
        }
        std::cout << *coll.pop();
    }
    std::cout << std::endl;
}
