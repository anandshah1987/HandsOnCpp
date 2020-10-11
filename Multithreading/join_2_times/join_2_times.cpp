// join_2_times.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>

void TestFunc()
{
	std::cout << "I am in TestFunc()" << std::endl;
	throw std::exception("I am dying....");
}

int main()
{
	std::thread th(TestFunc);
	th.join();
	std::cout << "I am after join .." << std::endl;
	//std::this_thread::sleep_for(std::chrono::minutes(1));
	//th.detach();
	
	/*try
	{
		th.join();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}*/

	/*std::thread th1;
	try
	{
		th1.join();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}*/
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
