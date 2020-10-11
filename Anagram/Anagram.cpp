// Anagram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>

int main()
{
    std::string str1{"abbcdd"};
    std::string str2{ "ddcabh" };

    std::map<char, int> charCount1;
    std::map<char, int> charCount2;;

    if (str1.size() != str2.size())
    {
        std::cout << "Not a anagram";
        return 0;
    }

    for (const auto& character : str1)
    {
        charCount1[character]++;
    }

    for (const auto& character : str2)
    {
        charCount2[character]++;
    }

    for (const auto& character : charCount1)
    {
        if (character.second != charCount2[character.first])
        {
            std::cout << "Not a anagram";
            return 0;
        }
    }

    std::cout << "Its a Anagram";

   return 0;
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
