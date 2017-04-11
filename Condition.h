#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>
#include "Mutex.h"

class Condition
{
  public:
    explicit Condition(Mutex& mutex) : mutex_(mutex)
    {
      pthread_cond_init(&cond_, NULL);
    }

    void wait()
    {
      pthread_cond_wait(&cond_, mutex_.getPthreadMutex());
    }

    void signal() 
    {
      pthread_cond_signal(&cond_);
    }

    ~Condition()
    {
      pthread_cond_destroy(&cond_);
    }

    Condition(const Condition&) =delete;
    Condition& operator=(const Condition&) = delete;

  private:

    pthread_cond_t cond_;
    Mutex &mutex_;
};

#endif
