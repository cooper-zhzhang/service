#include "InetAddress.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>

InetAddress::InetAddress(int port)
{
  bzero(&address_, sizeof(struct sockaddr_in));
  address_.sin_family = AF_INET;
  address_.sin_addr.s_addr = htonl(INADDR_ANY);
  address_.sin_port = htons(port);
}

sa_family_t InetAddress::family() const
{
  return address_.sin_family;
}

int InetAddress::port() const
{
  return ntohs(address_.sin_port);

}

