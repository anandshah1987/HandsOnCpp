// ReturnErrorIfThreadIsRunning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
//#include <synchapi.h>
#include <Windows.h>


void ThreadFunction(std::atomic_bool& isPrevOperationRunning)
{
    std::cout << "I am starting to execute time consuming operation" << '\n';

    std::this_thread::sleep_for(std::chrono::seconds(3));

    isPrevOperationRunning = false;
    std::cout << "I am finished executing time consuming operation" << '\n';
}

void MyFunction(int operationCount)
{
    static std::atomic_bool isPrevOperationRunning = false;

    if (isPrevOperationRunning)
    {
        std::cout << "Previous operation still not finished. Not executing operation no " << operationCount << '\n';
        return;
    }

    isPrevOperationRunning = true;
    std::thread thread(ThreadFunction, std::ref(isPrevOperationRunning));
    if (thread.joinable())
    {
        thread.detach();
    }
}

int main()
{
    int count = 0;
    MyFunction(++count);
    MyFunction(++count);
    MyFunction(++count);

    Sleep(5000);
    MyFunction(++count);

    while (1) {};
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
