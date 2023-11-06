#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char message[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send and receive messages
    printf("Connected to the server. Type 'exit' to quit.\n");
    while (1) {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        // Send the message to the server
        if (send(client_socket, message, strlen(message), 0) == -1) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        // Receive a response from the server
        if (recv(client_socket, message, sizeof(message), 0) == 0) {
            printf("Server disconnected.\n");
            break;
        }

        // Check if the server wants to terminate the connection
        if (strncmp(message, "exit", 4) == 0) {
            printf("Server has terminated the connection.\n");
            break;
        }

        // Display server's response
        printf("Server: %s", message);
    }

    // Close the socket
    close(client_socket);
    return 0;
}
