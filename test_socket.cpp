#include <iostream>
#include "Socket.h"

int main()
{
  Socket socket(Socket::create());
  std::cout << socket.socketFd();
  std::cout << std::endl;

  return 0;
}
