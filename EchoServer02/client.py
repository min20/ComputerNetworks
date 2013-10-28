# Echo client program
import socket
import time

HOST = '0.0.0.0'        # The remote host
PORT = 50007              # The same port as used by the server

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
for i in xrange(100):
  print i
  time.sleep(0.1)
s.sendall('quit')
data = s.recv(1024)
s.close()
print 'Received:', data
#print 'Received', repr(data)
