#include <iostream>
#include "Mutex.h"

int main()
{
	Mutex mutex;
	{
	MutexGaurd(mutex);

	//离开这个作用域的时候 自动解锁
	}

	return 0;
}

