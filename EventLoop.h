#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "Current.h"
#include "Channel.h"
#include "Epoll.h"

class EventLoop
{
  public:

    EventLoop();
    ~EventLoop();

    EventLoop(const EventLoop &) = delete;
    EventLoop& operator = (const EventLoop &) = delete;

    static int createEventFd();

    void run();
    void quit();
    bool isInLoopThread() const
    {
      return Current::tid() == threadId_;
    }

    void removeChannel(Channel *channel);
    void updateChannel(Channel *channel);
    void wakeUp();

    void doPengFunctions();

  private:
    std::vector<Channel*> activeChannels_;
    Channel *activeChannel;

    std::unique_ptr<Epoll> epoll_;
    bool running_;
    bool quit_;
    const pid_t threadId_;

    int wakeFd_;
    Channel *wakeChannel_;
    void handleWakeUp();

    Mutex mutex_;
    std::vector<std::function<void()>> pengFunctions_;
};


#endif 
