#ifndef EPOLL_H
#define EPOLL_H

#include <map>
#include <vector>
#include <sys/epoll.h>
#include "EventLoop.h"
#include "Channel.h"

class Epoll
{
  public:
    Epoll(EventLoop *loop);
    void removeChannel(Channel *channel);
    void updateChannel(Channel *channel);
    void poll(int timeOut);

  private:
    void fillActiveChannel(int num, std::vector<Channel*> *chanbelList);
    void _update(int operation, Channel *channel);
    int epollfd_;
    std::map<int, Channel*> channels_;
    EventLoop *loop_;
    std::vector<struct epoll_event> events_;
};
#endif
