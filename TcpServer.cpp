#include "TcpServer.h"
#include "Socket.h"

TcpServer::TcpServer(EventLoop *loop, InetAddress &serverAddres, std::string name)
  :loop_(loop), name_(name), acceptor_(new Acceptor(loop, serverAddres)),
  connectionCallBack_(defaultConnectionCallBack()),
  messageCallback_(defaultMessageCallBack()),
  nextConnId_(1),
  threadPools_(new EventLoopThreadPool(loop, name))
{
  start_.store(0);
  acceptor_->newConnectionCallBack(std::bind(&TcpServer::newConnection, this, _1, _2));
}

TcpServer::~TcpServer()
{
  for(auto it = connections_.begin(); it != connections_.end(); ++it)
  {
    auto conn = it->second;
    //std::shared_ptr<Connection> conn = it->second;
    it->second.reset();
    conn->getLoop()->runInLoop(std::bind(&TcpConnection::stop, conn));
    conn->reset();
  }
}

void TcpServer::start()
{
  if(start_.load() == 0)
  {
    threadPools_->start();
    loop->runInLoop(std::bind(&Acceptor::linsten, acceptor_.get()));
  }
}

void TcpServer::_newConnection(int sockfd, InetAddress &clientAddres)
{
  EventLoop* loop = threadPools_->getNextEvent();
  std::string connName = name_ + std::to_string(++nextConnId_);

  InetAddress serAddres(Socket::getLocalAddres(sockfd));

  std::shared_ptr<TcpConnection> conn (new TcpConnection(loop, connName, sockfd, serAddres, clientAddres));

  connections_[connName] = conn;
  conn->setConnectionCallBack(connectionCallBack_);
  conn->setMessageCallBack(messageCallback_);
  conn->setCloseCallBack(std:bind(&TcpServer::_removeConnection, this, _1));
  loop->runInLoop(std::bind(&TcpConnection::start, conn));
}


void TcpServer::_removeConnection(const std::shared_ptr<TcpConnection> &connection)
{
  loop_->runInLoop(std::bind(&TcpServer::_removeConnectionInLoop, this, connection));
}

void TcpServer::_removeConnectionInLoop(const std::shared_ptr<TcpConnection> &connection)
{
  connections_.erase(conn->name());
  EventLoop *loop = conn->getLoop();
  loop->runInQueue(std::bind(&TcpConnection::stop, conn));
}


