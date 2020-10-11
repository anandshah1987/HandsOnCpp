// Observer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>
class EventBase
{
public:
	virtual void EventNotification() = 0;
};

class PublisherBase
{
public :
	virtual void Notify() = 0;
	virtual void SubscribeEventHandler(EventBase& event) = 0;
	//virtual void UnSubscribeEventHandler(EventBase* event) = 0;
};

class CParticipant : public PublisherBase
{
	std::vector<std::reference_wrapper<EventBase>> eventsToNotiify;
public :
	void Create()
	{
		std::cout << "Creating Participant ..." << std::endl;
		Notify();
	}
	void Notify() override
	{
		std::cout << "Notifying events about new participant creation ..." << std::endl;
		for (auto& event : eventsToNotiify)
		{
			event.get().EventNotification();
		}
	}
	void SubscribeEventHandler(EventBase& event) override
	{
		eventsToNotiify.emplace_back(event);
	}
};


class XmlDispatchOnNewParticipantCreation : public EventBase
{
	//std::unique_ptr<PublisherBase> m_eventPublisher;
public :
	void EventNotification() override
	{
		std::cout << "Got new participant creation event. Dispatching XML report..." << std::endl;
	}
};

class TriggerAsyncProcOnNewParticipantCreation : public EventBase
{
	//std::unique_ptr<PublisherBase> m_eventPublisher;
public:
	void EventNotification() override
	{
		std::cout << "Got new participant creation event. Triggering async proc..." << std::endl;
	}
};

void CreateParticipant()
{
	CParticipant participant;
	XmlDispatchOnNewParticipantCreation dispatcher;
	TriggerAsyncProcOnNewParticipantCreation asycTrigger;
	participant.SubscribeEventHandler(dispatcher);
	participant.SubscribeEventHandler(asycTrigger);
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
