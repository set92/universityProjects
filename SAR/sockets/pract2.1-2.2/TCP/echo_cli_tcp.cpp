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
#include <arpa/inet.h>

#define MAX_BUF 1024
#define PORT 50002

int main(int argc, char *argv[]) {
    // Comprobar el paso de parametros
    if(argc != 2) {
        fprintf(stderr, "Uso: %s <DireccionIPv4>\n", argv[0]);
        exit(1);
    }

    int sock, n;
    char buf[MAX_BUF];
    struct sockaddr_in dir_serv;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    dir_serv.sin_family = AF_INET;
    dir_serv.sin_port = htons(PORT);
    inet_aton(argv[1],&dir_serv.sin_addr);

    connect(sock, (struct sockaddr *) &dir_serv, sizeof(dir_serv));

    while(fgets(buf, MAX_BUF, stdin) != NULL) {
        write(sock, buf, strlen(buf));
        int buf2 = strlen(buf);
        n = read(sock, buf, MAX_BUF);
        while(n < buf2) {
            n += n = read(sock, buf+n, MAX_BUF);
        }
        buf[n] = 0;
        printf("%s", buf);
    }
    close(sock);
}
/*
    Leer de la entrada estandar hasta leer EOF o encontrar algun error.
    Lo leido sera guardado en la variable 'buf' y contendra el caracter
    de fin de string.
    ¿Que ocurrira si la linea leida tiene mas caracteres que la
    capacidad del buffer, MAX_BUF? Pon un valor mas pequeño para
    MAX_BUF y haz la prueba.
*/
