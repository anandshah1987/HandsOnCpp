// VariadicArgumentCompileTime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <string>

template <typename Type>
void doSomething(Type&& arg) /* noexcept */
{
    // Each argument available here.
    std::cout << arg << "\n";
}

template <typename ...Args>
void SampleFunc(std::string str, Args&&... args) /* noexcept */
{
    (std::cout << ... << args) << '\n';
    (doSomething(std::forward<Args>(args)), ...);
}

template<typename ...Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

int main()
{
    SampleFunc("Anand", 1,2,3);
    printer(1, 2, 3, "abc");
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
