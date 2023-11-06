#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include <arpa/inet.h>

#define MYPORT 1025

int main()
{
	int sockfd;
	struct sockaddr_in my_addr;
	
	sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd==-1){
        perror("socket error");
    } else { 
	    printf("\nSocket success: %d\n", sockfd);
    }
	my_addr.sin_family= AF_INET;
	my_addr.sin_port= htons(MYPORT);
	my_addr.sin_addr.s_addr= inet_addr("127.0.0.1");

	int b=bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));	
	if(b==0){
        printf("\nbind success\n");
    } else {
        perror("\nbind error\n");
    }
	close(sockfd);
	return 0;
}