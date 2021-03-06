/*
    This problem was asked by Uber.
    Given an array of integers,
        return a new array such that each element at index i of the new array
        is the product of all the numbers in the original array except the one at i.

    For example,
        if our input was [1, 2, 3, 4, 5],
        the expected output would be [120, 60, 40, 30, 24].

        If our input was [3, 2, 1],
        the expected output would be [2, 3, 6].

    Follow-up: What if you can't use division?
 */

#include <cstddef>
#include <iostream>
#include <vector>

// O(n) = n^2 
auto multiply(const std::vector<int>&) -> std::vector<int>;
auto operator<<(std::ostream&, const std::vector<int>&) -> std::ostream&;

int main()
{
    std::vector<int> example1 = {1, 2, 3, 4, 5};
    std::vector<int> example2 = {3, 2, 1};

    auto modifiedExample1(multiply(example1));
    auto modifiedExample2(multiply(example2));

    std::cout << "base array: " << example1 << std::endl;
    std::cout << "modified: " << modifiedExample1 << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << "base array: " << example2 << std::endl;
    std::cout << "modified: " << modifiedExample2 << std::endl;

    return 0;
}

std::vector<int> multiply(const std::vector<int>& oldArray)
{
    std::vector<int> temp;
    int val(0);

    for (std::size_t i = 0; i < oldArray.size(); i++)
    {
        for (std::size_t j = 0; j < oldArray.size(); j++)
        {
            if (i == j)
                continue;

            if (j == 0)
            {
                val = oldArray.at(0);

                continue;
            }

            if (i == 0 && j == 1)
            {
                val = oldArray.at(1);

                continue;
            }
            
            val *= oldArray.at(j);
        }

        temp.push_back(val);
    }

    return temp;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
    for (const auto& entry : vec)
    {
        if (&entry == &vec.back())
        {
            os << entry << "]";

            break;
        }

        if (&entry == &vec.front())
        {
            os << "[";
        }

        os << entry << ", ";
    }
}