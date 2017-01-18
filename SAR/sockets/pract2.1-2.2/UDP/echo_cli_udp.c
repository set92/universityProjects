#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUF 1024
#define PORT 50001

int main(int argc, char *argv[])
{
	// Comprobar el paso de parametros
	if(argc != 2)
	{
		fprintf(stderr, "Uso: %s <DireccionIPv4>\n", argv[0]);
		exit(1);
	}

    int sock, n;
    char buf[MAX_BUF];
    struct sockaddr_in dir_serv;

    //Crear socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    dir_serv.sin_family = AF_INET;
    dir_serv.sin_port = htons(PORT);
    inet_aton(argv[1], &dir_serv.sin_addr);

    while(fgets(buf, MAX_BUF, stdin) != NULL)
	{
        sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &dir_serv, sizeof(dir_serv));

        n = recvfrom(sock, buf, MAX_BUF, 0, NULL, NULL);

        buf[n] = 0;

        printf("%s",buf);
	}
    close(sock);

}
