#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MAX 1000

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8000);

    int num;
    const char *exit_command = "close";

    while (true)
    {
        printf("Enter a Number (type '-1' to quit) : ");
        scanf("%d", &num);
        getchar(); 

        char num_str[MAX];
        sprintf(num_str, "%d", num);

        if (sendto(sockfd, num_str, strlen(num_str), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            perror("Send failed");
            continue;
        }

        if (num == -1) 
        {
            printf("Closing. . .\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}
