#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Bind to the specified port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Server listening on port %s...\n", argv[1]);

    // Accept a connection
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
        perror("accept");
        exit(1);
    }

    printf("Connection established with client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    // Message exchange
    char message[1024];
    while (1) {
        memset(message, 0, sizeof(message));
        if (recv(client_socket, message, sizeof(message), 0) == -1) {
            perror("recv");
            break;
        }
        if (strcmp(message, "close\n") == 0) {
            printf("Client requested to close the connection.\n");
            break;
        }
        printf("Received from client: %s", message);

        printf("Enter a message to send to the client: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    printf("Connection closed.\n");

    return 0;
}
