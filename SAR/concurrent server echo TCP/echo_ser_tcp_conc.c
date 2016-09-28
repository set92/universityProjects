#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>	// Para la funcion 'signal'

#define MAX_BUF 1024
#define PORT 50004

/*
	NOTA:
	Los numeros (entre parentesis) de los comentarios identifican distintos
	 ejercicios. Se recomienda realizar los distintos ejercicios de uno en
	 uno, probando su correcto funcionamiento antes de pasar al siguiente.
*/

int main(){
	int sock, dialogo, n;
	struct sockaddr_in dir_serv;
	char buf[MAX_BUF];

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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
	if(listen(sock,5) < 0)
	{
		perror("Error al convertir el socket en socket de escucha");
		exit(1);
	}

	signal(SIGCHLD, SIG_IGN);
	/*
		A COMPLETAR POR EL ALUMNO:
		(2) Evitar que procesos hijo queden como zombi
		    Para ello habra que usar la funcion 'signal' para que trate
		     las senyales tipo SIGCHLD
	*/

	while(1) {
		if((dialogo = accept(sock, NULL, NULL)) < 0) {
			perror("Error al aceptar una peticion de conexion");
			exit(1);
		}
		if(fork() != 0) {
			close(dialogo);
		}else{
			while((n=read(dialogo, buf, MAX_BUF)) > 0)
			{
				if(write(dialogo, buf, n) < n)
				{
					perror("Error al enviar datos");
					close(dialogo);
					exit(1);
				}
			}
			if(n < 0)
				perror("Error al recibir datos");

			close(dialogo);
		}


	}
	close(sock);
}
