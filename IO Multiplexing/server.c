#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>

#define PORT 12345
#define MAX_CLIENTS 30

int main() {
    int server_socket, client_socket[MAX_CLIENTS], activity, max_sd, sd;
    int max_clients = MAX_CLIENTS;
    fd_set readfds;
    
    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Initialize server address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    
    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    // Accept the incoming connections
    int addrlen = sizeof(server_address);
    char buffer[1024];
    char *exit_msg = "exit";    
    
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;
        
        // Add child sockets to set
        for (int i = 0; i < max_clients; i++) {
            sd = client_socket[i];
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }
            if (sd > max_sd) {
                max_sd = sd;
            }
        }
        
        // Wait for an activity on one of the sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        
        if (FD_ISSET(server_socket, &readfds)) {
            // Handle new incoming connection
            int new_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t*)&addrlen);
            if (new_socket < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }
            
            // Add new socket to the array of client sockets
            for (int i = 0; i < max_clients; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }
        
        // Handle data from clients
        for (int i = 0; i < max_clients; i++) {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds)) {
                int valread = read(sd, buffer, sizeof(buffer));
                if (valread == 0) {
                    // Client disconnected
                    close(sd);
                    client_socket[i] = 0;
                } else {
                    // Check for exit message
                    if (strncmp(buffer, exit_msg, strlen(exit_msg)) == 0) {
                        // Terminate the respective connection
                        close(sd);
                        client_socket[i] = 0;
                    } else {
                        // Handle other messages from clients
                        // Do something with the received message (e.g., broadcast to other clients)
                    }
                }
            }
        }
    }
    
    return 0;
}
