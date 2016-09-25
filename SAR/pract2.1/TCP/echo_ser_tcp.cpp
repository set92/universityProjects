//
// Created by set92 on 20/09/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_BUF 1024
#define PORT 50002

int main() {
    int sock, dialogo, n;
    struct sockaddr_in dir_serv;
    char buf[MAX_BUF];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    dir_serv.sin_family = AF_INET;
    dir_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    dir_serv.sin_port = htons(PORT);

    bind(sock, (struct sockaddr *) &dir_serv, sizeof(dir_serv));

    listen(sock, 5);

    while(1) {
        dialogo = accept(sock, NULL, NULL);
        while((n = read(dialogo, buf, MAX_BUF)) > 0) {
            write(dialogo, buf, strlen(buf));

        }
        buf[n] = 0;
        close(dialogo);
    }
    close(sock);
}
