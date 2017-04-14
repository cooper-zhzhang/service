fndef SOCKET_H
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
      socketFd_(fd){}
    Socket(const Socket& socket) = delete;
    Socket& operator=(const Socket& socket) =  delete;

    ~Socket()
    {
      close(socketFd_);
    }

    int socketFd()
    {
      return socketFd_;
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
      int sult =::listen(socketFd_, SOMAXCONN);
      if(sult < 0)
      {
        exit(-1);
      }
    }

    int acceptSocket(InetAddress *clientAddress)
    {
      socklen_t len = sizeof(clientAddress->inetAddress());
      ::accept4(socketFd_, (sockaddr*)(clientAddress->inetAddressPtr()), &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    }

    void setKeepAlive()
    {
      int optval = 1;
      ::setsockopt(socketFd_, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof optval));
    }

    void shutdownWrite()
    {
      ::shutdown(socketFd_, SHUT_WR);
    }
  private:
    int socketFd_;
};
#endif
