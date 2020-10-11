#include <vector>
#include <iostream>

class NotCopyable {
protected:
	NotCopyable() {}
	~NotCopyable() {}

public:
	NotCopyable(const NotCopyable& nc) = delete;
	NotCopyable& operator=(const NotCopyable& nc) = delete;
	NotCopyable(NotCopyable&& nc) = delete;
	NotCopyable& operator=(NotCopyable&& nc) = delete;
};



class Test : public NotCopyable
{

public :
	Test() {}
	
};

enum  Color
{
	red,
	black
};

int main()
{
	Test t1, t2;
	t1 = t2;
}