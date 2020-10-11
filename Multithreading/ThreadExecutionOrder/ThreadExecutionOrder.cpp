// ThreadExecutionOrder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
//std::mutex oneMutex;
//std::mutex twoMutex;

std::condition_variable zeroConVar;
std::condition_variable oneConVar;
std::condition_variable twoConVar;


void PrintZero()
{
    int i = 5;
    while (i > 0)
    {
        std::cout << "0" << std::endl;
        oneConVar.notify_one();
        i--;
        std::unique_lock<std::mutex> lock(mutex);
        zeroConVar.wait(lock);
    }
}

void PrintOne()
{
    int i = 5;
    while (i > 0)
    {
        std::unique_lock<std::mutex> lock(mutex);
        oneConVar.wait(lock);
        std::cout << "1" << std::endl;
        twoConVar.notify_one();
        i--;
    }
}

void PrintTwo()
{
    int i = 5;
    while (i > 0)
    {
        std::unique_lock<std::mutex> lock(mutex);
        twoConVar.wait(lock);
        std::cout << "2" << std::endl;
        zeroConVar.notify_one();
        i--;
    }
}

int main()
{
    std::cout << "Hello World!\n";
    std::thread zeroThread(PrintZero);
    std::thread oneThread(PrintOne);
    std::thread twoThread(PrintTwo);
    //zeroConVar.notify_one();
    zeroThread.join();
    oneThread.join();
    twoThread.join();
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
