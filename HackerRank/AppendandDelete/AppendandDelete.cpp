// AppendandDelete.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>


std::string appendAndDelete(std::string s, std::string t, int k)
{
    int origStrLen = s.length();
    int desiredStrLen = t.length();

    if ((std::abs(origStrLen- desiredStrLen)) > k)
    {
        return "No";
    }

    auto loopLimit = std::min(origStrLen, desiredStrLen);

    int index = 0;
    for (; index<loopLimit; index++)
    {
        if (s[index] != t[index])
        {
            break;
        }
    }

    int misMatchIndexOrigStr = origStrLen - index;
    int misMatchIndexDesiredStr = desiredStrLen - index;
    if (origStrLen>=desiredStrLen)
    {
        if ((misMatchIndexOrigStr + misMatchIndexDesiredStr) > k)
        {
            return "No";
        }
        return "Yes";
    }
    else
    {
        if (0==index)
        {
            if ((origStrLen+ desiredStrLen) <= k)
            {
                return "Yes";
            }
            return "No";
        }
        else if ((misMatchIndexOrigStr+ misMatchIndexDesiredStr)==k)
        {
            return "Yes";
        }
        return "No";
    }

}

int main()
{
    auto str = appendAndDelete("Y","YU",2);
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
