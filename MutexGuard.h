#ifndef MUTEXGUARD_H
#define MUTEXGUARD_H
#include <pthread.h>
#include "Mutex.h"

class MutexGuard
{
	public:
		MutexGuard(Mutex &mutex):mutex_(mutex)
	{
		mutex_.lock();
	}

		~MutexGuard()
		{
			mutex_.unlock();
		}

	private:
		MutexGuard(const MutexGuard &);
		MutexGuard& operator=(const MutexGuard &);
		Mutex &mutex_;
};


#endif
