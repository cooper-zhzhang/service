#ifndef EPOLL_H
#define EPOLL_H

#include <map>
#include "EventLoop.h"
#include "Channel.h"

class Epoll
{
  public:
    Epoll(EventLoop *loop);
    addChannel();
    deleteChannel();
    updateChannel();

  private:
    void update(int operation, Channel *channel);
    int epollfd_;
    std::map<int, Channel*> channels_;
    EventLoop *loop;
}
#endif
