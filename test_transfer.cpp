#include <iostream>
#include <functional>
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
    server_->setMessageCallBack(std::bind(&Translate::message, this, std::placeholders::_1, std::placeholders::_2));
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

//        connections_.insert(std::pair<std::shared_ptr<TcpConnection>, int>(ptr, fd));
        connections_.insert(std::make_pair(ptr, fd));

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
      std::cout <<  "write data" << std::endl;
      auto it = connections_.find(ptr);
      if(it == connections_.end())
        return;

      int fd = it->second;
      std::string data = buffer->allAsString();
      write(fd, data.data(), data.size());  
    }

  private:

    TcpServer *server_;
    std::map<std::shared_ptr<TcpConnection>, int> connections_;
};

int main(int argc, char **argv)
{

  InetAddress addres(5000);
  EventLoop loop;
  TcpServer server(&loop, addres, std::string("tran"));
  Translate transerver(&server);
  transerver.start();
  loop.run();

  return 0;
}

