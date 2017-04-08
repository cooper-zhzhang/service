#include "Channel.h"

const int Channel::READEVENT = EPOLLIN | EPOLLPRI;
const int Channel::NONEEVENt = 0;
const int Channel::WRITEEVENT = EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd): 
  loop_(loop), fd_(fd), events_(0), status_(-1)
{
}

void Channel::setReadCallBack(std::function<void()> callBack)
{
  readCallBack_ = callBack;
}

void Channel::setWriteCallBack(std::function<void()> callBack)
{
  writeCallBack_ = callBack;
}

void Channel::setErrorCallBack(std::function<void()> callBack)
{
  errorCallBack_ = callBack;
}

void Channel::_update()
{
  loop_->updateChannel(this);
}

void Channel::remove()
{
  loop_->removeChannel(this);
}

void Channel::disableReading()
{
  events_ &= (~READEVENT); 
  _update();
}

void Channel::enableReading()
{
  events_ |= READEVENT;
  _update();
}

void Channel::disableWriting()
{
  events_ &= (~WRITEEVENT);
  _update();
}

void Channel::enableWriting()
{
  events_ |= WRITEEVENT;
  _update();
}

void disableAll()
{
  events_ &= NONEEVENt;
}

bool Channel::isWriting()
{
  return events_ & WRITEEVENT;
}

bool Channel::isReading()
{
  return events_ & READEVENT;
}

void Channel::handleEvent()
{
  if(respondEvents_ & EPOLLHUP && (!respondEvents_ & EPOLLIN))
  {
    if(errorCallBack_) errorCallBack_();
  }

  if(respondEvents_ & (EPOLLIN | EPOLLPRI | EPOLLHUP))
  {
    if(readCallBack_) readCallBack_();
  }

  if(respondEvents_ & ( EPOLLERR | EPOLLVAL))
  {
    if(errorCallBack_) errorCallBack_();
  }

  if(respondEvents_ & EPOLLOUT)
  {
    if(writeCallBack_) writeCallBack_();
  }
}


