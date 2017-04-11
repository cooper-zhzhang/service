#include "TcpConnection.h"

const int TcpConnection::DISCONNECTING = 1;
const int TcpConnection::CONNECTED = 2;
const int TcpConnection::DISCONNECTED = 3;

TcpConnection::TcpConnection(EventLoop *loop, const string name, 
    int sockfd, const InetAddress &serviceAddres, const InetAddress clientAddres) :
  loop_(loop), name_(name), serviceAddres_(serviceAddres),
  clinetAddres_(clientAddres), status_(CONNECTED), socket_(new Socket(sockfd)),
  channel_(new Channel(loop, sockfd))
{
  channel_->setErrorCallBack(std::bind(&TcpConnection::handleError, this));
  channel_->setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
  channel_->setReadCallBack(std::bind(&TcpConnection::handleRead, this));
  channel_->setCloseCallBack(std::bind(&TcpConnection::handleClose, this));
  socket_->setKeepAlive();
  
}

void TcpConnection::handleRead()
{
  ssize_t num = inputBuffer_.readByFd(channel_.fd());
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

    if(n > 0)
    {
      outputBuffer_.retrieve(n);
    }
    if(outputBuffer_.readableBytes() == 0)
    {
      channel_.disableWriting();

      if(status_ == DISCONNECTING)
      {
        shutDownInLoop();
      }
    }
  }
}

void TcpConnection::handleClose()
{
  setStatus(DISCONNECTED);
  channel_-disableAll();

  std::shared_ptr<TcpConnection> ptr(shared_from_this());
  closeCallBack(ptr);
}

void TcpConnection::handleError()
{
  // TODO 日志
}

