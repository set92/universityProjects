#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_BUF 1024
#define PORT 65535

/**
 * Función temperatura que recibe a traves del buffer TT.t/HH:mm y devuelve OK si es correcto, o ER3 o ER4 si no lo es.
 * @param buf Buffer de gestión de los datos enviados y recibidos por el servidor.
 */
void temperatura(char *buf) {
    double temp;
    int hh, mm;
    char param[4];

    // Troceamos en substrings los distintos parametros recibidos en el buffer
    memcpy(param, buf + 3, 4);
    param[4] = '\0';
    temp = atof(param);

    memcpy(param, buf + 8, 2);
    param[2] = '\0';
    hh = atoi(param);

    memcpy(param, buf + 11, 2);
    param[2] = '\0';
    mm = atoi(param);

    memset(buf, 0, MAX_BUF);
    if (temp < 0.0 || temp > 99.9) memcpy(buf, "ER3", 3);
    else if ((hh < 0 || hh > 23) || (mm < 0 || mm > 59))  memcpy(buf, "ER4", 3);
    else memcpy(buf, "OK", 2);
}

/**
 * Función que devuelve OK seguido de la lista alamacenada en el fichero fich, si hay algun error devolvera ER5.
 * @param buf Buffer de gestión de los datos enviados y recibidos por el servidor.
 */
void registro(char *buf) {
    FILE *file;
    file = fopen("fich", "r");
    char aux[1024];

    memset(buf, 0, MAX_BUF);
    if (file == NULL) memcpy(buf, "ER5", 3);
    else {
        // return OK + LIST
        strncat(buf, "OK\r\n", strlen(buf));
        while (fgets(aux, MAX_BUF, file) > 0) {
            strncat(buf, aux, strlen(aux));
            strncat(buf, "\r\n", 1);
        }
        buf[strlen(buf)] = 0;
    }
}

/**
 * Recibe en el buffer "ID[0-1]" siendo ID el valor que identifica a cada ventana, y el siguiente digito si se quiere
 * bajar o subir la ventana respectivamente. Si algo no fuera correcto tendriamos los errores ER6, ER7
 * @param buf Buffer de gestión de los datos enviados y recibidos por el servidor.
 */
void persiana(char *buf) {
    int id, modo;
    char param[2];

    memcpy(param, buf + 3, 2); // Troceamos en substrings
    param[2] = '\0';
    id = atoi(param);

    memcpy(param, buf + 5, 1);
    param[1] = '\0';
    modo = atoi(param);

    memset(buf, 0, MAX_BUF);
    if ((id < 0 || id > 99) || (modo < 0 || modo > 1)) memcpy(buf, "ER6", 3);
    else if (0) memcpy(buf, "ER7", 3);
    else memcpy(buf, "OK", 2);
}

/**
 * Función que recibe un valor entre 1 y 5, si hay algun error, devolvera ER8 o ER9.
 * @param buf Buffer de gestión de los datos enviados y recibidos por el servidor.
 */
void reproductor(char *buf) {
    int func;
    char param[1];

    memcpy(param, buf + 3, 1);
    param[1] = '\0';
    func = atoi(param);

    memset(buf, 0, MAX_BUF);
    if (func < 1 || func > 5) memcpy(buf, "ER8", 3);
    else if (0) memcpy(buf, "ER9", 3);
    else memcpy(buf, "OK", 2);
}

/**
 * Función que usara un valor entre 0 y 100 para regular el volumen, si hay algun error devolvera ER10 o ER11.
 * @param buf Buffer de gestión de los datos enviados y recibidos por el servidor.
 */
void volumen(char *buf) {
    int vol;
    char param[3];

    memcpy(param, buf + 3, 3);
    param[3] = '\0';
    vol = atoi(param);

    memset(buf, 0, MAX_BUF);
    if (vol < 0 || vol > 100) memcpy(buf, "ER10", 4);
    else if (0) memcpy(buf, "ER11", 4);
    else memcpy(buf, "OK", 2);
}


int main() {
    int sock;
    struct sockaddr_in dir_serv, dir_cli;
    socklen_t tam_dir;
    char buf[MAX_BUF];
    char commandSelect[3];

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error al crear el socket");
        exit(1);
    }

    dir_serv.sin_family = AF_INET;
    dir_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    dir_serv.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *) &dir_serv, sizeof(dir_serv)) < 0) {
        perror("Error al asignar direccion a socket");
        exit(1);
    }

    while (1) {
        tam_dir = sizeof(dir_cli);

        if((recvfrom(sock, buf, MAX_BUF, 0, (struct sockaddr *) &dir_cli, &tam_dir)) < 0) {
            perror("Error al recibir datos");
            exit(1);
        }

        /** \brief Creamos un substring con el comando seleccionado */
        memcpy(commandSelect, buf, 3);
        commandSelect[3] = 0;

        printf("El comando seleccionado es: %s\n", commandSelect);

        if (strcmp(commandSelect, "SET") == 0) temperatura(buf);
        else if (strcmp(commandSelect, "REG") == 0) registro(buf);
        else if (strcmp(commandSelect, "PER") == 0) persiana(buf);
        else if (strcmp(commandSelect, "CRL") == 0) reproductor(buf);
        else if (strcmp(commandSelect, "VOL") == 0) volumen(buf);
        else {
            perror("Comando no encontrado");
            exit(1);
        }

        if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &dir_cli, tam_dir) < 0) {
            perror("Error al enviar datos");
            exit(1);
        }

    }
    close(sock);
}