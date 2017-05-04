#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <string.h>

using namespace std;


int main()
{

  int count = 0;
  std::string fileName = to_string(cout);
  int fd = open("1.txt", O_RDONLY);
  char data[100];
  memset(data, 0, 100);
  int num = read(fd, data, 100);
  std::cout << string(data);
  return 0;
}

