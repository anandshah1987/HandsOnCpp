// Non-Divisible-Subset.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

//https://www.youtube.com/watch?v=3qPSBZFTnzQ&feature=youtu.be

int nonDivisibleSubset(int k, std::vector<int> s)
{
    std::vector<int> reminder;
    reminder.resize(k, 0);

    for (const auto& val : s)
    {
        reminder[val % k]++;
    }
    int zeroRemainder = reminder[0];
    int maxNumberOfDivisibleSet = zeroRemainder > 0 ? 1 : 0;
    for (int i = 1; i <= (k / 2); i++) 
    {
        if (i != k - i)
            maxNumberOfDivisibleSet += std::max(reminder[i], reminder[k - i]);
        else
            maxNumberOfDivisibleSet++;
    }

    return maxNumberOfDivisibleSet;

}

int main()
{
    //auto result = nonDivisibleSubset(7, { 278, 576, 496, 727, 410, 124, 338, 149, 209, 702, 282, 718, 771, 575, 436 });
    auto result = nonDivisibleSubset(3, { 1,7,2,4});
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
