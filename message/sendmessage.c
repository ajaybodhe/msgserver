#include "message/sendmessage.h"

/*
    Sends message to upstream server and notes down the response
*/
int sendMessage(char *serverAddr, int serverPort, char *message) 
{
    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char response[4096];

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    /* lookup the ip address */
    server = gethostbyname(serverAddr);
    if (server == NULL) {
        error("ERROR, no such host");
    }

    /* fill in the structure */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0) {
            error("ERROR writing message to socket");
        }
        if (bytes == 0) {
            break;
        }
        sent+=bytes;
    } while (sent < total);

    printf("sent the message=%s\n", message);

    /* receive the response */
    // memset(response,0,sizeof(response));
    // total = sizeof(response)-1;
    // received = 0;
    // do {
    //     bytes = read(sockfd, response + received, total - received);
    //     if (bytes < 0) {
    //         error("ERROR reading response from socket");
    //     }
    //     if (bytes == 0) {
    //         break;
    //     }
    //     received+=bytes;
    // } while (received < total);

    // if (received == total) {
    //     error("ERROR storing complete response from socket");
    // }

    /* process response */
    // printf("Response:%s\n",response);

    /* close the socket */
    close(sockfd);
}