#ifndef IGNOREPIPE_H
#define IGNOREPIPE_H

#include <signal.h>

class IgnorePipe
{
  public:
    IgnorePipe()
    {
      ::signal(SIGPIPE, SIG_IGN);
    }
};

#endif
