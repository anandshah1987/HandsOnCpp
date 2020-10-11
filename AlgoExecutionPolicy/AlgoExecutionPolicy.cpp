// AlgoExecutionPolicy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <execution>
#include <vector>
#include <random>
#include <chrono>

// Conclusion - So paraller execution policy starts better performing after 100000 int elements
// so you have to always profile your code for your type and algorithm and see if parallel execution
// really helps
// Note from Microsoft -  Parallelization does have some overhead and will be slower than the serial version 
// if N is small enough, 
// https://www.bfilipek.com/2018/11/parallel-alg-perf.html

int main()
{
    std::random_device rd;
    //std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 1000);
    std::vector<int> vecInt{};
    for (int i=0; i< 100000; i++)
    {
        vecInt.emplace_back(distribution(rd));
    }

    auto start = std::chrono::steady_clock::now();
    //std::sort(std::execution::par, vecInt.begin(), vecInt.end());
    std::sort(vecInt.begin(), vecInt.end());
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "[µs]" << std::endl;
}