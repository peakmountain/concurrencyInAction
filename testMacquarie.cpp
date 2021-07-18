#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

template <typename T>
void printData(const std::vector<T>& data)
{
    copy(data.begin(), data.end(),
            std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

void GetUniqueResult(std::vector<std::vector<int>>& coll, int maxDaily, int sumHours, int dimention)
{
    for (int i = 0; i < dimention; i++)
    {
        for (

    }

}

void GetCombination(std::vector<std::vector<int>>& coll, int maxDaily, int sumHours, int dimention)
{
    GetUniqueResult(coll, maxDaily, sumHours, dimention);

    std::cout << "calling GetCombination" << std::endl;
    while (std::next_permutation(candidate.begin(), candidate.end()))
    {
        std::cout << "In while loop" << std::endl;
        printData(candidate);
        coll.push_back(candidate);
    }
}

int main()
{
    std::vector<std::vector<int>> combinations;

    GetCombination(combinations, 8, 4, 2);

}
