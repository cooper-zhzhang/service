#ifndef INETADDRESS_H
#define INETADDRESS_H

class InetAddress
{
  InetAddress(const struct sockaddr_in &address) : address_(address)
  {}
  InetAddress(int port, bool anyAddress);

  private:
    sockaddr_in address_;
};

#endif 
