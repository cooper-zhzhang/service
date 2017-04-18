#! /usr/bin/env python

import socket, sys

port = 3000
host = sys.argv[1]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
result = s.connect((host, port))

while 1:
  filename = raw_input("raw_input: ")
  print("send " + filename)
  s.sendall(filename)
  buf = s.recv(2048)
  if not len(buf):
   break;
  print("read : " + buf);


