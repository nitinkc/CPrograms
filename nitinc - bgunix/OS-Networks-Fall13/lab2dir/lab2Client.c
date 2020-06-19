#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	int sock,n,m;
	struct sockaddr_in sin;
	struct hostent *hp;
	char exit_msg[256];
	int received_int = 0;
	char name[100]; //Name limit: 100 characters
	
	bzero(name,100);
	bzero(exit_msg,256);

	if(argc < 2){
		printf("%s input error, enter host and port number\n",argv[0]);/* input error; need port number */
		return -1;
	}

	//CREATE SOCKET
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket failed");
		close(sock);
		exit(1);
	}

	// fill-in address information
	sin.sin_family = AF_INET; //set protocoal family to internet
	sin.sin_port = htons(atoi(argv[2])); //set prot number
	hp = gethostbyname(argv[1]); //set the ip address as bgunix
	if (hp == 0){
		perror("get hostbyname failed");
		close(sock);
		exit(1);
	}
	//copy the address by gethostname into sin address
	memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);

	/* CONNECT */
	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0){
		perror("Connect failed");
		close(sock);
		exit(1);
	}

	scanf("%[^\t\n]s", name); //wild characters to accept the blank space separated stings
	//fgets(name,sizeof(name),stdin);
	if(write(sock, name, sizeof(name)) < 0){
				perror("send failed");
				exit(1);
			}
	// receive it
	if (read(sock, &received_int, sizeof(received_int)) > 0) {
	printf("Received ACK = %d\n", ntohl(received_int)); //network to host long
	}
	else{
		printf("error in receiving ACK");
		}
	close(sock);
	system("pkill -9 -f Server");
return 0;
}
