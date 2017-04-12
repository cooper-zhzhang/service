#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, std::string &name):
  baseLoop_(baseLoop), name_(name), start_(false), numbers_(0), next_(0)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
}

EventLoop* EventLoopThreadPool::getNextEvent()
{
  if(loops_.empty())
    return baseLoop_;

  next_ = (next_ + 1) % numbers_;
  return loops_[next_];
}

std::vector<EventLoop*> EventLoopThreadPool::getAllEvent()
{
  if(loops_.empty())
    return std::vector<EventLoop*> (1, baseLoop_);
  return loops_;
}

void EventLoopThreadPool::start()
{
  start_ = true;
  for(int i = 0; i < numbers_; ++i)
  {
    std::string threadName = name_ + std::to_string(i);
    EventLoopThread *pthread = new EventLoopThread(threadName);
    threads_.push_back(std::unique_ptr<EventLoopThread>(pthrad));
    loops_.push_back(pthread->startiRun());
  }
}

