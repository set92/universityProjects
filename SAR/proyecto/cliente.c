#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "cliente.h"

int main(int argc, char *argv[])
{
	int sock, n;
	char buf[MAX_BUF], buf2[MAX_BUF];
	
	//crear socket y asignarle direccion
	struct sockaddr_in dir_serv;

	if(argc != 2)
	{
		fprintf(stderr, "Uso: %s <DireccionIPv4>\n", argv[0]);
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
	if(inet_aton(argv[1],&dir_serv.sin_addr) <= 0)
	{
		fprintf(stderr,"Error en la direccion IP: %s\n", argv[1]);
		exit(1);
	}
	
	while (1){
	//muestra el menu y
	//recoge el comando con los parametros
		menu(buf);


		if(sendto(sock, buf, strlen(buf), 0,(struct sockaddr *) &dir_serv, sizeof(dir_serv)) < 0)
		{
			perror("Error al enviar datos");
			exit(1);
		}

		if((n = recvfrom(sock, buf2, MAX_BUF,0,NULL,NULL)) < 0)
		{
			perror("Error al recibir datos");
			exit(1);
		}
		//controlar el mensaje recibido
		int estado = parse(buf2);
		
		gestionComando(estado, buf2);
		//borramos el buffer por si acaso
		memset(buf2, 0, MAX_BUF );
	}

	printf("Cerrando Socket...\n");
	close(sock);
	exit(0);
}

int menu(char *mensaje){
	int opcion;
	char buf[MAX_BUF];

	printf("introduce una opcion\n");
	printf("1- Control de temperatura\n");
	printf("2- Registro de llamadas\n");
	printf("3- Ajustar la apertura de la persiana\n");
	printf("4- Reproductor de musica\n");
	printf("5- Volumen del reproductor\n");
	printf("6- Salir\n");
	fgets(buf,MAX_BUF,stdin);
	opcion = atoi(buf);
	
	switch(opcion){
	case 1 :
		temperatura(mensaje);//devuelve el comando a usasr
		break;
	case 2 :
		llamadas(mensaje);
		break;
	case 3 :
		persiana(mensaje);
		break;
	case 4 :
		reproductor(mensaje);
		break;
	case 5 :
		volumen(mensaje);
		break;
	case 6 :
		printf("hasta luego\n");
		exit(0);
		break;
	default : 
		menu(mensaje);
	}
	

}

int temperatura(char *mensaje){
	char buf[MAX_BUF];

	char *comando="SET";

	strcpy(mensaje, comando);


	printf("Introduce la temperatura:\n");
	printf("Solo podra tener como maximo dos digitos en la parte entera y uno en la parte decimal\n");
	fgets(buf,MAX_BUF,stdin);
	buf[strlen(buf)-1]=0;
	strcat(mensaje, buf);

	strcat(mensaje, "/");

	printf("Introduce la hora a la que se va a apagar el termostato\n");
	printf("Formato-> hh:mm\n");
	fgets(buf,MAX_BUF,stdin);
	strcat(mensaje, buf);
	
}

int llamadas(char *mensaje){
	const char *com="REG";
	strcpy(mensaje, com);
}

int persiana(char *mensaje){
	char buf[MAX_BUF];

	char *com="PER";
	
	strcpy(mensaje, com);

	printf("Introduce la id: ");
	fgets(buf,MAX_BUF,stdin);
	buf[strlen(buf)-1]=0;
	strcat(mensaje, buf);

	strcat(mensaje, "/");

	printf("Introduce el modo: ");
	fgets(buf,MAX_BUF,stdin);
	buf[strlen(buf)-1]=0;
	strcat(mensaje, buf);	
}

int reproductor(char *mensaje){
	char buf[MAX_BUF];

	char *com="CRL";

	strcpy(mensaje, com);

	printf("introduce una opcion\n");
	printf("1- Encender\n");
	printf("2- Apagar\n");
	printf("3- Play\n");
	printf("4- Stop\n");
	printf("5- Next\n");
	fgets(buf,MAX_BUF,stdin);
	strcat(mensaje, buf);	
}

int volumen(char *mensaje){
	char buf[MAX_BUF];

	char *com="VOL";

	strcpy(mensaje, com);
	
	printf("Introduce el volumen: ");
	fgets(buf,MAX_BUF,stdin);
	strcat(mensaje, buf);
}

//Manda 0 en caso de ir todo bien o un codigo de error en caso de haber un error
int parse(char *status)
{
	if(!strncmp(status,"OK",2))
		return 0;
	else if(!strncmp(status,"ER",2))
		return(atoi(status+2));
	else
	{
		fprintf(stderr,"Respuesta inesperada.\n");
		exit(1); 
	}
}

//Muestra un mensaje de recibido o en caso de error muestra el error
int gestionComando(int estado, char *buf){
	switch (estado){
	case 0 :
		printf("%s\n", buf+2);
		break;
	case 3 :
		printf("Temperatura incorrecta o fuera de los limites\n");
		break;
	case 4 :
		printf("Hora incorrecta\n");
		break;
	case 5 :
		printf("Error en gestion de llamadas\n");
		break;
	case 6 :
		printf("ID de persiana inexistente\n");
		break;
	case 7 :
		printf("Error en la gestion de persiana\n");
		break;
	case 8 :
		printf("valor no valido\n");
		break;
	case 9 :
		printf("error en el reproductor de musica\n");
		break;
	case 10 :
		printf("El volumen no esta entre 0 y 100\n");
		break;
	case 11 :
		printf("Error en el control de volumen\n");
		break;
	default : 
		printf("Error en la aplicacion\n");
		exit(1);
	}
	
		
}

