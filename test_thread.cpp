#include "Thread.h"
#include <iostream>
#include <string>
#include <functional>
#include <pthread.h>


void fun()
{
	std::cout << "this is a thread" << std::endl;
}

int main()
{

	std::function<void()> thread_fun = fun;
	Thread thread(thread_fun, std::string("test"));
	std::cout << thread.name() << std::endl;
	thread.start();
	thread.join();

	return 0;
}
