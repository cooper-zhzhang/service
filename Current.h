#ifndef CURRENT_H
#define CURRENT_H

#include <sys/syscall.h>
#include <unistd.h>

class Current
{
  public:

  static pid_t tid()
  {
    return syscall(SYS_gettid);
  }

};

#endif
