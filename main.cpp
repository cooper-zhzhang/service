#include "EventLoop.h"
#include "InetAddress.h"
#include "TcpServer.h"
#include <functional>
#include <string>
#include <set>
#include <iostream>

class chatServer
{
  public:
    chatServer(TcpServer *server):server_(server)
  {
    server_->setConnectionCallBack(std::bind(&chatServer::connection, this, std::placeholders::_1));
    server_->setMessageCallBack(std::bind(&chatServer::message, this, std::placeholders::_1, std::placeholders::_2));
  }
    void start()
    {
      server_->start();
    }

    void connection(const std::shared_ptr<TcpConnection> & ptr)
    {
      if(ptr->connected())
      {
        connections_.insert(ptr);
        
        std::cout << "size " << connections_.size() << std::endl;
        std::cout << " :" << ((ptr->clientAddres()).port());
      }
      else
      {
        connections_.erase(ptr);
        std::cout << "销毁" << std::endl;
      }
    }

    void message(const std::shared_ptr<TcpConnection>&ptr, Buffer *buffer)
    {
      std::string mes = buffer->allAsString();
      mes = std::string("other: ") + mes;

      for(auto it = connections_.begin(); it != connections_.end(); ++it)
      {
        std::cout << "send size :" << connections_.size() << std::endl;
        std::cout << mes << std::endl;
        if((*it) == ptr)
          continue;
        (*it)->send(mes);
      }
    }

  private:
    TcpServer *server_;
    std::set<std::shared_ptr<TcpConnection>> connections_;

};

int main()
{
  InetAddress addres(3000);
  EventLoop loop;
  TcpServer ser(&loop, addres, std::string("chatServer"));
  chatServer chat(&ser);
  chat.start();
  loop.run();

  return 0;

}

