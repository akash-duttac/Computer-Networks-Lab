#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Sockfd value: %d", sockfd);
    
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_address.sin_port = 8000;

    int bind_result = bind(sockfd,(struct sockaddr *)&client_address,sizeof(client_address));
    if (bind_result==0)
        printf("\nBind Successful\n");
    else
        perror("\nBind Unsuccessful\n");
    
    char buffer[100], temp[100], msg[100];
    strcpy(msg,"exit");
    bool flag = true;

    while(flag){
        printf("\nEnter message: ");
        fgets(buffer);
        strcpy(temp,buffer);

        sendto(sockfd,buf,100,0,(struct sockaddr *)&client_address,sizeof(client_address));
        int tolen = sizeof(client_address);
        recvfrom(sockfd,buf,100,0,(struct sockaddr *)&client_address,&tolen);

        if (strcmp(buf,msg)==0 || strcmp(buf,msg)==0){
            printf("\nEnding Chat\n");
            flag = false;
        }
        printf("\nMessage sent: ");
        puts(buf);
    }
return 0;
}