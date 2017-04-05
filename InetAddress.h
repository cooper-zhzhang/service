#ifndef INETADDRESS_H
#define INETADDRESS_H
#include <netinet/in.h>

class InetAddress
{
  public:
    InetAddress(const struct sockaddr_in &address) : address_(address)
  {}
    InetAddress(int port);
    sa_family_t family() const;
    int port() const; 

    struct sockaddr_in inetAddress() 
    {
      return address_;
    }

  private:
    struct sockaddr_in address_;
};

#endif 
