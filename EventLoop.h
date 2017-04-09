#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "Current.h"
#include "Channel.h"

class EventLoop
{
  public:

    EventLoop();
    ~EventLoop();

    EventLoop(const EventLoop &) = delete;
    EventLoop& operator = (const EventLoop &) = delete;

    static int createEventFd();

    void loop();
    void quit();
    bool isInLoopThread() const
    {
      return Current::tid() == threadId_;
    }

    void removeChannel(Channel *channel);
    void updateChannel(Channel *channel);


  private:
    std::vector<Channel*> activeChannels_;

    bool running_;
    bool quit_;
    const pid_t threadId_;
};


#endif 
