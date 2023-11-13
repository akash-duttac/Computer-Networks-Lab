#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port_number>\n", argv[0]);
        exit(1);
    }

    int client_socket;
    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2])); // Port number from command-line argument
    server_addr.sin_addr.s_addr = inet_addr(argv[1]); // Server IP address from command-line argument

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to the server.\n");

    char buffer[BUFFER_SIZE];

    // Send the first message
    printf("Client 1 (You): ");
    fgets(buffer, BUFFER_SIZE, stdin);
    send(client_socket, buffer, strlen(buffer), 0);

    while (1) {
        // Receive messages
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            // Server has closed the connection
            printf("Server closed the connection. Exiting...\n");
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Received from Server: %s", buffer);

        // Send a message
        printf("Client 1 (You): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(client_socket, buffer, strlen(buffer), 0);

        // Check if the client wants to close the socket
        if (strcmp(buffer, "exit\n") == 0) {
            printf("You closed the connection. Exiting...\n");
            break;
        }
    }

    // Close the client socket
    close(client_socket);

    return 0;
}