// Abstract_Factory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

class Button
{
public :
	virtual void DrawButton() = 0;
	~Button()
	{

	}
};

class WinButton : public Button
{
public :
	void DrawButton() override
	{
		std::cout << "Drwaing windows button ..." << std::endl;
	}
};

class LinuxButton : public Button
{
public:
	void DrawButton() override
	{
		std::cout << "Drwaing linux button ..." << std::endl;
	}
};

// New addition to support MAC
//class MacButton : public Button
//{
//public :
//	void DrawButton() override
//	{
//		std::cout << "Drwaing Mac button ..." << std::endl;
//	}
//};

class ScrollBar
{
public :
	virtual void DrawScrollBar() = 0;
};

class WinScrollBar : public ScrollBar
{
public:
	void DrawScrollBar() override
	{
		std::cout << "Drawing windows scrollbar ..." << std::endl;
	}

};

class LinuxScrollBar : public ScrollBar
{
public:
	void DrawScrollBar() override
	{
		std::cout << "Drawing linux scrollbar ..." << std::endl;
	}
};

// New addition to support MAC
//class MacScrollBar : public ScrollBar
//{
//public:
//	void DrawScrollBar() override
//	{
//		std::cout << "Drawing Mac scrollbar ..." << std::endl;
//	}
//};

class WidgetBaseFactory
{
public :
	virtual Button* CreateButton() = 0;
	virtual ScrollBar* CreateScrollBar() = 0;
};

class WinWidgetFactory : public WidgetBaseFactory
{
public:
	Button* CreateButton() override
	{
		return new WinButton();
	}
	ScrollBar* CreateScrollBar() override
	{
		return new WinScrollBar();
	}
};

class LinuxWidgetFactory : public WidgetBaseFactory
{
public :
	Button* CreateButton() override
	{
		return new LinuxButton();
	}
	ScrollBar* CreateScrollBar() override
	{
		return new LinuxScrollBar();
	}
};

// So now let's say you want to add widgets button and scroll bar for MAC os.
//class MacWidgetFactory : public WidgetBaseFactory
//{
//public:
//	Button* CreateButton() override
//	{
//		return new MacButton();
//	}
//	ScrollBar* CreateScrollBar() override
//	{
//		return new MacScrollBar();
//	}
//};


#define WINDOWS

int main()
{
    std::cout << "Hello World!\n"; 
	WidgetBaseFactory *factory;

#if defined WINDOWS
	factory = new WinWidgetFactory();
#elif defined LINUX
	factory = new LinuxWidgetFactory();
#elif defined MAC
	/*factory = new MacWidgetFactory();*/
#endif // WINDOWS
	Button* button = factory->CreateButton();
	button->DrawButton();
	ScrollBar* scrollBar = factory->CreateScrollBar();
	scrollBar->DrawScrollBar();

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
