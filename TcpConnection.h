#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <string>
#include "EventLoop.h"
#include "InetAddress.h"
#include "Buffer.h"

class TcpConnection
{
  public:
    TcpConnection(EventLoop *loop, const string name,
        int sockfd, const InetAddress &serviceAddre,
        const InetAddress &clientAddre);

    TcpConnection(const TcpConnection&) = delete;
    TcpConnection & operator =(const TcpConnection&) = delete;

    ~TcpConnection();

    const string& name()
    {
      return name_;
    }

    EventLoop* getLoop()
    {
      return loop_;
    }
    const InetAddress& serviceAddres()
    {
    }

    const InetAddress& clientAddres()
    {
    }

    bool connected()
    {
      // TODO 添加常量
      status_ == CONNECTED;
    }

    void send(void *message, int len);
    void send(string &message);
    void send(Buffer *buffer);

    Buffer* outputBuffer()
    {
      return outputBuffer_;
    }

    BUffer* inputBuffer()
    {
      return inputBuffer_;
    }

    void setConnectionCallBack(std::function<void(std::shared_ptr<TcpConnection>> &ptr) callBack)
    {
      connectionCallBack_ = callBack;
    }

    void setMessageCallBack(std::function<void(std::shared_ptr<TcpConnection> &ptr, Buffer *buffer)> callBack)
    {
      messageCallBack_ = callBack;
    }

    const static int DISCONNECTING;
    const static int CONNECTED;
    const static int DISCONNECTED;

  private:
    void handleWrite();
    void handleRead();
    void handleClose();
    void handleError();

    std::function<void(std::shared_ptr<TcpConnection> &ptr)> connectionCallBack_;
    std::function<void(std::shared_ptr<TcpConnection> &ptr, Buffer *buffer)> messageCallBack_;


    EventLoop *loop_;
    string name_;
    int status_;
    InetAddress serviceAddres_;
    InetAddress clinetAddres_;

    Buffer inputBuffer_;
    Buffer outputBuffer_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
}

#endif

