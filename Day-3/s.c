#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
int main()
{
  int i,j,sockfd, flag = 0;
  char buf[100], buf1[100], mes[100];
  struct sockaddr_in client_addr;

  sockfd=socket(AF_INET,SOCK_DGRAM,0);

  client_addr.sin_family=AF_INET;
  client_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); 
  client_addr.sin_port=6000;

  i=bind(sockfd,(struct sockaddr *)&client_addr, sizeof(client_addr));
  
  
	for(i=0; i < 100; i++)
	{ 	buf[i] = '\0'; 
		buf1[i] = '\0';
		mes[i]='\0';
	}
	strcpy(mes,"exit");

	while(flag == 0)
	{
		for(i=0; i < 100; i++) buf[i] = '\0';
		printf("\nString: ");
		scanf("%s", buf);
		strcpy(buf1, buf);
		// Send to server  
		sendto(sockfd, buf, 100, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
		
		for(i=0; i < 100; i++) buf[i] = '\0';
		int s=sizeof(client_addr);
		// Receive a reply from the server
		recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&client_addr, &s);
		if(strcmp(buf, mes) == 0 || strcmp(buf1, mes) == 0)
		{
			flag = 1;
			break;
		}
		printf("Server sent (of client 1): %s\n", buf);
	}
  
  /*for(i=0; i < 100; i++) buf[i] = '\0';
	strcpy(buf,"Message from client");
	sendto(sockfd, buf, 100, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));

	int s=sizeof(client_addr);
		for(i=0; i < 100; i++) buf[i] = '\0';
			recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&client_addr, &s);
			printf("%s\n", buf);
			printf("Got packet from %s", inet_ntoa(client_addr.sin_addr));*/
	
close(sockfd);
return 0;
}