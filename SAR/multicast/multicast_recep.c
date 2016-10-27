#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUF 1024
#define PORT 50007

int main()
{
	int sock, n;
	struct sockaddr_in dir_serv, dir_cli;
	socklen_t tam_dir;
	char buf[MAX_BUF];

	struct ip_mreq group;
	
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
		Asociar el socket a la direccion multicast
	*/

	group.imr_multiaddr.s_addr = inet_addr("224.0.0.11");
	group.imr_interface.s_addr = dir_serv.sin_addr.s_addr;

	if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0){
		perror("Adding multicast group error");
		close(sock);
		exit(1);
	}
	/*
		A COMPLETAR POR EL ALUMNO:
		En este caso el bucle no sera infinito
	*/
	do {
		tam_dir = sizeof(dir_cli);
		if((n = recvfrom(sock, buf, MAX_BUF, 0, (struct sockaddr *) &dir_cli, &tam_dir)) < 0)	{
			perror("Error al recibir datos");
			exit(1);
		}

		/*
			A COMPLETAR POR EL ALUMNO:
			Responder al emisor con el codigo seguido del nombre del alumno
			Recibir respuesta y, si es negativa, intentarlo de nuevo
		*/
		strcpy(buf+10,"pl25");
		if(sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &dir_cli, tam_dir) < 0) {
			perror("Error al enviar datos");
			exit(1);
		}

		if((n = recvfrom(sock, buf, MAX_BUF, 0, (struct sockaddr *) &dir_cli, &tam_dir)) < 0){
			perror("Error al recibir datos");
			exit(1);
		}

	} while (strcmp(buf,"ER") == 0);
	/*
		A COMPLETAR POR EL ALUMNO:
		Desasociar direccion multicast
	*/
	setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&group, sizeof(group));
	close(sock);
}
