// Observer_C++11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <functional>
//#include <vector>
#include <unordered_map>


// Visit https://www.theimpossiblecode.com/blog/c11-generic-observer-pattern/ to understand how to unsubscribe
// using vector's iterator returned from SubscribeEventHandler() method

using CallBackFunction = std::function<void(void)>;


class PublisherBase
{
public:
	virtual void Notify() = 0;
	virtual void SubscribeEventHandler(std::string key, CallBackFunction event) = 0;
	virtual void UnSubscribeEventHandler(std::string key) = 0;
};

class CParticipant : public PublisherBase
{
	std::unordered_map<std::string, CallBackFunction> evenCallBacks;
	//std::vector<CallBackFunction> evenCallBacks;
public:
	void Create()
	{
		std::cout << "Creating Participant ..." << std::endl;
		Notify();
	}
	void Notify() override
	{
		std::cout << "Notifying events about new participant creation ..." << std::endl;
		for (auto& callBack : evenCallBacks)
		{
			//callBack();
			callBack.second();
		}
	}
	void SubscribeEventHandler(std::string key, CallBackFunction event) override
	{
		//evenCallBacks.emplace_back(event);
		evenCallBacks[key] = event;
	}

	void UnSubscribeEventHandler(std::string key) override
	{
		//auto iter = std::find(evenCallBacks.begin(), evenCallBacks.end(), eventCallBack);
		auto iter = evenCallBacks.find(key);
		if (evenCallBacks.end() != iter)
		{
			evenCallBacks.erase(iter);
		}
	}
};


class XmlDispatchOnNewParticipantCreation
{
public:
	void XmlDispatcher()
	{
		std::cout << "Got new participant creation event in XmlDispatcher(). Dispatching XML report..." << std::endl;
	}
	void XmlDispatcher(int val)
	{
		std::cout << "Got new participant creation event in XmlDispatcher(int) with value " << val 
					<< " Dispatching XML report..." << std::endl;
	}
};

class TriggerAsyncProcOnNewParticipantCreation
{
public:
	void AysncTrigger()
	{
		std::cout << "Got new participant creation event in AysncTrigger(). Triggering async proc..." << std::endl;
	}
};

void CreateParticipant()
{
	CParticipant participant;
	XmlDispatchOnNewParticipantCreation dispatcher;
	TriggerAsyncProcOnNewParticipantCreation asycTrigger;
	// Pass lambadas below
	participant.SubscribeEventHandler("dispatcher.XmlDispatcher()", [&dispatcher] {dispatcher.XmlDispatcher(); });
	participant.SubscribeEventHandler("dispatcher.XmlDispatcher(10)", [&dispatcher] {dispatcher.XmlDispatcher(10); });
	participant.SubscribeEventHandler("asycTrigger.AysncTrigger()", [&asycTrigger] {asycTrigger.AysncTrigger(); });
	participant.Create();
	participant.UnSubscribeEventHandler("asycTrigger.AysncTrigger()");
	participant.Create();
}

int main()
{
	CreateParticipant();
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
