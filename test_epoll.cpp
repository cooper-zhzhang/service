#include "Epoll.h"
#include "EventLoop.h"

int main()
{
  EventLoop loop;
  Epoll epoll(&loop);

  return 0;
}
