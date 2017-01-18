#define MAX_BUF 1024
#define SERVER "localhost"
#define PORT 65535


int parse(char *status);
int menu();
int temperatura();
int llamadas();
int persiana();
int reproductor();
int volumen();
int gestionComando(int estado, char *buf);

