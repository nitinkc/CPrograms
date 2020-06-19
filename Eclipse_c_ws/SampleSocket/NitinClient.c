/*
 * NitinClient.c
 *
 *  Created on: Aug 12, 2013
 *      Author: nitin
 */
//SERVER Socket-->Bind-->Listen-->accept-->send/recv-->shutdown-->close
//CLIENT Socket-->connect-->send/recv-->shutdown-->close

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]){
	struct sockaddr_in serverAddress;
	int sockFd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],serverAddress.sin_addr);
	serverAddress.sin_port = htons(5000);
	connect(sockFd,(struct sockFd*)&serverAddress, sizeof(serverAddress));
	char sendBuff[] = "Nitin K Chaurasia";
	write(sockFd, sendBuff, sizeof(sendBuff));
	printf(sendBuff);

	return(1);

}

