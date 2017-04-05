#include "InetAddress.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include "Socket.h"

using std::cout;
using std::endl;

int main()
{
  InetAddress addres(1025);
  int fd = Socket::create();
  cout << fd << endl;
  Socket::bindFdAndAddress(fd, addres);
  cout << "sucess" << endl;

  return 0;
}

