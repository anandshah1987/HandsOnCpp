// Decorator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>


class BaseCount
{
public:
	virtual double GetTransCount()
	{
		return 0;
	}
};

//class ActiveTransCount : public BaseCount
//{
//public :
//	double GetTransCount() override
//	{
//		return 1;
//	}
//};
//class SentTransCount : public BaseCount
//{
//public:
//	double GetTransCount() override
//	{
//		return 2;
//	}
//};
//class SettledTransCount : public BaseCount
//{
//public:
//	double GetTransCount() override
//	{
//		return 3;
//	}
//};

// Now we may want to know transaction count for below combination. Notice that we need to re-implement the logic
// for GetTransCount() which was already done.

// In below combination, we will repeat the logic of active order count + sent order count.
// And that's the problem with inheritance. With many combinations, "Class explosion" happens(that means number of
// derived classes tends to increase) and code becomes very difficult to maintain
//class ActiveSentTransCount : public BaseCount
//{
//public:
//	double GetTransCount() override
//	{
//		return 3; // active 1 + sent 2 = 3
//	}
//};
//class ActiveSettledTransCount : public BaseCount
//{
//public:
//	double GetTransCount() override
//	{
//		return 4;  // active 1 + settled 3 = 4
//	}
//};

// As shown with below classes, we can solve problems of inheritance by using decorator design pattern  
// we need one class in hiracrhy who should have default constructor 

//Introduce below Abstract class to force everyone to implement GetTransCount() method
class BaseCountAbstract
{
public :
	virtual double GetTransCount()
	{
		return 0;
	}
};

class ActiveTransCount : public BaseCountAbstract
{
	BaseCountAbstract* m_basePtr{};
public :
	ActiveTransCount(BaseCountAbstract* basePtr):m_basePtr(basePtr)
	{
	}
	double GetTransCount() override
	{
		return 1 + m_basePtr->GetTransCount();
	}
};
class SentTransCount : public BaseCountAbstract
{
	BaseCountAbstract* m_basePtr{};
public:
	SentTransCount(BaseCountAbstract* basePtr) :m_basePtr(basePtr)
	{
	}
	double GetTransCount() override
	{
		return 2 + m_basePtr->GetTransCount();
	}
};
class SettledTransCount : public BaseCountAbstract
{
	BaseCountAbstract* m_basePtr{};
public:
	SettledTransCount(BaseCountAbstract* basePtr) :m_basePtr(basePtr)
	{
	}
	double GetTransCount() override
	{
		return 3 + m_basePtr->GetTransCount();
	}
};

int main()
{
   // So below is the way to create combination of ActiveSentTransCount 
	BaseCountAbstract*  ptr = new ActiveTransCount(new SentTransCount(new BaseCountAbstract()));
	std::cout << "Trans count for ActiveSentTransCount = " << ptr->GetTransCount() << std::endl;
	//Below is the way to create combination of ActiveSentSettledTransCount
	ptr = new ActiveTransCount(new SentTransCount(new SettledTransCount(new BaseCountAbstract())));
	std::cout << "Trans count for ActiveSentTransCount = " << ptr->GetTransCount() << std::endl;
	// Note :- To achieve above combination in inheritance, we require to create new a class and provide implementation to get transCout.
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
