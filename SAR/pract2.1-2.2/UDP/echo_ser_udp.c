#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUF 1024
#define PORT 50001

int main()
{
    int sock, n;
    struct sockaddr_in dir_serv, dir_cli;
    socklen_t tam_dir;
    char buf[MAX_BUF];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    dir_serv.sin_family = AF_INET;
    dir_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    dir_serv.sin_port = htons(PORT);

    bind(sock, (struct sockaddr *) &dir_serv, sizeof(dir_serv));

	while(1)
	{
        tam_dir = sizeof(dir_cli);
        n = recvfrom(sock, buf, MAX_BUF, 0, (struct sockaddr *) &dir_cli, &tam_dir);

        sendto(sock, buf, n, 0, (struct sockaddr *) &dir_cli, tam_dir);

	}
    //close(sock);
}
