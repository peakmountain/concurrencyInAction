#include <iostream>
#include <chrono>
#include <future>

int background_task()
{
    std::cout << "background_task: sleeping for 5 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        sum += i;
    }
    std::cout << "background_task: sum = " << sum << std::endl;

    return sum;
}

int main()
{
    std::future<int> result = std::async(background_task);

    std::cout << "main: sleeping for 2 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    std::cout << "main: result = " << result.get() << std::endl;
}
