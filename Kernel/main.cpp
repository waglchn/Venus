///检查编译报错
#include "Venus.h"

#include <windows.h>
#include <stdio.h>
using namespace venus;
static int gGlobalIndex = 0;
class CVenusThread :public VenusThread
{
	int miIndex;
public:
	CVenusThread(int index)
	{
		miIndex = index;
	}
	void onEntry() override
	{
		printf("onEntry:\t%d\n", miIndex);
	}

	void onLeave() 
	{
		printf("onLeave:\t%d\n", miIndex);
	}
	void onRun() 
	{
		while (working())
		{
			printf("onRun:\t%d-%d\n", miIndex,gGlobalIndex++);
		}
	}
};

int main(int argc, char** argv)
{
	//printf("%s", "hello world!");
	CVenusThread thread1(1);
	CVenusThread thread2(2);
	CVenusThread thread3(3);
	thread1.open();
	thread2.open();
	thread3.open();
	int key = 0;
	while (true)
	{
		scanf_s("%d", &key);
		if (key == 0)
		{
			break;
		}
		else if (key == 1)
		{
			thread1.activate();
		}
		else if (key == 2)
		{
			thread2.activate();
		}
		else if (key == 3)
		{
			thread3.activate();
		}
		else if (key == 4)
		{
			thread1.silent();
		}
		else if (key == 5)
		{
			thread2.silent();
		}
		else if (key == 6)
		{
			thread3.silent();
		}
		else if (key == 7)
		{
			thread1.cancel();
		}
		else if (key == 8)
		{
			thread2.cancel();
		}
		else if (key == 9)
		{
			thread3.cancel();
		}
	}
	
	return 0;
}
