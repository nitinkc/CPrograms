/*
	This is the server driver program

	Usage: $ pname
	Given that the program has been named pname
	Prints the port number the server is listening at
	Waits for connections from client to this PortNumber

	Message from client is printed and user is prompted
	for a response.

	To compile

		% gcc -lxnet lineserv.c -o pname

	Two copies may be linked with

		% mkfifo fi
		% pname < fi | pname > fi &

	Caution: strict alternation is required 
		 [ needs call to select(...) to fix ]
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>

#define ERROR -1
#define OK 0
#define backlog 5
#define STDIN 0
#define STDOUT 1

int buildServer(int socketNO, int portNO)
{
 struct sockaddr_in socketAddr;
 struct hostent *hp;
 char hostName[33];
 int lengthOfStruct;


 gethostname(hostName, 32);
 if ((hp = gethostbyname(hostName)) == NULL)  {
        fprintf(stderr,"%s: no such host ?\n",hostName);
        exit(1);
 }

 else {
        fprintf(stderr, "hostname is  %s\n",hp->h_name);

        socketAddr.sin_family = AF_INET;
        socketAddr.sin_port =  portNO;
        socketAddr.sin_addr.s_addr = INADDR_ANY;


 if (bind (socketNO, (struct sockaddr *) &socketAddr,sizeof(socketAddr))<0){
        perror("bind");
        exit(1);
 }

 lengthOfStruct = sizeof (socketAddr);
 if (getsockname(socketNO,( struct sockaddr *)&socketAddr,&lengthOfStruct)) {
    perror("getting socket name");
    exit(1);
 }

 fprintf(stderr, "socket has port #%d\n",ntohs(socketAddr.sin_port));
 }
 return (OK);
}


int  matchWithClient (int socketNO)
{
 struct sockaddr_in fullSocketAddr;
 int lengthOfStruct, connNO;

 lengthOfStruct = sizeof (fullSocketAddr);
 if ((connNO = accept
        (socketNO,(struct sockaddr *)&fullSocketAddr,&lengthOfStruct))<0)  {
      perror("accept");
      exit(1);
 }
 return (connNO);
}

main (int argc, char * argv[]) {
 int i,length;
 int socketNO, connNO;
 int PortNo = 0;
 char FromClient[BUFSIZ];
 char ToClient[BUFSIZ];

 if ((socketNO = socket(AF_INET,SOCK_STREAM,0)) < 0) {
   perror("socket");
   exit(1);
 };

 if (argc==2) PortNo = htons(atoi(argv[1]));

 if ( buildServer(socketNO, PortNo) < 0 ) {
	perror (" build server problem \n");
	exit(1);
 };

 listen(socketNO,backlog);  
 if ((connNO = matchWithClient (socketNO) ) < 0  ) {
      perror("accept");
      exit(1);
 };

 for (;;) {
   if ((i = read(connNO,FromClient,BUFSIZ)) > 0)  {
        FromClient[i] = 0;
        if(isatty(STDIN)) printf("Client Says> ");
	printf("%s", FromClient); fflush(stdout);
	if('\n'!=FromClient[i-1] && isatty(STDIN)) printf("\n");
	if(isatty(STDOUT)) printf("Response Is> ");
        fgets(ToClient, BUFSIZ, stdin);
   } else { perror("Nothing received from client\n");
            exit(1);
   };

   if (write(connNO,ToClient,strlen(ToClient)) < 0) {
      perror ("server unable to send to client\n");
      exit (1);
   };
   if(isatty(STDIN)) printf("\n");
 } 
 exit (0);   /* never reach here */
}