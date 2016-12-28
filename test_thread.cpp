#include "Thread.h"
#include <iostream>


void fun()
{
	std::cout << "this is a thread" << std::endl;
}

int main()
{


	std::function<void()> thread_fun = fun;
	Thread thread(thread_fun);
	thread.start();
	thread.join();

	return 0;
}
