// Thread_guard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <exception>

class thread_guard
{
public :
	explicit thread_guard(std::thread& thread):m_threadHandle(thread)
	{}
	~thread_guard()
	{
		if (m_threadHandle.joinable())
		{
			m_threadHandle.join();
		}
	}
	thread_guard(const thread_guard&) = delete;
	thread_guard& operator=(const thread_guard&) = delete;
private :
	std::thread& m_threadHandle;
};

class scoped_thread_guard 
{
public :
	scoped_thread_guard(std::thread threadHandle): m_threadHandle(std::move(threadHandle))
	{
		if (!m_threadHandle.joinable())
		{
			throw std::logic_error("no thread attached to this thread object");
		}
	}

	scoped_thread_guard(std::thread&& threadHandle) : m_threadHandle(std::move(threadHandle))
	{
		if (!m_threadHandle.joinable())
		{
			throw std::logic_error("no thread attached to this thread object");
		}
	}
	~scoped_thread_guard()
	{
		// As compare to thread_guard class above, we don't need to check for joinable() as no one elae
		// other than this class has access to thread object so no one else can call join before reaching
		// here.
		m_threadHandle.join();
	}
	scoped_thread_guard(const scoped_thread_guard&) = delete;
	scoped_thread_guard& operator=(const scoped_thread_guard&) = delete;

private :
	std::thread m_threadHandle;
};

void DoNothing()
{
	std::cout << "Anand Shah" << std::endl;
}


int main()
{
	scoped_thread_guard guard(std::thread(DoNothing));
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
