#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TIMEOUT 3
#define TOTAL_PACKETS 5

int main()
{

    srand(time(0));

    int packet = 1;

    while (packet <= TOTAL_PACKETS)
    {

        printf("Sender: Sending packet %d...\n", packet);
        sleep(1);

        if (rand() % 100 < 70)
        {
            printf("Receiver: ACK for packet %d received.\n\n", packet);
            packet++;
        }
        else
        {
            printf("Receiver: ACK for packet %d lost! Retransmitting...\n\n", packet);
            sleep(TIMEOUT);
        }
    }
    
    printf("All packets sent successfully!\n");
    return 0;
}