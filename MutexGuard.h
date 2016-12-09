#include <pthread>
#include "Mutex.h"

class MutexGuard
{
	MutexGuard(Mutex &mutex):mutex_(mutex)
	{
		mutex_.lock();
	}

	~MutexGuard()
	{
		mutex_.unlock();
	}

private:
	MutexGuard(MutexGuard &);
	MutexGuard& operator=(MutexGuard &);
	Mutex &mutex_;
};


