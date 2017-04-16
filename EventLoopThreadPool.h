#ifndef EVENTLOOPTHEADPOOL_H
#define EVENTLOOPTHEADPOOL_H
#include "EventLoop.h"
#include "EventLoopThread.h"

#include <string>
#include <vector>

class EventLoopThreadPool
{
  public:
    EventLoopThreadPool(EventLoop *baseLoop, std::string &name);
    ~EventLoopThreadPool();
    EventLoopThreadPool(const EventLoopThreadPool&) = delete;
    EventLoopThreadPool& operator = (const EventLoopThreadPool&) = delete;

    EventLoop* getNextEvent();
    std::vector<EventLoop*> getAllEvent();

    bool isStart() const
    {
      return start_;
    }

    std::string name()
    {
      return name_;
    }

    void setNumbers(int num)
    {
      numbers_ = num;
    }

    void start();

  private:
    EventLoop *baseLoop_;
    std::string name_;
    bool start_;
    int numbers_;
    int next_;
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};

#endif
