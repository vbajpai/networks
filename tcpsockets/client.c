#include <stdio.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define PORTNO 51717
#define HOSTNAME "localhost"

int main(int argc, char *argv[])
{
    // create a client socket 
    int clientsockID = socket(AF_INET, SOCK_STREAM, 0);
	
    // connect to server address
	
		// fetch server hostent structure from hostname
		struct hostent *serverHostent = gethostbyname(HOSTNAME);

		// prepare the serverAddress
		struct sockaddr_in serverAddress;	
		bzero((char *) &serverAddress, sizeof(serverAddress));
		serverAddress.sin_family = AF_INET;
		bcopy((char *)serverHostent->h_addr, (char *)&serverAddress.sin_addr.s_addr, serverHostent->h_length);
		serverAddress.sin_port = htons(PORTNO);
	
	connect(clientsockID,(struct sockaddr *) &serverAddress,sizeof(serverAddress));

	// send|receive stream on client socket 
    printf("Please enter the message: ");
	char buffer[256];
    bzero(buffer,256);
    fgets(buffer,255,stdin);	
	int n = send(clientsockID, buffer, sizeof(buffer), 0);
    bzero(buffer,256);
	n = recv(clientsockID, buffer, sizeof(buffer), 0);    
    printf("%s\n",buffer);
    return 0;
}