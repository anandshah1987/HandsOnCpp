// ConsumerProducer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>

std::vector<int> source;
std::mutex mutex;

std::mutex logMutex;

void LogMessage(std::string message)
{
    std::lock_guard<std::mutex> lock{logMutex};
    std::cout << message << std::endl;
}
// Version 1:- Producer fast, consumer slow

void ProcessingFunction()
{
    int job{};
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (source.empty())
            {
                std::stringstream message;
                message << "Treminating thread : " << std::this_thread::get_id();
                LogMessage(message.str());
                break;
            }
            job = source.back();
            source.pop_back();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(job));
        //std::cout << "Processed item " << job << " by thread " << std::this_thread::get_id() << std::endl;
        std::stringstream message1;
        message1 << "Processed item " << job << " by thread " << std::this_thread::get_id();
        LogMessage(message1.str());
    }
}

int main()
{
    std::cout << "Hello World!\n";

    // Launch 4 thread to process
    std::vector<std::thread> processorThreads;
    for (int i = 0; i < 4; i++)
    {
        std::thread thread(ProcessingFunction);
        processorThreads.emplace_back(std::move(thread));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    for (int i = 0; i < 100; i++)
    {
        source.emplace_back(i);
    }

    for (auto& threadObj : processorThreads)
    {
        if (threadObj.joinable())
        {
            threadObj.join();
        }
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
