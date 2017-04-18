#ifndef EPOLL_H
#define EPOLL_H

#include <sys/eventfd.h>
#include <map>
#include <vector>
#include <sys/epoll.h>
#include "EventLoop.h"
#include "Channel.h"
class Channel;
class EventLoop;

class Epoll
{
  public:
    Epoll(EventLoop *loop);
    ~Epoll();
    void removeChannel(Channel *channel);
    void updateChannel(Channel *channel);
    void poll(int timeOut, std::vector<Channel*> *channelList);

    static int createEventFd()
    {
      int eventFd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
      if(eventFd < 0)
      {
        exit(-1);
      }

      return eventFd;
    }

    static Epoll* newEpoll(EventLoop *loop)
    {
      return new Epoll(loop);
    }

    static const int INITVECTORSIZE;

  private:
    void fillActiveChannel(int num, std::vector<Channel*> *chanbelList);
    void _update(int operation, Channel *channel);
    int epollfd_;
    std::map<int, Channel*> channels_;
    EventLoop *loop_;
    std::vector<struct epoll_event> events_;
};
#endif
