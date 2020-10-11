// C++17_Structured_Bindings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>

extern "C"
{
    void MyFunc()
    {
        std::cout << "I am in MyFunc()" << '\n';
    }

    void MyFunc(int i)
    {
        std::cout << "I am in MyFunc(int i)" << '\n';
    }
}

int main()
{
    std::map<int, std::string> emploeeMapping = { {1, "Anand"}, {2, "Ashwini"},
        {3, "Deepak"} };

    // Old way of iterating over map
    for (const auto& employee : emploeeMapping)
    {
        std::cout << "Employee id : " << employee.first << " Employee name : "
            << employee.second << "\n";
    }

    // New C++17 way of iterating over map [Structured binding]
    for (const auto& [employeeId, employeeName] : emploeeMapping)
    {
        std::cout << "Employee id : " << employeeId << " Employee name : "
            << employeeName << "\n";
    }

    std::cout << "Hello World!\n";
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
