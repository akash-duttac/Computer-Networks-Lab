#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MESSAGE_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <receiver_ip> <receiver_port>\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct sockaddr_in server_addr;
    char message[MAX_MESSAGE_LEN];
    socklen_t addr_len = sizeof(server_addr);

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Fill in the server's information
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(1);
    }

    while (1) {
        printf("Enter a message: ");
        fgets(message, MAX_MESSAGE_LEN, stdin);

        // Send the message to the receiver
        sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, addr_len);

        // Check if the message is "exit"
        if (strcmp(message, "exit\n") == 0) {
            printf("Sender is exiting.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
