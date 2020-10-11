// FactorialOfLargeNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<vector>
using namespace std;



int main() {
    int num;
    cout << "Enter the number :";
    cin >> num;
    vector<int> res;
    res.push_back(1);
    int carry = 0;
    for (int i = 2; i <= num; i++) 
    {
        for (int j = 0; j < res.size(); j++) 
        {
            int tmp = res[j] * i;
            res[j] = (tmp + carry) % 10;
            carry = (tmp + carry) / 10;
        }
        while (carry != 0) 
        {
            res.push_back(carry % 10);
            carry = carry / 10;
        }

    }

    for (int i = res.size() - 1; i >= 0; i--) cout << res[i];
        cout << endl;

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
