#include <stdio.h>
#include <strings.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 51717

int main(int argc, char *argv[])
{		
	// create a server socket
	int serversockID = socket(AF_INET, SOCK_STREAM, 0);
	
	// bind the server socket
	struct sockaddr_in serverAddress;
	bzero((char *) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORTNO);		
	bind(serversockID, (struct sockaddr *) &serverAddress, sizeof(serverAddress)); 
	
	// listen on the server socket 
	listen(serversockID,5);
	
	// accept connections on the server socket
	struct sockaddr_in clientAddress;	
	unsigned int clientAddressLength = sizeof(clientAddress);
	int clientsockID = accept(serversockID, (struct sockaddr *) &clientAddress, &clientAddressLength);
	
	// send|receive stream on server socket
	char buffer[256];
	bzero(buffer,256);
	int n = recv(clientsockID, buffer, sizeof(buffer), 0);
	printf("%s",buffer);		
	n = send(clientsockID, "received", 8, 0);
	
	return 0;
}