// Array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
int maxDiff(int arr[], int n)
{
	// Initialize diff, current sum and max sum 
	int diff = arr[1] - arr[0];
	int curr_sum = diff;
	int max_sum = curr_sum;

	for (int i = 1; i < n - 1; i++)
	{
		// Calculate current diff 
		diff = arr[i + 1] - arr[i];

		// Calculate current sum 
		if (curr_sum > 0)
			curr_sum += diff;
		else
			curr_sum = diff;

		// Update max sum, if needed 
		if (curr_sum > max_sum)
			max_sum = curr_sum;
	}

	return max_sum;
}

int main()
{
    std::cout << "Hello World!\n"; 
	int arr[] = { 80, 2, 6, 3, 100 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// Function calling 
	std::cout << "Maximum difference is " << maxDiff(arr, n);

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
