#! /usr/bin/env python

import socket, sys, thread

def threadFuncion(s):
  buf = s.recv(2048)
  if not len(buf):
    sys.exit(0)
  sys.stdout.write('read: '+ buf)
  sys.stdout.flush()


host = sys.argv[1]
port = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
result = s.connect((host, port))

try:
  thread.start_new_thread(threadFuncion, (s,) )
except:
  print("thread error")

while 1:
  data = sys.stdin. readlines()
  s.sendall(data)


