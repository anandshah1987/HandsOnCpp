// NewDeleteOverloading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>

void* operator new(size_t size)
{
    std::cout << "Global Overload new, Allocating " << size << " bytes \n";
    return malloc(size);
}

void operator delete(void* ptr)
{
    std::cout << "Global Overlaod delete \n";
    free(ptr);
}
// Array version
void* operator new[](size_t size)
{
    std::cout << "Global Overload new[], Allocating " << size << " bytes \n";
    return malloc(size);
}

void operator delete[](void* ptr)
{
    std::cout << "Global Overlaod delete[] \n";
    free(ptr);
}

class Test
{
private :
    int m_val{};

public:
    void Set(int val)
    {
        m_val = val;
    }
    void print()
    {
        std::cout << "val = " << m_val << " \n";
    }
    Test()
    {
        std::cout << "Test() \n";
    }
    Test(int val)
    {
        std::cout << "Parameterized Test() with val = " << val << '\n';
        m_val = val;
    }
    ~Test()
    {
        std::cout << "~Test() \n";
    }
    
    void* operator new(size_t size)
    {
        std::cout << "Overload new, Allocating " << size << " bytes \n";
        return malloc(size);
    }

    void operator delete(void *ptr)
    {
        std::cout << "Overlaod delete \n";
        free(ptr);
    }
    // Array version
    void* operator new[](size_t size)
    {
        std::cout << "Overload new[], Allocating " << size << " bytes \n";
        return malloc(size);
    }

    void operator delete[](void* ptr)
    {
        std::cout << "Overlaod delete[] \n";
        free(ptr);
    }

    // Overload to pass arguments to new overload operator
    void* operator new(size_t size, int val)
    {
        std::cout << "Overload new with value, Allocating " << size << " bytes. Parameter = " << val << "\n";
        return malloc(size);
    }

};

int main()
{
    Test* ptr = new Test();
    ptr->print();
    delete ptr;

    ptr = new Test[2];
    for (int i = 0; i < 2; i++)
    {
        ptr[i].print();
    }
    delete[] ptr;

    ptr = new Test(10);
    ptr->print();
    delete ptr;

    // Below version will pass additional parameters to overload new
    ptr = new(12) Test();
    ptr->print();
    delete ptr;

    ptr = ::new Test();
    ptr->print();
    ::delete ptr;

    ptr = ::new Test[2];
    for (int i = 2; i < 10; i++)
    {
        ptr[i].print();
    }
    ::delete[] ptr;
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
