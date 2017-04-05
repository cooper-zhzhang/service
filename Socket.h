#ifndef SOCKET_H
#define SOCKET_H
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "InetAddress.h"
#include <netinet/in.h>

class Socket
{
  public:
    Socket(int fd):
      socket_fd_(fd){}
    Socket(const Socket& socket) = delete;
    Socket& operator=(const Socket& socket) =  delete;

    ~Socket()
    {
      close(socket_fd_);
    }
    
    int socketFd()
    {
      return socket_fd_;
    }

    static int create()
    {
      return socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    }

    static void bindFdAndAddress(int Fd, InetAddress serviceAddress)
    {
      //TODO 完善InetAddress 类后在来添加这个函数
      struct sockaddr_in address = serviceAddress.inetAddress();

      if(-1 == ::bind(Fd, (sockaddr*)(&address), sizeof(serviceAddress.inetAddress())))
      {
        exit(-1);
      }
    }

    void listen();
    int acceptSocket(InetAddress clientAddress);

  private:
    int socket_fd_;
};
#endif
