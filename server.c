#include <stdio.h> /* printf*/
#include <stdlib.h> /* exit */
#include <popt.h> /* command ine read */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include "server.h" /* application specific*/

/*
    Error function
*/
void error(const char *msg) 
{ 
    printf("error msg:= %s", msg); 
    exit(1); 
}

/*
    Reads command line arguments
    example: sendmsg -s 192.168.0.10 -p 12345 -m "hello server"
    s = server address
    p = server port
    m = message to be sent
*/
void readCommandLine(int argc, char *argv[], char **serverAddr, int *serverPort, char**message) 
{
    poptContext pc;

    // specify command line options
    struct poptOption options[] = {
        {NULL, SERVER_ADDRESS, POPT_ARG_STRING, serverAddr, 1, "server address", "input server address"},
        {NULL, SERVER_PORT, POPT_ARG_INT, serverPort, 2, "server port", "input server port"},
        {NULL, MESSAGE, POPT_ARG_STRING, message, 3, "message to be sent", "type the message"},
        POPT_AUTOHELP
        {NULL}
    };

    // pc is the context for all popt-related functions  
     pc = poptGetContext(NULL, argc, (const char **)argv, options, 0);  
     poptSetOtherOptionHelp(pc, "[ARG...]");     
     if (argc < 2) {  
         poptPrintUsage(pc, stderr, 0);  
         exit(1);  
     }

     // process options and handle each val returned  
     int val;  
     while ((val = poptGetNextOpt(pc)) >= 0) {  
         //printf("poptGetNextOpt returned val %d\n", val);  
     }  
       
     // poptGetNextOpt returns -1 when the final argument has been parsed  
     // otherwise an error occured  
     if (val != -1) {  
         // handle error  
         switch(val) {  
         case POPT_ERROR_NOARG:   
             error("Argument missing for an option\n");  
         case POPT_ERROR_BADOPT:   
             error("Option's argument could not be parsed\n");   
         case POPT_ERROR_BADNUMBER:  
         case POPT_ERROR_OVERFLOW:   
             error("Option could not be converted to number\n");   
         default:  
             error("Unknown error in option processing\n");   
         }  
     }  
       
     // Handle ARG... part of commandline  
     while (poptPeekArg(pc) != NULL) {  
         char *arg = (char*)poptGetArg(pc);  
         printf("poptGetArg returned arg: \"%s\"\n", arg);  
     }  
       
    // validations on input
    if (*serverAddr == NULL) {
        error("Please enter server address as -s");
    }
    if (serverPort == NULL) { // additional validation on port range shall be done
        error("Please enter server port as -p"); 
    }
     if (*message == NULL) {
        error("Please enter message as -m");
    }

    // Done. Print final result.  
    //  printf("final value of serverAddr: %s\n", *serverAddr);  
    //  printf("final value of serverPort: %d\n", *serverPort);  
    //  printf("final value of message: %s\n", *message);  
}

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
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd, response + received, total - received);
        if (bytes < 0) {
            error("ERROR reading response from socket");
        }
        if (bytes == 0) {
            break;
        }
        received+=bytes;
    } while (received < total);

    if (received == total) {
        error("ERROR storing complete response from socket");
    }

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:%s\n",response);

}
int main(int argc, char *argv[]) 
{
    char *s=NULL;
    int p=-1;
    char *m=NULL;
    readCommandLine(argc, argv, &s, &p, &m);
    sendMessage(s, p, m);
    return 0;
}