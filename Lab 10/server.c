#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int main() {
    int s, c;
    struct sockaddr_in a = {0};
    char b[1024];

    s = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&a, sizeof(a));
    listen(s, 1);
    printf("Server listening on port 8080...\n");

    c = accept(s, NULL, NULL);
    if (fork() == 0) {
        while (recv(c, b, sizeof(b)-1, 0) > 0) {
            printf("Client: %s", b);
            if (strncmp(b, "exit", 4) == 0) break;
        }
        exit(0);
    }

    while (fgets(b, sizeof(b), stdin)) {
        send(c, b, strlen(b), 0);
        printf("Server (you): %s", b);
        if (strncmp(b, "exit", 4) == 0) break;
    }

    wait(NULL);
    close(c);
    close(s);
    return 0;
}