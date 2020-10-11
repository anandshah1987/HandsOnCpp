// ObjectSlicing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Base
{
public :
    Base() = default;
    Base(const int val) :m_bVal(val) {}
    const int GetBaseVal() const
    {
        return m_bVal;
    }
    virtual ~Base() {}
private :
    int m_bVal{};
};
class Derived : public Base
{
public:
    Derived() = default;
    Derived(const int bVal, const int dVal) :Base(bVal), m_dVal(dVal) {}
    const int GetDerivedVal() const
    {
        return m_dVal;
    }
private :
    int m_dVal{};
};


int main()
{
    Base* bptr1 = new Derived(1,2);
    Base* bptr2 = new Derived(3, 4);
    *bptr1 = *bptr2; // This line results in object slicing as assignment operator is invoked statically so this
        // will invoke assigment operator of base class resulting in copying only base data.
    auto dPtr = dynamic_cast<Derived*>(bptr1);
    // Below line will print 3, 2 as against expected value of 3,4
    std::cout << dPtr->GetBaseVal() << " " << dPtr->GetDerivedVal();
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
