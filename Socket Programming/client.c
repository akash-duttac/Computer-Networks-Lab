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

    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8000);

    char buf[MAX_MESSAGE_LENGTH];
    const char *exit_command = "exit";

    while(true){
        printf("Enter message (from client): ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0'; // Remove newline character if present

        if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("Send failed");
            continue;
        }

        if (strcmp(buf, exit_command) == 0) {
            printf("Exiting\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}