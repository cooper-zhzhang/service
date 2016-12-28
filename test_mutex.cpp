#include <iostream>
#include <pthread.h>
#include "Mutex.h"
#include "MutexGuard.h"

static int count = 0;
Mutex mutex;

void* fun(void*)
{
	int i = 10000;
	while(i--)
	{
		{
			MutexGuard lock(mutex);
			++ count;
		}
	}
	return NULL;
}

int main()
{

	pthread_t t1, t2;
	pthread_create(&t1, NULL, fun, NULL);
	pthread_create(&t2, NULL, fun, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	std::cout << count << std::endl;

	return 0;
}

