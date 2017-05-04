#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <error.h>

int main(int argc, char **argv)
{
  int image = open(argv[1], O_RDONLY);
  if(image == -1)
  {
    std::cout << "open error" << std::endl;
    exit(-1);
  }
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd == -1)
  {
    std::cout << "socket error" << std::endl;
    exit(-1);
  }

  struct sockaddr_in addres;
  bzero(&addres, sizeof(addres));
  addres.sin_family = AF_INET;
  addres.sin_addr.s_addr = (INADDR_ANY);
  addres.sin_port = htons(3000);

  int result = connect(fd, (sockaddr*)&addres, sizeof(addres));
  if(result == -1)
  {
    std::cout << "connect error" << std::endl;
    std::cout << error << std::endl;
  }

  char buffer[100];
  int num;
  while((num = read(image, buffer, 100)) != 0)
  {
    write(fd, buffer, num);
  }
  std::cout << "write end" << std::endl;
  return 0;
}
