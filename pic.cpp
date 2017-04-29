#include <unistd.h>
#include <fctln.h>
#include <iostream>

int main(int argc, char **argv)
{
  int image = open(argv[1], O_RDONLY);
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in;
  sockaddr_in.sin_family = AF_INET;
  sockaddr_in.sin_addr.s_addr = (INADDR_ANY);
  sockaddr_in.sin_port = htons(3000);
  connect(fd, &sockaddr_in, sizeof(sockaddr_in));
  void buffer[100];
  int num;
  while((num = read(image, buffer, 100)) != 0)
  {
    write(fd, buffer, num);
  }
  std::cout << "write end" << std::endl;
  return 0;
}
