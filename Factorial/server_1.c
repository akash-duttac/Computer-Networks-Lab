#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 1000

int factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8000);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    char num_str[MAX];
    const char *exit_cmd = "close";
    while (true)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        int bytes_received = recvfrom(sockfd, num_str, sizeof(num_str), 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (bytes_received == -1)
        {
            perror("Receive failed");
            continue;
        }
        num_str[bytes_received] = '\0';

        int num = atoi(num_str);

        if (num == -1) 
        {
            printf("Closing. . .\n");
            break;
        }

        int result = factorial(num);
        printf("Received Number: %d\nFactorial : %d\n", num, result);
    }
    close(sockfd);
    return 0;
}