#include <pthread.h>

class Thread
{
pubblic:
	Thread(function<void, void> threadFunction);
	void start();
};
