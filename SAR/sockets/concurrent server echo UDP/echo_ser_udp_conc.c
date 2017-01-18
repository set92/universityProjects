#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>	// Para la funcion 'select'
#include <signal.h>	// Para la funcion 'signal'

#define MAX_BUF 1024
#define PORT 50005
#define MAX_WAIT 120	// Tiempo maximo de espera

/*
	NOTA:
	Los numeros (entre parentesis) de los comentarios identifican distintos
	 ejercicios. Se recomienda realizar los distintos ejercicios de uno en
	 uno, probando su correcto funcionamiento antes de pasar al siguiente.
*/

int main()
{
	int sock, n;
	struct sockaddr_in dir_serv, dir_cli;
	socklen_t tam_dir;
	char buf[MAX_BUF];

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error al crear el socket");
		exit(1);
	}

	memset(&dir_serv, 0, sizeof(dir_serv));
	dir_serv.sin_family = AF_INET;
	dir_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	dir_serv.sin_port = htons(PORT);

	if(bind(sock, (struct sockaddr *) &dir_serv, sizeof(dir_serv)) < 0)
	{
		perror("Error al asignarle una direccion al socket");
		exit(1);
	}

	/*
		A COMPLETAR POR EL ALUMNO:
		(2) Evitar que procesos hijo queden como zombi
		    Para ello habra que usar la funcion 'signal' para que trate
		     las senyales tipo SIGCHLD
	*/
	signal(SIGCHLD, SIG_IGN);

	while(1)
	{
		tam_dir = sizeof(dir_cli);
		if((n=recvfrom(sock, buf, MAX_BUF, 0, (struct sockaddr *) &dir_cli,
		               &tam_dir)) < 0)
		{
			perror("Error al recibir datos");
			exit(1);
		}


		if(fork() == 0) {
			sock = socket(AF_INET, SOCK_DGRAM, 0);
			if(connect(sock, (struct sockaddr *) &dir_cli, sizeof(dir_cli)) < 0){
				perror("Error al conectar el socket UDP con el del servidor");
				exit(1);
			}
			write(sock, buf, n)


			select(n, &readfds, NULL, NULL, &tv);

			fd_set readfds;
			struct timeval tv;

			FD_ZERO(&readfds);
			FD_SET(sock, &readfds);
			n = sock + 1;
			tv.tv_sec = MAX_WAIT;
			tv.tv_usec = 0;
			int rv;
			do {
				int reads;
				if((reads = read(sock, buf, MAX_BUF)) < 0){
					perror("Error al recibir datos");
					exit(1);
				}
				if (reads == 0) {
					close(sock);
					exit(0);
				}
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

				tv.tv_sec = MAX_WAIT;
				tv.tv_usec = 0;

			} while(rv == 0 );
			if(n < 0)
				perror("Error al recibir datos");

			close(dialogo);
		}

		if(sendto(sock, buf, n, 0, (struct sockaddr *) &dir_cli, tam_dir) < 0)
		{
			perror("Error al enviar datos");
			exit(1);
		}
	}
	close(sock);
}
