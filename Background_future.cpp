#include <iostream>
#include <chrono>
#include <future>

int background_task()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "background_task: sleeping for 5 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        sum += i;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "background_task: sum = " << sum << std::endl;
    // std::cout << "background_task: it takes " << std::chrono::duration<double, std::chrono::seconds>(stop - start).count() << " seconds." << std::endl;
    std::cout << "background_task: it takes " << std::chrono::duration<double, std::ratio<1,1>>(stop - start).count() << " seconds." << std::endl;

    return sum;
}

int main()
{
    std::future<int> result = std::async(background_task);

    std::cout << "main: sleeping for 2 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int s = result.get();

    std::cout << "main: result = " << s << std::endl;
}
