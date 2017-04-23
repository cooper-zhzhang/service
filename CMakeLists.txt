  cmake_minimum_required(VERSION 3.5)
  project(server C CXX)

  set(CMAKE_CXX_COMPLICE '/usr/bin/clang++')
#set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)

  set(SOURCE_FILES main.cpp Channel.cpp Channel.h EventLoop.cpp EventLoop.h Mutex.cpp Mutex.h Current.h Epoll.cpp Epoll.h Acceptor.cpp Acceptor.h InetAddress.cpp InetAddress.h Socket.h Condition.h MutexGuard.h Thread.h TcpConnection.cpp TcpConnection.h Buffer.cpp Buffer.h EventLoopThreadPool.cpp EventLoopThreadPool.h EventLoopThread.cpp EventLoopThread.h TcpServer.cpp TcpServer.h IgnorePipe.h)
  add_executable(server ${SOURCE_FILES})
  target_link_libraries(server Threads::Threads)
