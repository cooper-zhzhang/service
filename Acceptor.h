#ifndef ACCETPOR_H
#define ACCETPOR_H
#include "EventLoop.h"

class EventLoop;
class InetAddress;

class Acceptor
{
  public:
    Acceptor(EventLoop *loop, InetAddress inetAddress);
    ~Acceptor();
    Acceptor(const Acceptor &) = delete;
    Acceptor& operator = (const Acceptor&) = delete;

    void listen();
    void newConnectionCallBack(const std::function<void(int, InetAddress)> callBack)
    {
      newConnectionCallBack_ = callBack;
    }

  private:
    void handleRead();
    EventLoop* loop_;
    Socket serviceSocket_;
    Channel serviceChannel_;
    std::function<void (int socketFd, InetAddress& clientInetAddress)> newConnectionCallBack_;

};
#endif
