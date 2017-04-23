#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <string>
#include <memory>
#include "EventLoop.h"
#include "InetAddress.h"
#include "Buffer.h"
#include "Socket.h"

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
  public:
    TcpConnection(EventLoop *loop, const std::string name,
        int sockfd, const InetAddress &serviceAddres,
        const InetAddress &clientAddres);

    TcpConnection(const TcpConnection&) = delete;
    TcpConnection & operator =(const TcpConnection&) = delete;

    ~TcpConnection() = default;

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
      return status_ == CONNECTED;
    }

    void send(void *message, int len);
    void send(const std::string &message);
    void send(Buffer *buffer);

    Buffer* outputBuffer()
    {
      return &outputBuffer_;
    }

    Buffer* inputBuffer()
    {
      return &inputBuffer_;
    }

    void setStatus(int flag)
    {
      status_ = flag;
    }

    void setConnectionCallBack(std::function<void(const std::shared_ptr<TcpConnection> &ptr)> callBack)
    {
      //TcpConnection 开始或者结束都要运行这个函数
      // 这个函数是由业务层指定的，在TcpConnection 中的stop() 函数中调用一次
      //在TcpServer 的_newConnection() 中调用一次
      connectionCallBack_ = callBack;
    }

    void setMessageCallBack(std::function<void(const std::shared_ptr<TcpConnection> &ptr, Buffer *buffer)> callBack)
    {
      messageCallBack_ = callBack;
    }

    void setCloseCallBack(std::function<void(std::shared_ptr<TcpConnection>)> callBack)
    {
      closeCallBack_ = callBack;
    }

    void shutDown();

    void startRead();
    void stopRead();

    void start();
    void stop();

    const static int DISCONNECTING;
    const static int CONNECTED;
    const static int DISCONNECTED;
    const static int CONNECTING;

  private:
    void handleWrite();
    void handleRead();
    void handleClose();
    void handleError();

    void shutDownInLoop();

    void sendInLoop(const std::string &message);
    void sendInLoop(const void *message, int len);

    void startInLoop();
    void stopReadInLoop();

    std::function<void(const std::shared_ptr<TcpConnection> &ptr)> connectionCallBack_;
    std::function<void(const std::shared_ptr<TcpConnection> &ptr, Buffer *buffer)> messageCallBack_;
    //给TcpServer 使用，用于通知移除所有的TcpConnecionPtr
    std::function<void(std::shared_ptr<TcpConnection> &ptr)> closeCallBack_;


    EventLoop *loop_;
    std::string name_;
    int status_;
    InetAddress serviceAddres_;
    InetAddress clinetAddres_;

    Buffer inputBuffer_;
    Buffer outputBuffer_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    bool reading_;
};

#endif

