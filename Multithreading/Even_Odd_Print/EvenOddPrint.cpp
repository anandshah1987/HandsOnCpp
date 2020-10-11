// EvenOddPrint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <tchar.h>

#define SEM_EVEN "EVEN_SEM"
#define SEM_ODD "SEM_ODD"

void PrintEvenNum()
{
	int counter = 2;
	auto evenSem = CreateSemaphore(nullptr, 0, 1, _T(SEM_EVEN));
	auto oddSem = CreateSemaphore(nullptr, 0, 1, _T(SEM_ODD));

	while (counter < 20)
	{
		WaitForSingleObject(evenSem, INFINITE);
		std::cout << "Even thread prints - " << counter << std::endl;
		counter += 2;
		ReleaseSemaphore(oddSem, 1, nullptr);
	}
}

int main()
{
    std::cout << "Hello World!\n"; 
	std::thread evenThread(PrintEvenNum);

	auto evenSem = CreateSemaphore(nullptr, 0, 1, _T(SEM_EVEN));
	auto oddSem = CreateSemaphore(nullptr, 0, 1, _T(SEM_ODD));
	ReleaseSemaphore(oddSem, 1, nullptr);

	int counter = 1;
	while (counter < 20)
	{
		WaitForSingleObject(oddSem, INFINITE);
		std::cout << "Odd thread prints - " << counter << std::endl;
		counter += 2;
		ReleaseSemaphore(evenSem, 1, nullptr);
	}

	if (evenThread.joinable())
	{
		evenThread.join();
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
