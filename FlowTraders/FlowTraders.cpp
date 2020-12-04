//// FlowTraders.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//
#include <iostream>
#include <vector>
#include <string>


//https://stackoverflow.com/questions/49738476/why-is-the-default-constructor-deleted-in-derived-class
//template <typename T>
//class Foo 
//{
//    T tVar;
//public:
//    Foo(T t) : tVar(t) {}
//};
//
//class FooDerived : public Foo<std::string> {};
//
//
//int main()
//{
//    FooDerived d;
//    return 0;
//}
//
//using namespace std;
//
//template<typename T>
//void adl(T)
//{
//    cout << "T";
//}
//
//struct S
//{
//};
//
//
//
//template<typename T>
//void call_adl(T t)
//{
//    adl(S());
//    adl(t);
//}
//
//void adl(S)
//{
//    cout << "S";
//}
//
//
//int main()
//{
//    call_adl(S());
//}
//
//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//// Debug program: F5 or Debug > Start Debugging menu
//
//// Tips for Getting Started: 
////   1. Use the Solution Explorer window to add/manage files
////   2. Use the Team Explorer window to connect to source control
////   3. Use the Output window to see build output and other messages
////   4. Use the Error List window to view errors
////   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
////   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

//#include <algorithm>
//#include <bitset>
//#include <string>
//
//int changeAds(int base10) 
//{
//    auto numStr = std::bitset<32>(base10).to_string();
//    int result{};
//
//    if (numStr.size() > 0)
//    {
//        numStr.erase(0, std::min(numStr.find_first_not_of('0'), numStr.size() - 1));
//        for (auto& character : numStr)
//        {
//            if ('1' == character)
//            {
//                character = '0';
//            }
//            else if ('0' == character)
//            {
//                character = '1';
//            }
//        }
//        result = std::bitset<32>(numStr).to_ullong();
//    }
//    return result;
//}
//
//int kDifference(std::vector<int> projectCosts, int target) 
//{
//    std::sort(projectCosts.begin(), projectCosts.end(), std::greater<int>());
//    int sameTargetCount = 0;
//    using CountType = std::vector<int>::size_type;
//    for (CountType i=0; i<(projectCosts.size()-1); i++)
//    {
//        for (CountType j=i+1; j< projectCosts.size(); j++)
//        {
//            auto diff = projectCosts.at(i) - projectCosts.at(j);
//            if (diff > target)
//            {
//                break;
//            }
//            if (diff == target)
//            {
//                sameTargetCount++;
//            }
//        }
//    }
//    return sameTargetCount;
//}
//
//int main()
//{
//    int a = 0;
//    decltype((a)) b = a;
//    b++;
//    std::cout << a << b;
//}

//template <template <typename> class>
//struct X 
//{
//    X() { std::cout << "1"; }
//};

//template <typename>
//struct Y {};
//
//template <typename T>
//using Z = Y<T>;
//
//template <>
//struct X<Y>
//{
//    X() { std::cout << "2"; }
//};


//struct A
//{
//    A()
//    {
//        throw 2;
//    }
//};
//
//struct B
//{
//    B()
//    {
//        try
//        {
//            A a;
//        }
//        catch (int i)
//        {
//            std::cout << i;
//        }
//    }
//};

////#include <math.h>
//
//struct Point
//{
//    Point(int xIn, int yIn) :x(xIn), y(yIn) {}
//    int x{};
//    int y{};
//};
//
//int square(int x)
//{
//    return x * x;
//}
//
//int distSquare(Point p1, Point p2)
//{
//    return square(p1.x - p2.x) + square(p1.y - p2.y);
//}
//
//float area(int x1, int y1, int x2, int y2, int x3, int y3)
//{
//    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
//}
//
//bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
//{
//    /* Calculate area of triangle ABC */
//    float A = area(x1, y1, x2, y2, x3, y3);
//
//    /* Calculate area of triangle PBC */
//    float A1 = area(x, y, x2, y2, x3, y3);
//
//    /* Calculate area of triangle PAC */
//    float A2 = area(x1, y1, x, y, x3, y3);
//
//    /* Calculate area of triangle PAB */
//    float A3 = area(x1, y1, x2, y2, x, y);
//
//    /* Check if sum of A1, A2 and A3 is same as A */
//    return (A == A1 + A2 + A3);
//}
//
//bool IsValidNonDegenerateTriangle(int lenAB, int lenBC, int lenAC)
//{
//    if (((lenAB + lenBC) > lenAC) && ((lenBC+ lenAC)> lenAB)
//        && ((lenAB+ lenAC) > lenBC))
//    {
//        return true;
//    }
//    return false;
//}
//
//struct Triangle
//{
//    Triangle(Point aIn, Point bIn, Point cIn) :a(aIn), b(bIn), c(cIn) {}
//    Point a;
//    Point b;
//    Point c;
//}
//
//bool DoesPointBelongToTriangle(const Triangle& triangle, Point pointToCheck)
//{
//
//}
//
//int pointsBelong(int x1, int y1, int x2, int y2, int x3, int y3, int xp, int yp, int xq, int yq)
//{
//    Point a(x1, y1);
//    Point b(x2, y2);
//    Point c(x3, y3);
//    int lenAB = std::sqrt(distSquare(a, b));
//    int lenBC = std::sqrt(distSquare(b, c));
//    int lenAC = std::sqrt(distSquare(a, c));
//
//    if (!IsValidNonDegenerateTriangle(lenAB, lenBC, lenAC))
//    {
//        return 0;
//    }
//    return -1;
//}

//int main() {
//  /*  X<Y> x1;
//    X<Z> x2;*/
//    //B b;
//    //std::cout << 3;
//}