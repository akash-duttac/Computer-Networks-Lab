#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(1);
    }

    int client_socket;
    struct sockaddr_in server_addr;

    // Create a socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
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

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected to server %s:%s\n", argv[1], argv[2]);

    // Message exchange
    char message[1024];
    while (1) {
        printf("Enter a message to send to the server: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        memset(message, 0, sizeof(message));
        if (recv(client_socket, message, sizeof(message), 0) == -1) {
            perror("recv");
            break;
        }
        if (strcmp(message, "close") == 0) {
            printf("Server requested to close the connection.\n");
            break;
        }
        printf("Received from server: %s", message);
    }

    // Close the socket
    close(client_socket);

    printf("Connection closed.\n");

    return 0;
}
