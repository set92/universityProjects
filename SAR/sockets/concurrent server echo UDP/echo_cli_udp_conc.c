#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_BUF 1024
#define PORT 50005

int main(int argc, char *argv[])
{
	int sock, n;
	char buf[MAX_BUF];
	struct sockaddr_in dir_serv;
	struct hostent *hp;

	if(argc != 2)
	{
		fprintf(stderr, "Uso: %s <NombreServidor | DireccionIPv4>\n",
		 argv[0]);
		exit(1);
	}

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error al crear el socket");
		exit(1);
	}

	memset(&dir_serv, 0, sizeof(dir_serv));
	dir_serv.sin_family = AF_INET;
	dir_serv.sin_port = htons(PORT);
	if((hp = gethostbyname(argv[1])) == NULL)
	{
		herror("Error al resolver el nombre del servidor");
		exit(1);
	}
	memcpy(&dir_serv.sin_addr, hp->h_addr, hp->h_length);

	/*
		A COMPLETAR POR EL ALUMNO:
		Enviar primer mensaje y recibir respuesta.
	*/
	sendto(sock, buf, n, 0, (struct sockaddr *) &dir_serv, tam_dir);
	recvfrom(sock, buf, MAX_BUF, 0, (struct sockaddr *) &dir_serv, &tam_dir);
	/*
		A TENER EN CUENTA POR EL ALUMNO:
		Verificar que el 'connect' se hace con el socket adecuado
	*/
	if(connect(sock, (struct sockaddr *) &dir_serv, sizeof(dir_serv)) < 0)
	{
		perror("Error al conectar el socket UDP con el del servidor");
		exit(1);
	}

	while(fgets(buf, MAX_BUF, stdin) != NULL)
	{
		if(write(sock, buf, strlen(buf)) < strlen(buf))
		{
			perror("Error al enviar datos");
			exit(1);
		}

		if((n = read(sock, buf, MAX_BUF)) < 0)
		{
			perror("Error al recibir datos");
			exit(1);
		}
		buf[n] = 0;
		printf("%s",buf);
	}

	write(sock, "", 0);
	/*
		A COMPLETAR POR EL ALUMNO:
		Enviar un mensaje vacio para que acabe el proceso servidor
	*/
	close(sock);
	exit(0);
}
