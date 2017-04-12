#include "EventLoopThread.h"
#include <functional>

EventLoopThread::EventLoopThread(std::string &name):
  loop_(nullptr), thread_(std::bind(&EventLoopThread::threaFun, this), name),
  mutex_(), condition_(mutex_)
{
}

EventLoopThread::~EventLoopThread()
{
  exiting_ = true;
  if(loop_ != nullptr)
  {
    loop_->quit();
    thread_.join();
  }
}


EventLoop* EventLoopThread::startRun()
{
  thread_.start();

  {
    MutexGuard lock(mutex_);
    while(loop_ == nullptr)
    {
      condition_.wait();
    }
  }

  return loop_;
}

void EventLoopThread::threaFun()
{
  EventLoop loop;
  {
    MutexGuard lock(mutex_);
    loop_ = &loop;
    condition_.signal();
  }

  loop_->run();
  loop_= nullptr;

}
