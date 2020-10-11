// ACM_ICPC_Team.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <utility>

std::vector<int> acmTeam(std::vector<std::string> topic)
{
    std::vector<std::pair<int, int>> result;
    int maxSum = 0;
    for (int counter=0; counter< (topic.size()-1); counter++)
    {
        int topicSum = 0;
        for (int j=counter+1; j<topic.size();j++)
        {
            auto subjects1 = topic[counter];
            auto subjects2 = topic[j];
            for(int i=0; i< subjects1.size(); i++)
            {
                auto char1 = subjects1[i];
                auto char2 = subjects2[i];
                if (('0'-char1) || ('0'-char2))
                {
                    topicSum++;
                }
            }
            if (topicSum>= maxSum)
            {
                if (topicSum>maxSum)
                {
                    result.clear();
                }
                result.emplace_back(counter+1, j+1);
                maxSum = topicSum;
            }
            topicSum = 0;
        }
    }

    std::vector<int> resultSet{ maxSum, static_cast<int>(result.size())};
    return resultSet;
}


int main()
{
    auto result = acmTeam({"10101","11100","11010","00101"});
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
