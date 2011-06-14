#include <stdio.h>
#include <strings.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 51717

int main(int argc, char *argv[])
{		
	// create a server socket
	int serversockID = socket(AF_INET, SOCK_DGRAM, 0);
	
	// bind the server socket
	struct sockaddr_in serverAddress;
	bzero((char *) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORTNO);		
	bind(serversockID, (struct sockaddr *) &serverAddress, sizeof(serverAddress)); 
	
	// receive datagram from client
	char buffer[256];
	bzero(buffer,256);	
	struct sockaddr_in clientAddress;	
	unsigned int clientAddressLength = sizeof(clientAddress);
	recvfrom(serversockID, buffer, sizeof(buffer), 0 , (struct sockaddr *) &clientAddress, &clientAddressLength);
	
	// process the received datagram
	printf("%s",buffer);		
	
	// send datagram to client	
	int flag = sendto(serversockID, "received", 8, 0, (struct sockaddr *) &clientAddress, clientAddressLength);

	return 0;
}