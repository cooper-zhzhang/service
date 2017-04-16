#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include <atomic>
#include "EventLoop.h"
#include "InetAddress.h"
#include "Buffer.h"
#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "TcpConnection.h"
#include "Acceptor.h"

class TcpServer
{
  public:
    TcpServer(EventLoop *loop, const InetAddress &serverAddres, const std::string &name);
    ~TcpServer();
    TcpServer(const TcpServer&) = delete;
    TcpServer& operator = (const TcpServer&) = delete;

    void start();

    EventLoop* getEventLoop()
    {
      return loop_;
    }

    void setThreadNum(int num)
    {
      threadPools_->setNumbers(num);
    }

    std::string name()
    {
      return name_;
    }

    void setMessageCallBack(std::function<void(const std::shared_ptr<TcpConnection>&, Buffer*)> callBack)
    {
      messageCallback_ = callBack;
    }

    void setConnectionCallBack(std::function<void(const std::shared_ptr<TcpConnection>&)> callBack)
    {
      connectionCallBack_ = callBack;
    }

    static void defaultConnectionCallBack(const std::shared_ptr<TcpConnection>& conn)
    {
      //空的函数体
    }

    static void defaultMessageCallBack(const std::shared_ptr<TcpConnection> &cnon, Buffer *buffer)
    {
      buffer->retrieveAll();
    }

  private:
    const std::string name_;

    void _newConnection(int sockfd, const InetAddress &clientAddres);
    void _removeConnection(const std::shared_ptr<TcpConnection> &connection);
    void _removeConnectionInLoop(const std::shared_ptr<TcpConnection> &connection);
    EventLoop *loop_;
    int nextConnId_;

    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPools_;

    std::function<void (const std::shared_ptr<TcpConnection> &, Buffer*)> messageCallback_;
    std::function<void (const std::shared_ptr<TcpConnection> &)> connectionCallBack_;

    std::map<std::string, std::shared_ptr<TcpConnection>> connections_;

    //使用原子性,防止重复
    std::atomic<int> start_;

};
#endif
