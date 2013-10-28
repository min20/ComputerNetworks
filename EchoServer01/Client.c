#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;

	struct sockaddr_in serv_addr;
	struct hostent *server;

	portno = 50007;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname("10.73.43.58");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((void *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);

	serv_addr.sin_port = htons(portno);
	if (connect (sockfd, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0) 
	error("ERROR connecting");

	while(1) {
		char buffer[256] = {};
		char input[256] = {};
		scanf("%s", input);
		bzero(buffer, 256);
		strcpy(buffer, input);
		n = write(sockfd, buffer, strlen(buffer));

		if (n < 0) 
			error("ERROR writing to socket");

		bzero(buffer,256);
		n = read(sockfd,buffer,255);

		if (n < 0) 
			error("ERROR reading from socket");
	//	printf("%s\n",buffer);
	}

	return 0;
}
