## 代码风格
关于代码的风格，后续的代码统一使用驼峰的风格，无论是函数名还是变量名
关于类的私有成员函数，命名统一使用下划线开头
私有变量统一使用下划线结尾


<center> <h1>连接过程</h1></center>

```sequence
EventLoop-->EventLoop:EventLoop::run()
EventLoop->Epoll:Epoll:run()
EventLoop->Channel: Channel:handleEvent()
Channel->Acceptor:Acceptor::handelRead()
Acceptor->Acceptor:Acceptor::_handleRead()
Acceptor->TcpServer:TcpServer::_newConntion()
TcpServer->TcpConnection:TcpConnection::start()
TcpConnection-->TcpConnection:TcpConnection::starRead()
TcpConnection-->TcpConnection:TcpConnection::startInLoop()
TcpConnection-->Channel:Channel::enableReading()
Channel-->Channel:Channel::_update()
Channel->EventLoop:EventLoop::updateChannel()
EventLoop->Epoll:Epoll::updateChannel()
Epoll-->Epoll:Epoll::_update()
```
<center> <h1>客户端挂起</h1></center>

```sequence
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

```sequence
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
