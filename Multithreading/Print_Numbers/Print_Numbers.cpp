// Print_Numbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <condition_variable>
#include <thread>
//
//Problem statement :- Print series 010203040506 .... where 1st thread prints zero, 2nd thread will print 
//ony odd numbers and 3rd thread will print even numbers ..

static int counter = 0;

std::mutex nuumLock;
std::condition_variable printEven;
std::condition_variable printOdd;
std::condition_variable printZeros;
bool isNoPrinted = false;

void PrintZeros()
{
	std::cout << 0;
}
void PrintEven()
{
	int lastCountVal = 0;
	while (counter < 10)
	{
		std::unique_lock<std::mutex> lock(nuumLock);
		printEven.wait(lock, [lastCountVal] {return ((counter > 0) && (counter % 2 == 0) && (counter > lastCountVal)); });
		std::cout << counter;
		lastCountVal = counter;
		isNoPrinted = true;
		printZeros.notify_one();
	}
	return;
}
void PrintOdd()
{
	int lastCountVal = 0;
	while (counter < 9)
	{
		std::unique_lock<std::mutex> lock(nuumLock);
		printOdd.wait(lock, [lastCountVal] {return ((counter > 0) && (counter % 2 == 1) && (counter > lastCountVal)); });
		std::cout << counter;
		lastCountVal = counter;
		isNoPrinted = true;
		printZeros.notify_one();
	}
	return;
}

int main()
{
	std::thread evenNumberThread(PrintEven);
	std::thread oddNumberThread(PrintOdd);
	while (counter < 10)
	{
		{
			std::unique_lock<std::mutex> lock(nuumLock);
			isNoPrinted = false;
			std::cout << 0;
			counter++;
			if (counter % 2 == 0)
			{
				printEven.notify_one();
			}
			else
			{
				printOdd.notify_one();
			}
		}
		{
			std::unique_lock<std::mutex> lock(nuumLock);
			printZeros.wait(lock, [] {return isNoPrinted; });
		}
	}
	if(evenNumberThread.joinable())
		evenNumberThread.join();
	if (oddNumberThread.joinable())
		oddNumberThread.join();
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
