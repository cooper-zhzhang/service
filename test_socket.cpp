#include <iostream>
#include "Socket.h"

int main()
{
  Socket socket(Socket::createFd());
  std::cout << socket.socketFd();
  std::cout << std::endl;

  return 0;
}
