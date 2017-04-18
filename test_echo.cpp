#include "TcpServer.h"
#include "TcpConnection.h"
#include "Buffer.h"
#include <memory>
#include <functional>

class EchoServer
{
  public:
    EchoServer(EventLoop *loop, 
        const InetAddress &seraddrs)
      : loop_(loop), server_(loop, seraddrs, "echo")
    {
      server_.setConnectionCallBack(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));

      server_.setMessageCallBack(std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2));
    }

    void onConnection(const std::shared_ptr<TcpConnection> &TcpConnectionPtr)
    {

    }

    void onMessage(const std::shared_ptr<TcpConnection> &conn, Buffer *buf)
    {
      std::string msg(buf->allAsString());
      conn->send(msg);
    }


  private:
    EventLoop *loop_;
    TcpServer server_;
};


int main()
{
  EventLoop loop;
  InetAddress listenAddr(3000);
  EchoServer ser(&loop, listenAddr);
  loop.run();
  return 0;
}
