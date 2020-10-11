// Strim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

size_t strtrim(char* szString)
{
	char* 	szPos;
	size_t 	iLength;

	if ((szString == nullptr) || (*szString == 0))
		return 0;

	szPos = szString;
	while (*szPos != 0)
	{
		if (strchr(" \t\r\n", *szPos) == nullptr)
			break;
		szPos++;
	}

	iLength = strlen(szPos);
	if (szPos != szString)
	{
		memmove(szString, szPos, iLength + 1);
	}

	if (*szString == 0)
		return 0;

	szPos = &szString[iLength - 1];
	while (szPos != szString)
	{
		if (strchr(" \t\r\n", *szPos) == nullptr)
			break;
		*szPos = 0;
		szPos--;
	}

	return (szPos - szString) + 1;
}

int main()
{
	char string[] = "   Anand   Shah  ";

	strtrim(string);
	std::cout << string << std::endl;
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
