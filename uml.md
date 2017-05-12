<center> <h1>连接过程</h1></center>

```seq

EventLoop-->EventLoop:EventLoop::run()
EventLoop->Epoll:Epoll:run()
EventLoop->Channel: Channel:handleEvent()
Channel->Acceptor:Acceptor::handelRead()
Acceptor->Acceptor:Acceptor::_handleRead()
Acceptor->TcpServer:TcpServer::_newConntion()
TcpServer->TcpConnection:TcpConnection::start()
TcpConnection-->TcpConnection:TcpConnection::starRead()
TcpConnection-->TcpConnection:TcpConnection::startInLoop()
TcpConnection->Channel:Channel::enableReading()
Channel->Channel:Channel::_update()
Channel->EventLoop:EventLoop::updateChannel()
EventLoop->Epoll:Epoll::updateChannel()
Epoll-->Epoll:Epoll::_update()
Epoll-->EventLoop:
EventLoop-->EventLoop:EventLoop::run()
```
<center> <h1>客户端挂起</h1></center>
```seq

EventLoop-->EventLoop:EventLoop::run()
EventLoop->Epoll:Epoll:poll()
Epoll-->EventLoop:
EventLoop->Channel: Channel:handleEvent()
Channel->TcpConnection:TcpConnection::handelClose()
TcpConnection->Channel:Channel::disableAll()
Channel->Channel:Channel::_update()
Channel->EventLoop:EventLoop::updateChannel()
EventLoop->Epoll:Epoll::updateChannel()
Epoll-->Epoll:Epoll::_update()
Epoll-->TcpConnection:
TcpConnection->TcpServer:TcpServer::_removeConnection()
TcpServer->TcpConnection:TcpConnection::stop
TcpConnection->Channel:Channel::remove()
Channel->EventLoop:EventLoop::removeChannel()
EventLoop->Epoll::removeChannel()
Epoll->Epoll:Epoll::uodate()
Epoll-->TcpServer::
TcpServer-->EventLoop:

```

<center> <h1>客户端关闭write操作</h1></center>
```seq

EventLoop-->EventLoop:EventLoop::run()
EventLoop->Epoll:Epoll:poll()
Epoll-->EventLoop:
EventLoop->Channel: Channel:handleEvent()
Channel->TcpConnection:TcpConnection::handleRead()
TcpConnection->TcpConnection:TcpConnection::handelClose()
TcpConnection->Channel:Channel::disableAll()
Channel->Channel:Channel::_update()
Channel->EventLoop:EventLoop::updateChannel()
EventLoop->Epoll:Epoll::updateChannel()
Epoll-->Epoll:Epoll::_update()
Epoll-->TcpConnection:
TcpConnection->TcpServer:TcpServer::_removeConnection()
TcpServer->TcpConnection:TcpConnection::stop
TcpConnection->Channel:Channel::remove()
Channel->EventLoop:EventLoop::removeChannel()
EventLoop->Epoll::removeChannel()
Epoll->Epoll:Epoll::uodate()
Epoll-->TcpServer::
TcpServer-->EventLoop:

```
