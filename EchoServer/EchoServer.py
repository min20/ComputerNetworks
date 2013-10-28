# Echo server program
import socket

HOST = '10.73.43.230'        # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
while True:
	conn, addr = s.accept()
	print 'Connected by', addr
	cmd = '';
	while 1:
		data = conn.recv(1024)
		cmd += data;
		if not data: break
		conn.sendall(data)
		print data
	conn.close()
	if cmd != "quit":
		print cmd
	else:
		print "String"
		break
