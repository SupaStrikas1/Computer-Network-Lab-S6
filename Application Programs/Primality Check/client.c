#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char input[100];

    // Create socket file descriptor
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter a number: ");
    scanf("%s", input);

    // Send the number to the server
    send(sock, input, strlen(input), 0);

    // Read the response from the server
    read(sock, buffer, 1024);

    printf("Server: %s\n", buffer);

    // Close the socket
    close(sock);

    return 0;
}