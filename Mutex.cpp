#include <pthread.h>
#include "Mutex.h"

Mutex::Mutex()
{
	pthread_mutex_init(&mutex_, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&mutex_);
}

void Mutex::lock()
{
	pthread_mutex_lock(&mutex_);
}
	
void Mutex::unlock()
{
	pthread_mutex_unlock(&mutex_);
}

pthread_mutex_t* Mutex::getPthreadMutex()
{
	return &mutex_;
}

