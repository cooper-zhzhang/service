#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <string>
#include <memory>
#include "EventLoop.h"
#include "InetAddress.h"
#include "Buffer.h"
#include "Socket.h"

class TcpConnection : public enable_shared_ptr<TcpConnection>
{
  public:
    TcpConnection(EventLoop *loop, const std::string name,
        int sockfd, const InetAddress &serviceAddres,
        const InetAddress &clientAddres);

    TcpConnection(const TcpConnection&) = delete;
    TcpConnection & operator =(const TcpConnection&) = delete;

    ~TcpConnection();

    const std::string& name()
    {
      return name_;
    }

    EventLoop* getLoop()
    {
      return loop_;
    }

    const InetAddress& serviceAddres()
    {
      return serviceAddres_;
    }

    const InetAddress& clientAddres()
    {
      return clinetAddres_;
    }

    bool connected()
    {
      // TODO 添加常量
      status_ == CONNECTED;
    }

    void send(void *message, int len);
    void send(std::string &message);
    void send(Buffer *buffer);

    Buffer outputBuffer()
    {
      return outputBuffer_;
    }

    Buffer inputBuffer()
    {
      return inputBuffer_;
    }

    void setStatus(int flag)
    {
      status_ = flag;
    }

    void setConnectionCallBack(std::function<void(std::shared_ptr<TcpConnection> &ptr)> callBack)
    {
      connectionCallBack_ = callBack;
    }

    void setMessageCallBack(std::function<void(std::shared_ptr<TcpConnection> &ptr, Buffer *buffer)> callBack)
    {
      messageCallBack_ = callBack;
    }

    void setCloseCallBack(std::function<void(std::shared_ptr<TcpConnection>)> callBack)
    {
      closeCallBack_ = callBack;
    }

    void shutDown();

    const static int DISCONNECTING;
    const static int CONNECTED;
    const static int DISCONNECTED;
    const static int CONNECTED;

  private:
    void handleWrite();
    void handleRead();
    void handleClose();
    void handleError();

    void shutDowniInLoop();

    void sendInLoop(std::string &message);
    void sendInLoop(void *message, int len);

    std::function<void(std::shared_ptr<TcpConnection> &ptr)> connectionCallBack_;
    std::function<void(std::shared_ptr<TcpConnection> &ptr, Buffer *buffer)> messageCallBack_;
    //给TcpServer 使用，用于通知移除所有的TcpConnecionPtr
    std::function<void(std::shared_ptr<TcpConnection> &ptr)> closeCallBack;


    EventLoop *loop_;
    std::string name_;
    int status_;
    InetAddress serviceAddres_;
    InetAddress clinetAddres_;

    Buffer inputBuffer_;
    Buffer outputBuffer_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
};

#endif

