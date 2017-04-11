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

    static int createFd()
    {
      return socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    }

    static void bindFdAndAddress(int Fd, InetAddress serviceAddress)
    {
      struct sockaddr_in address = serviceAddress.inetAddress();

      if(-1 == ::bind(Fd, (sockaddr*)(&address), sizeof(serviceAddress.inetAddress())))
      {
        exit(-1);
      }
    }

    void listen()
    {
      int sult =::listen(socket_fd_, SOMAXCONN);
      if(sult < 0)
      {
        exit(-1);
      }
    }

    int acceptSocket(InetAddress *clientAddress)
    {
      socklen_t len = sizeof(clientAddress->inetAddress());
      ::accept4(socket_fd_, (sockaddr*)(clientAddress->inetAddressPtr()), &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    }

  private:
    int socket_fd_;
};
#endif
