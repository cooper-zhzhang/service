#include "Acceptor.h"
#include "InetAddress.h"

int main()
{
  EventLoop loop;
  InetAddress addr(2008);
  Acceptor acceptot(&loop, addr);
  acceptot.listen();
  while(1)
  {
  }

  return 0;
}
