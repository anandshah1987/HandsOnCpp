// PickingNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <vector>


int pickingNumbers(std::vector<int> a)
{
    int result[101]{};
    for (const int val : a)
    {
        result[val]++;
    }

    int maxResult = 1;
    for (int i=0; i<=100; i++)
    {
        auto sum = result[i] + result[i+1];
        if (sum > maxResult)
        {
            maxResult = sum;
        }
    }
    return maxResult;

    /*std::map<int, int> result;
    for (const int val : a)
    {
        result[val]++;
    }

    if (result.empty())
    {
        return 0;
    }
    else if(result.size() == 1)
    {
        return result.at(a[0]);
    }*/

   /* int prevKey = 0;
    int size = 0;
    int prevCount = 0;
    int maxSize = 0;
    int key = 0;
    for (const auto& data : result)
    {
        key = data.first;
        if ((key==prevKey)|| (key == (prevKey + 1)))
        {
            size = prevCount + data.second;
            if (size > maxSize)
            {
                maxSize = size;
            }
        }
        prevKey = key;
        prevCount = data.second;
    }
    return maxSize;*/
}

int main()
{
    auto val = pickingNumbers({ 4,97,5,97,97,4,97,4,97,97,97,97,4,4,5,5,97,5,97,99,4,97,5,97,97,97,5,5,97,4,5,97,97,5,97,4,97,5,4,4,97,5,5,5,4,97,97,4,97,5,4,4,97,97,97,5,5,97,4,97,97,5,4,97,97,4,97,97,97,5,4,4,97,4,4,97,5,97,97,97,97,4,97,5,97,5,4,97,4,5,97,97,5,97,5,97,5,97,97,97 });
    std::cout << "Hello World!\n";
    std::cout << val;
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
