#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#include <functional>
#include <iostream>
#include <assert.h>


class thread_data
{
	public:
		thread_data(std::function<void()> &f):fun(f){}
		std::function<void()> fun;
};

class Thread
{
	public:
		explicit	Thread(std::function<void()> threadFunction):thread_function(threadFunction)
	{
		start_ =false;
		join_ = false;
	}

		~Thread()
		{
			if(start_ && !join_)
			{
				pthread_detach(tid);
			}
		}

		void start()
		{
			start_ = true;
			thread_data *thread_data_ptr = new thread_data(thread_function);
			pthread_create(&tid, NULL, run, thread_data_ptr);
		}

		void stop()
		{
			pthread_detach(tid);
		}

		int join()
		{
			assert(!join_);
			join_ = true;
			return pthread_join(tid, NULL);
		}

	private:

		static void* run(void* obj)
		{
			//必须是静态的成员函数才可以被调用
			//那么问题来了 怎么办
			thread_data* data = static_cast<thread_data*>(obj);
			data->fun();
			delete data;
			return NULL;
		}

		std::function<void()> thread_function;

		Thread(const Thread&) = delete;
		Thread& operator=(const Thread&) = delete;

		pthread_t tid;
		bool start_;
		bool join_;
};

#endif
