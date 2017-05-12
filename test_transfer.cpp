#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include "TcpServer.h"
#include "EventLoop.h"
#include "InetAddress.h"

class Translate
{
  public:
    Translate(TcpServer *server):server_(server)
  {
    server_->setConnectionCallBack(std::bind(&Translate::connection, this, std::placeholders::_1));
    server_->setMessageCallBack(std::bind(&Translate::message, this, std::placeholder::_1, std::placeholders::_2));
  }

    void start()
    {
      server_->start();
    }
    void connection(const std::shared_ptr<TcpConnection> & ptr)
    {
      if(ptr->connected())
      {
        int fd;

        if ((fd = open(ptr->name().c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
        {
          ptr->stop();
          return;
        }

        connections_.insert(std::pair(ptr, fd));

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

    }

  private:

    TcpServer *server_;
    std::map<std::shared_ptr<TcpConnection>, int> connections_;
};

int main(int argc, char **argv)
{

  InetAddress addres(5000);
  EventLoop loop;

  return 0;
}

