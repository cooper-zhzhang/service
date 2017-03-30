#ifndef SOCKET_H
#define SOCKET_H
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

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
    
    int socketfd()
    {
      return socket_fd_;
    }

    static int create()
    {
      return socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    }

  private:
    int socket_fd_;
};
#endif
