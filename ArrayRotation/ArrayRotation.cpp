// ArrayRotation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
// Sample code to perform I/O:

#include <iostream>

using namespace std;

int main() {
	int num;
	cin >> num;										// Reading input from STDIN
	cout << "Input number is " << num << endl;		// Writing output to STDOUT
}

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <iostream>
#include <vector>
#include <algorithm>


std::vector<int> Operation(int arraySize, int noOfRotations)
{
	std::vector<int> data{};
	data.reserve(arraySize);
	for (int count = 0; count < arraySize; count++)
	{
		int arrayMember{};
		std::cin >> arrayMember;
		data.emplace_back(arrayMember);
	}

	auto actualRotations = noOfRotations % data.size();
	if (0 == actualRotations)
	{
		return data;
	}

	std::reverse(data.begin(), data.end());

	std::reverse(data.begin(), data.begin() + actualRotations);
	std::reverse(data.begin() + actualRotations, data.end());
	return data;
}

int main()
{
	int num = 0;
	std::cin >> num;

	for (int i = 0; i < num; i++)
	{
		int arraySize = 0;
		std::cin >> arraySize;
		int numOfRotation = 0;
		std::cin >> numOfRotation;
		auto result = Operation(arraySize, numOfRotation);
		std::for_each(result.cbegin(), result.cend(), [](int value)->void {std::cout << value << " "; });
		std::cout << '\n';
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
