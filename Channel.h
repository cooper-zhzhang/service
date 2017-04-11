#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include "EventLoop.h"

class EventLoop;

class Channel
{
  public:
    Channel(EventLoop *loop, int fd);

    void handleEvent();

    void setReadCallBack(const std::function<void()> &callBack);
    void setWriteCallBack(const std::function<void()> &callBack);
    void setErrorCallBack(const std::function<void()> &callBack);
    void SetCloseCallBack(const std::function<void()> &callBack);

    void remove();

    int fd() const
    {
      return fd_;
    }

    void setRespondEvents(int event)
    {
      respondEvents_ = event;
    }

    int events()
    {
      return events_;
    }

    EventLoop* ownerLoop() const
    {
      return loop_;
    }

    void setStatus(int status)
    {
      status_ =  status;
    }

    int status()
    {
      return status_;
    }

    void disableReading();
    void enableReading();

    void disableWriting();
    void enableWriting();

    void disableAll();

    bool isWriting();
    bool isReading();
    bool isNonEvent()
    {
      return events_ == NONEEVENT;
    }

    static const int NEWED;
    static const int ADDED;
    static const int DELETED;

  private:

    static const int READEVENT;
    static const int WRITEEVENT;
    static const int NONEEVENT;
    void _update();

    EventLoop *loop_;

    //表示当前Channel的状态
    //-1: 初始化新的
    // 0: 已添加
    // 1：已删除
    int status_;
    // enum status_ {
    //  Snew, Sadd, Sdelete};

    const int fd_;

    //本身关注的事件
    int events_;

    //epoll 响应的事件
    int respondEvents_;

    std::function<void()> readCallBack_;
    std::function<void()> writeCallBack_;
    std::function<void()> closeCallBack_;
    std::function<void()> errorCallBack_;
    std::function<void()> eventCallBack_;
};

#endif
