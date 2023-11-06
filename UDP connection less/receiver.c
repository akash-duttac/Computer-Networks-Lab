#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MESSAGE_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_port>\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char message[MAX_MESSAGE_LEN];
    socklen_t addr_len = sizeof(client_addr);

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Fill in the server's information
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified port
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    while (1) {
        // Receive a message from the sender
        int bytes_received = recvfrom(sockfd, message, MAX_MESSAGE_LEN, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_received == -1) {
            perror("recvfrom");
            exit(1);
        }

        // Null-terminate the received message
        message[bytes_received] = '\0';

        // Print the received message
        printf("Received: %s", message);

        // Check if the message is "exit"
        if (strcmp(message, "exit\n") == 0) {
            printf("Receiver is exiting.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
