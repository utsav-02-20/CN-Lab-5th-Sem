#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in a = {0};
    char b[1024];

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &a.sin_addr);

    connect(s, (struct sockaddr *)&a, sizeof(a));
    printf("Connected to server.\n");

    if (fork() == 0) {
        while (recv(s, b, sizeof(b)-1, 0) > 0) {
            printf("Server: %s", b);
            if (strncmp(b, "exit", 4) == 0) break;
        }
        exit(0);
    }

    while (fgets(b, sizeof(b), stdin)) {
        send(s, b, strlen(b), 0);
        printf("Client (you): %s", b);
        if (strncmp(b, "exit", 4) == 0) break;
    }

    close(s);
    return 0;
}