#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
int main()
{
int sockfd, i, j, flag = 0;
char buf1[100], buf2[100], mes[100];
struct sockaddr_in server_addr, client_addr1, client_addr2;

sockfd=socket(AF_INET,SOCK_DGRAM,0);

 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=INADDR_ANY;
 server_addr.sin_port=6000;

   i=bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
 printf("test %d%d\n", sockfd, i);
 
 for(i=0; i < 100; i++) 
	{
		buf1[i] ='\0';
		buf2[i] = '\0';
		mes[i] ='\0';
	}
	strcpy(mes,"exit");

	while(flag == 0)
	{
		for(i=0; i < 100; i++){
			buf1[i] = '\0';
			buf2[i] = '\0';
		}
		
		// Receive a message from client
		int s1=sizeof(client_addr1);
		recvfrom(sockfd, buf1, 100, 0, (struct sockaddr *)&client_addr1, &s1);
		int s2=sizeof(client_addr2);
		recvfrom(sockfd, buf2, 100, 0, (struct sockaddr *)&client_addr2, &s2);
		printf("Client 1 sent: %s\n", buf1);
		printf("Client 2 sent: %s\n", buf2);
			
		//Sending message to the client	
		sendto(sockfd, buf2, 100, 0, (struct sockaddr *)&client_addr1, sizeof(client_addr1));
		sendto(sockfd, buf1, 100, 0, (struct sockaddr *)&client_addr2, sizeof(client_addr2));
		
		if((strcmp(buf1, mes) == 0) || (strcmp(buf2, mes) == 0))
		{
		 	flag = 1;
		 	break;
		}
		
	}

close(sockfd);

 }