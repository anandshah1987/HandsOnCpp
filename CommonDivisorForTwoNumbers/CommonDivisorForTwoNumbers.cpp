// CommonDivisorForTwoNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int GCD(int a, int b)
{
    if (0 == a)
    {
        return b;
    }
    if (0 == b)
    {
        return a;
    }

    return GCD(b % a, a);
}

int CommonDivisors(int a, int b)
{
    auto gcd = GCD(a, b);
    auto sqRt = std::sqrt(gcd);
    int result = 0;
    for (int i=1; i<= sqRt; i++)
    {
        if (gcd  %i ==0)
        {
            if (gcd/i == i)
            {
                result+= 1;
            }
            else
            {
                result += 2;
            }
        }
    }
    return result;
}

int main()
{
    auto count = CommonDivisors(36, 24);
    std::cout << "Hello World!\n";
}