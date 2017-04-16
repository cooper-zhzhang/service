#ifndef IGNOREPIPE_H
#define IGNOREPIPE_H

#include <signal.h>

class IgnorePipe
{
  IgnorePipe()
  {
    ::signal(SIGPIPE, SIG_IGN);
  }
};

#endif
