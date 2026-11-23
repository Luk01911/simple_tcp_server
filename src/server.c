#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void start_echo_server(void) {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("[ECHO SERVER] Listening on port %d...\n", PORT);

    client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("[ECHO SERVER] Client connected!\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);

        if (bytes_read <= 0) {
            printf("[ECHO SERVER] Client disconnected.\n");
            break;
        }

        printf("[RECEIVED]: %s", buffer);
        write(client_socket, buffer, bytes_read);
    }

    close(client_socket);
    close(server_fd);
}
