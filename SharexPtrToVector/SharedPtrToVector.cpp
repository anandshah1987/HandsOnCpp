// SharedPtrToVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
class Test
{
public :
    Test()
    {
        std::cout << "Construct Test()" << std::endl;
    }
    Test(const Test& t)
    {
        std::cout << "copy Construct Test()" << std::endl;
    }

    ~Test()
    {
        std::cout << "Destruct Test()" << std::endl;
    }
};

std::vector<Test> testCollection;
using TestCollection = std::vector<Test>;

std::shared_ptr<TestCollection> ptrToTestCollection;


int main()
{
   ptrToTestCollection = std::make_shared<TestCollection>();
   ptrToTestCollection->reserve(3);
    for (int i=3; i>0; i--)
    {
        ptrToTestCollection->emplace_back();
    }

    std::cout << "================================" << std::endl;

    ptrToTestCollection.reset();
    if (!ptrToTestCollection)
    {
        std::cout << "ptrToTestCollection is null" << std::endl;
    }
    if (ptrToTestCollection==nullptr || ptrToTestCollection->empty())
    {
        std::cout << "Collection is empty" << std::endl;
    }

    std::cout << "Hello World!\n";
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
