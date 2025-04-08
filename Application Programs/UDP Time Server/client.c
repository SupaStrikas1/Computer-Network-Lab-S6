#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char *request_message = "TIME_REQUEST";

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    // Send time request to server
    sendto(sockfd, request_message, strlen(request_message), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Time request sent to server.\n");

    // Receive response from server
    recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);

    printf("Current time from server: %s\n", buffer);

    close(sockfd);
    return 0;
}