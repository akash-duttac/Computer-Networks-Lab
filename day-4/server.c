#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX 1000

int main(){
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd == -1){
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8000);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Bind failed\n");
        exit(EXIT_FAILURE);
    }

    char buf[MAX];
    const char *exit_cmd = "exit";

    while(true){
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        int bytes_received = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (bytes_received == -1) {
            perror("Receive failed");
            continue;
        }

        buf[bytes_received] = '\0'; // Null-terminate the received message

        printf("Message from client: %s\n", buf);

        if (strcmp(buf, exit_command) == 0) {
            printf("Exiting\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}