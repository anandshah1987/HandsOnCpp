// ClimbingTheLeaderboard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::vector<int> climbingLeaderboard(std::vector<int> ranked, std::vector<int> player)
{
    std::vector<int> result{};
    int preVal = 0;
    for (const auto val : ranked)
    {
        if (val != preVal)
        {
            result.push_back(val);
        }
        preVal = val;
    }

    std::vector<int> resultVector{};
    for (const auto val : player)
    {
        int index = 0;
        if (val >= result.at(0))
        {
            index = 1;
        }
        else
        {
            auto location = std::lower_bound(result.begin(), result.end(), val, std::greater<int>());
            if (result.end() == location)
            {
                index = result.size();
            }
            else
            {
                index = location- result.begin();
            }
            ++index;
        }
        resultVector.push_back(static_cast<int>(index));
    }
    
    return resultVector;
}


int main()
{
    auto result = climbingLeaderboard({100,90,90,80,75,60}, {50,65,77,90,102});
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
