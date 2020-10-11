// RandomNumGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <chrono>

int main()
{
   // std::cout << "Hello World!\n";
    
    for (int i=0; i<100; i+=10)
    {
        double d = 1230.1230+i;
        double minPercentage = -1;
        double maxPercentage = 1;

        auto start = std::chrono::steady_clock::now();

        std::random_device myRandomDevice;
        unsigned seed = myRandomDevice();
         // Initialize a default_random_engine with the seed
         //std::default_random_engine myRandomEngine(10);
        std::default_random_engine myRandomEngine(seed);

        std::uniform_real_distribution<double> myUnifRealDist(minPercentage, maxPercentage);
        double randomPerc = myUnifRealDist(myRandomEngine);

        auto number = d + (d * (randomPerc / 100));
        std::cout << "Number is " << number << std::endl;

        auto end = std::chrono::steady_clock::now();

       /* std::cout << "Elapsed time in microseconds : "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << " mmicrsecs" << std::endl;*/
        /*for (int i = 0; i < 5; i++)
        {
            double number = myUnifRealDist(myRandomEngine);
            std::cout << std::fixed << number << std::endl;
        }*/
    }
    
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
