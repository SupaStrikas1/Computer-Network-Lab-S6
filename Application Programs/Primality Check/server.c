#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PORT 8080

bool is_prime(int num)
{
    if (num <= 1)
        return false;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char response[1024];

    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen for incoming connections
    listen(server_fd, 3);

    printf("Server is listening on port %d...\n", PORT);

    // Accept a connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    // Read data from the client
    read(new_socket, buffer, 1024);
    int number = atoi(buffer);

    // Determine if the number is prime
    if (is_prime(number))
    {
        snprintf(response, sizeof(response), "%d is a prime number.", number);
    }
    else
    {
        snprintf(response, sizeof(response), "%d is not a prime number.", number);
    }

    // Send the response back to the client
    send(new_socket, response, strlen(response), 0);

    printf("Processed request for number: %d\n", number);

    // Close the sockets
    close(new_socket);
    close(server_fd);

    return 0;
}
