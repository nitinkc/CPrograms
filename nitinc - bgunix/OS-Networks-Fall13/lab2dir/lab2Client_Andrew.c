#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main( int argc, char *argv[] )
{
	/* Variable Declaration */
    int sockfd, n;
    char buffer[256];
    struct sockaddr_in sa;
    struct hostent *server;
	
	/* Create Socket; First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //sockfd is File descriptor of IP Socket of TCP Type
    if (sockfd < 0) 
    {
        perror("Socket creation failed:ERROR opening socket");
        exit(1);
    }
	
	/******************************************************************************/
	sa.sin_family = AF_INET;		//socket internet(in)
	sa.sin_port = htons(argv[2]);	//Port Number

	server = gethostbyname(argv[1]);
	memcpy(&sa.sin_addr,server->h_addr,sizeof(server->h_length));


	/*****************************************************************************/
	if (connect(sockfd, (struct sockaddr *)&sa, sizeof(sa)) < 0)
	{
		perror("ERROR Connecting");
		exit(1);

	}
	else
	{
		fgets(buffer,sizeof(buffer),stdin);
		n = write(sockfd,buffer,sizeof(buffer));
		if (n < 0)
		{
			perror("ERROR writing to socket");
			exit(1);
		}
		n = read(sockfd,buffer,sizeof(buffer));
		if (n < 0)
		{
			perror("ERROR reading from socket");
			exit(1);
		}
		printf("Received ACK = %s \n",ntohl(buffer));
        
		close(sockfd);
        exit(0);
    }

}
