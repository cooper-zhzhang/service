#ifndef EVENTLOOPTHREAD_H
#define EVENTLOOPTHREAD_H

#include "EventLoop.h"
#include "Thread.h"
#include "Mutex.h"
#include "Condition.h"
#include <string>

class EventLoopThread
{
  public:

    EventLoopThread(string &name);
    ~EventLoopThread();
    EventLoopThread(const EventLoopThread&) = delete;
    EventLoopThread& operator = (const EventLoopThread) = delete;

    EventLoop* startRun();
  private:
    void threaFun();

    EventLoop *loop_;
    bool exiting_;
    Thread thread_;

    Mutex mutex_;
    Condition condition_;

};
#endif 
