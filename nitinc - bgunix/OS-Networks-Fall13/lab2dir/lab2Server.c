#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 12345
#define STUDENTS 72

void calcRand (int sock)
{
    int n, ranVal;
    char h;
    char buffer[256];
    n = read(sock,buffer,255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }
    printf("Hello,%s ! You have successfully executed The Client Program\n",buffer);
    n = write(sock,buffer,sizeof(buffer));
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    srand(45665);
    ranVal = random() % 1000;
    sleep(3);
	int converted_number = htonl(ranVal); //host to network long
        if (write(sock,&converted_number,sizeof(converted_number)) < 0)
        {
            perror("ERROR writing to socket");
            exit(1);
        }
}
//===== Main program =====
int main( int argc, char *argv[] )
{
	/* Variable Declaration */
    int sockfd, newsockfd, portno, cli_len;
    char buffer[256];
    pid_t pid;
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* Create Socket; First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //sockfd is File descriptor of IP Socket of TCP Type
    if (sockfd < 0) 
    {
        perror("Socket creation failed:ERROR opening socket");
        exit(1);
    }
    /* fill-in address information, and then bind it; Initialize socket structure */
    serv_addr.sin_family = AF_INET;//socket internet(in)
    serv_addr.sin_addr.s_addr = INADDR_ANY;//"bgunix.bgsu.edu" INADDR_ANY
    serv_addr.sin_port = htons(PORTNO);
 
    // Now bind the host address using bind() call;
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
         perror("Bind Failure,ERROR on binding");
         exit(1);
    }
    //  Start listening for the clients

    listen(sockfd,STUDENTS);
    cli_len = sizeof(cli_addr);
    printf(" ********************The server is ready**********************\n");
    /* The infinite loop */
    while (1) 
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
        if (newsockfd < 0)
        {
            perror("unable to create Socket, ERROR on accept");
            exit(1);
        }

        pid = fork();
        if (pid < 0)
        {
            perror("ERROR on fork");
	    exit(1);
        }
        if (pid == 0)  
        {
            /* This is the client process */
           close(sockfd);
           printf("Welcome, Please enter your name\n");
           /* CHECK POINT FOR TESTING: inform ME of socket number - used in send and receive */
            calcRand(newsockfd);
            close(newsockfd);
            exit(0);
        }
    } /* end of while */
}
