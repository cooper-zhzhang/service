#include <unistd.h>
#include "EventLoop.h"
#include "MutexGuard.h"

EventLoop::EventLoop():
  running_(false), 
  quit_(false), 
  threadId_(Current::tid()), 
  wakeFd_(Epoll::createEventFd()), 
  wakeChannel_(new Channel(this, wakeFd_)), 
  epoll_(Epoll::newEpoll(this))
{
  wakeChannel_->setReadCallBack(std::bind(&EventLoop::handleWakeUp, this));
  wakeChannel_->enableReading();
}

EventLoop::~EventLoop()
{
  wakeChannel_->disableAll();
  wakeChannel_->remove();
  ::close(wakeFd_);
}

void EventLoop::wakeUp()
{
  int wakeup = 1;
  size_t num = ::write(wakeFd_, &wakeup, sizeof(wakeup));
  if(num != sizeof(wakeup))
  {
    // TODO 添加日志
  }
}

void EventLoop::run()
{
  running_ = true;
  quit_ = false;

  while(!quit_)
  {
    activeChannels_.clear();
    epoll_->poll(10000, &activeChannels_);

    for(auto it = activeChannels_.begin(); it != activeChannels_.end(); ++it)
    {
      activeChannel = *it;
      activeChannel->handleEvent();
    }
    activeChannel = nullptr;

    doPengFunctions();
  }
}

void EventLoop::doPengFunctions()
{
  std::vector<std::function<void()>> functions;

  {
    MutexGuard lock(mutex_);
    std::swap(functions, pengFunctions_);
  }

  for(int i = 0; i < functions.size(); ++i)
  {
    functions[i]();
  }
}

void EventLoop::runInLoop(std::function<void()> fun)
{
  if(isInLoopThread())
  {
    fun();
  }
  else
  {
    runInQueue(fun);
  }
}

void EventLoop::runInQueue(std::function<void()> fun)
{
  MutexGuard lock(mutex_);
  pengFunctions_.push_back(fun);
}

void EventLoop::removeChannel(Channel *channel)
{
  epoll_->removeChannel(channel);
}

void EventLoop::updateChannel(Channel *channel)
{
  epoll_->updateChannel(channel);
}

void EventLoop::quit()
{
  quit_ = true;
  if(!isInLoopThread())
    wakeUp();
}

void EventLoop::handleWakeUp()
{
  int wakeup = 1;
  size_t num = ::read(wakeFd_, &wakeup, sizeof(wakeup));
  if(num != sizeof(wakeup))
  {
    // TODO 日志
  }
}
