#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include "utils.h"

/*
    Sends message to upstream server and notes down the response
*/
int sendMessage(char *serverAddr, int serverPort, char *message);