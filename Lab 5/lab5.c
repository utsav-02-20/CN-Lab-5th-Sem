    
#include <stdio.h>

int main() {
    int seq = 0;

    printf("STOP-AND-WAIT FLOW CONTROL PROTOCOL\n\n");

    for (int frame = 0; frame <= 4; frame++) {
        int attempt = 1;

        while (1) {
            printf("Sender: DATA(seq=%d), Attempt %d\n", seq, attempt);

            // Data frame lost (Frame 1)
            if (frame == 1 && attempt == 1) {
                printf("Network: DATA Lost!\n");
                printf("Sender: TIMEOUT -> Retransmitting...\n\n");
                attempt++;
                continue;
            }

            printf("Receiver: DATA(seq=%d) Received\n", seq);

            // ACK lost (Frame 2)
            if (frame == 2 && attempt == 1) {
                printf("Receiver: ACK Sent\n");
                printf("Network: ACK Lost!\n");
                printf("Sender: TIMEOUT -> Retransmitting...\n\n");
                attempt++;
                continue;
            }

            // Duplicate frame after ACK loss
            if (frame == 2 && attempt == 2) {
                printf("Receiver: Duplicate DATA Detected\n");
                printf("Receiver: ACK Re-sent\n");
            } else {
                printf("Receiver: ACK Received by Sender\n");
            }

            printf("Sender: Frame Confirmed\n\n");
            break;
        }

        seq = 1 - seq;   // Alternate sequence number (0 ↔ 1)
    }

    printf("All frames delivered successfully.\n");
    return 0;
}