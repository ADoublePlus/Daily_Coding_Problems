/*
    This problem was recently asked by Google.
    Given a list of numbers and a number k,
        return whether any two numbers from the list add up to k.

    For example,
        given [10, 15, 3, 7] and k = 17,
        return true,
        since 10 + 7 = 17.

    Bonus: Can you do this in one pass?
 */

#include "stdc++.h"

#include <unordered_set>

using namespace std;

bool twoSum(const vector<int>& nums, int target)
{
    unordered_set<int> comps;

    for (int num : nums)
    {
        if (comps.find(num) != comps.end())
            return true;

        comps.insert(target - num);
    }

    return false;
}

int main()
{
    vector<int> nums{2, 7, 5, 11, -7, 6, -131};
    int target = 1;

    cout << twoSum(nums, target);
}