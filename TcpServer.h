#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include "EventLoop.h"
#include "InetAddress.h"


class TcpServer
{
  public:
    TcpServer(EventLoop *loop, InetAddress &serverAddres, std::string name);
    ~TcpServer();
    TcpServer(const TcpServer&) = delete;
    TcpServer& operator = (const TcpServer&) = delete;

    void start();

    void setMessageCallBack(std::function<void(const TcpConnectionPtr&)> callBack)
    {
      messageCallback_ = callBack;
    }

    void setConnectionCallBack(std::function<void(const TcpConnectionPtr&)> callBack)
    {
      connectionCallBack_ = callBack;
    }

privaet:
    void newConnection(int sockfd, InetAddress &clientAddres);
    void removeConnection(const std::shared_ptr<TcpConnection> &connection);
    EventLoop *loop_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPools_;

    std::function<void (const std::shared_ptr<TcpConnection> &, Buffer*)> messageCallback_;
    std::function<void (const std::shared_ptr<TcpConnection> &)> connectionCallBack_;

    std::map<std::string, std::shared_ptr<TcpConnection>> connections_;

};
#endif
