// BUfferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>

void Function1();

std::mutex m1;

void Function2()
{
    std::cout << "I am entering Function2" << '\n';
    std::lock_guard<std::mutex> lock(m1);
    Function1();
}

void Function1()
{
    std::cout << "I am entering Function1" << '\n';
    std::lock_guard<std::mutex> lock(m1);
    while (1)
    {
        ;
    }
   // Function2();
    std::cout << "I am exiting Function1" << '\n';
}

using Address = char[10];

int main()
{
  /*  Address myAdress{};
    strcpy_s(myAdress, "Anand Deepak Shah, Flat No A1-402, Oxygen Valley, Pune");
    std::cout << "Hello World!\n";*/

    std::thread thread(Function1);
    std::thread thread1(Function2);
    std::cout << "I am exiting main" << '\n';
    if (thread.joinable())
    {
        thread.join();
    }
    if (thread1.joinable())
    {
        thread1.join();
    }
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
