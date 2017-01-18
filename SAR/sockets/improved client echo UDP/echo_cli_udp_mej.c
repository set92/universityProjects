#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>	// Para la funcion 'gethostbyname'.
#include <sys/time.h>	// Para la funcion 'select'.
#include <unistd.h>

#define MAX_BUF 1024
#define PORT 50003
#define TIMER 0		// Tiempo de espera (en segundos) antes de hacer una
			//  retransmision.
#define INTENTO_MAX 3	// Numero maximo de intentos de transmision de un
			//  mensaje.

int main(int argc, char *argv[])
{
	int sock, n;
	char buf[MAX_BUF];
	struct sockaddr_in dir_serv;

	// Comprobar el paso de parametros
	if(argc != 2) {
		fprintf(stderr, "Uso: %s <NombreServidor | DireccionIPv4>\n", argv[0]);
		exit(1);
	}

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Error al crear el socket");
		exit(1);
	}

	memset(&dir_serv, 0, sizeof(dir_serv));
	dir_serv.sin_family = AF_INET;
	dir_serv.sin_port = htons(PORT);

	struct hostent *hp;
	hp = gethostbyname(argv[1]);
	memcpy(&dir_serv.sin_addr, hp->h_addr_list[0], hp->h_length);

	printf("Dirección IP: %s\n", inet_ntoa(dir_serv.sin_addr));

	if(hp == 0) {
		fprintf(stderr,"Error en la direccion IP: %s\n", argv[1]);
		exit(1);
	}

	connect(sock, (struct sockaddr *) &dir_serv, sizeof(dir_serv));

	while(fgets(buf, MAX_BUF, stdin) != NULL) {
		fd_set readfds;
		struct timeval tv;

		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
		n = sock + 1;
		tv.tv_sec = TIMER;
		tv.tv_usec = 1000;
		int cont = 0;
		int rv;
		do {
			printf("Escribiendo...\n");
			write(sock, buf, strlen(buf));
			rv = select(n, &readfds, NULL, NULL, &tv);
			if (rv == -1) {
		    	perror("select"); // error occurred in select()
			} else if (rv == 0) {
		    	printf("Timeout occurred!  No data after 1 seconds.\n");
			}

			FD_ZERO(&readfds);
			FD_SET(sock, &readfds);

			tv.tv_sec = TIMER;
			tv.tv_usec = 0;
			cont++;

		} while(rv == 0 && cont < INTENTO_MAX);

		if (cont < INTENTO_MAX) {
			int buf2 = strlen(buf);
			n = read(sock, buf, MAX_BUF);
			while(n < buf2) {
				n += n = read(sock, buf+n, MAX_BUF);
			}
		}else{
			printf("El servidor no responde\n");
			exit(1);
		}
		buf[n] = 0;

		printf("%s\n", buf);

	}
	close(sock);
	exit(0);
}
