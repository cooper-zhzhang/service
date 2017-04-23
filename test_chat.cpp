#include "EventLoop.h"
#include "InetAddres.h"
#include "TcpServer.h"

class chatServer
{
  public:
    chatServer(TcpServer *loop):loop_(loop)
  {
    loop_->setConnectionCallBack();
    loop_->setMessageCallBack();
  }
    void start()
    {
      server_->start();
    }

    void connection(const std::shared_ptr<TcpConnection> & ptr)
    {
      if(ptr->connected())
      {
        connections_[ptr->name()] = ptr;
      }
      else
      {
        connections_.earse(ptr->name());
      }
    }
  private:
    TcpServer *server_;
    std::map<std::string, std::shared_ptr<TcpConnection>> connections_;

};

int main()
{
  InetAddres addres(4000);
  EventLoop loop;
  TcpServer(&loop, addres, std::string("chatServer"));

  return 0;

}

