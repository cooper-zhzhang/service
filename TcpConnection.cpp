#include "TcpConnection.h"

const int TcpConnection::DISCONNECTING = 1;
const int TcpConnection::CONNECTED = 2;
const int TcpConnection::DISCONNECTED = 3;
const int TcpConnection::CONNECTING = 4;

TcpConnection::TcpConnection(EventLoop *loop, const std::string name, 
    int sockfd, const InetAddress &serviceAddres, const InetAddress &clientAddres) :
  loop_(loop), name_(name), serviceAddres_(serviceAddres),
  clinetAddres_(clientAddres), status_(CONNECTED), socket_(new Socket(sockfd)),
  channel_(new Channel(loop, sockfd)), reading_(false)
{
  channel_->setErrorCallBack(std::bind(&TcpConnection::handleError, this));
  channel_->setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
  channel_->setReadCallBack(std::bind(&TcpConnection::handleRead, this));
  channel_->setCloseCallBack(std::bind(&TcpConnection::handleClose, this));
  socket_->setKeepAlive();

}

void TcpConnection::handleRead()
{
  //num 就是read的返回值
  ssize_t num = inputBuffer_.readByFd(channel_->fd());
  if(num > 0)
  {
    messageCallBack_(shared_from_this(), &inputBuffer_);
  }
  else if(num == 0)
  {
    handleClose();
  }
  else
  {
    handleError();
  }
}

void TcpConnection::handleWrite()
{
  if(channel_->isWriting())
  {
    ssize_t num = ::write(channel_->fd(), outputBuffer_.peek(), outputBuffer_.readableBytes());

    if(num > 0)
    {
      outputBuffer_.retrieve(num);
      if(outputBuffer_.readableBytes() == 0)
      {
        channel_->disableWriting();

        if(status_ == DISCONNECTING)
        {
          // TODO 补充这个函数的定义
          shutDownInLoop();
        }
      }
    }
  }
}

void TcpConnection::handleClose()
{
  setStatus(DISCONNECTED);
  channel_->disableAll();
  //对于disableAll的处理, epoll使用的是DEL

  std::shared_ptr<TcpConnection> ptr(shared_from_this());
  //这个是用户的关闭回调，一般用于对TcpConnection的处理,或许是TcpServer定义的
  closeCallBack_(ptr);
}

void TcpConnection::handleError()
{
  // TODO 日志
}

void TcpConnection::send(void *message, int len)
{
  send(std::string(static_cast<char *>message, len));
}

void TcpConnection::send(std::string& message)
{
  if(status_ == CONNECTED)
  {
    if(loop_->isInLoopThread())
      sendInLoop(message);
    else
    {
      void (TcpConnection::*fd)(std::string &message) = &TcpConnection::sendInLoop;
      loop_->runInLoop(std::bind(fp, this, message));
    }
  }
}

void TcpConnection::sendInLoop(std::string &message)
{
  sendInLoop(static_cast<void*>(message.data()), message.size());
}

void TcpConnection::sendInLoop(void *message, int len)
{
  ssize_t num;
  size_t remaining = len;
  if(status_ == DISCONNECTED)
    return ;
  if(!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
  {
    ssize_t num = ::write(channel_->fd(), message, len);
    if(num >= 0)
    {
      remaining = len - num;
    }
    else
    {
      num = 0;
    }
  }

  if(remaining > 0)
  {
    outputBuffer_.append(static_cast<char*>(data) + num, remaining); 
    if(!channel_->isWriting())
      channel_->enableWriting();
  }
}

//其实不应该使用大写，是一个单词
void TcpConnection::shutDown()
{
  if(status_ == CONNECTED)
  {
    setStatus(DISCONNECTING);
    loop_->runInLoop(std::bind(TcpConnection::shutDownInLoop, this));
  }
}

void TcpConnection::shutDownInLoop()
{
  if(!channel_->isWriting())
    socket_->shutdownWrite();
}

void TcpConnection::send(Buffer *buffer)
{
  if(status_ == CONNECTED)
  {
    if(loop_->isInLoopThread())
    {
      sendInLoop(buffer->peek(), buffer->readableBytes());
    }
    else
    {
      void (TcpConnection::*fd)(std::string &message) = &TcpConnection::sendInLoop;
      loop_->runInLoop(std::bind(fd, this, buffer->allAsString()));
    }
  }
}

void TcpConnection::startRead()
{
  loop_->runInLoop(std::bind(TcpConnection::startInLoop, this));
}

void TcpConnection::startInLoop()
{
  if(!reading_ || !channel_->isReading())
  {
    channel_->enableReading();
    reading_ = true;
  }
}

void TcpConnection::stopRead()
{
  loop_->runInLoop(std::bind(&TcpConnection::stopReadInLoop, this));
}

void TcpConnection::stopReadInLoop()
{
  if(reading_ || channel_->isReading())
  {
    reading_ = false;
    channel_->disableReading();
  }
}

void TcpConnection::start()
{
  setStatus(CONNECTED);
  startRead();
  connectionCallBack_(shared_from_this());
}

void stop()
{
  if(status_ == CONNECTED)
  {
    setStatus(DISCONNECTED);
    channel_->disableAll();
    connectionCallBack_(shared_from_this());
  }
  channel_->remove();
}


