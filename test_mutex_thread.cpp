#include <iostream>
#include <pthread.h>
#include "Mutex.h"
#include "MutexGuard.h"
#include "Thread.h"

#define DEBUG

static int count = 0;
Mutex mutex;

void fun()
{
	int i = 10000;
	while(i--)
	{
		{
			MutexGuard lock(mutex);
			++ count;
		}
	}
}

int main()
{

	std::function<void()> thread_function;
	thread_function = fun;

	Thread thread1(thread_function);
	Thread thread2(thread_function);
//	Thread thread3(thread2); 验证delete
	thread1.start();
	thread2.start();
	thread1.join();
	thread2.join();
	//thread2.join();验证不能重复join
	std::cout << count << std::endl;

	return 0;
}

