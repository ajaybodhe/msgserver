#ifndef _COMMANDLINE_H_
#define _COMMANDLINE_H_
#include <stdio.h> /* printf*/
#include <stdlib.h> /* exit */
#include <popt.h> /* command ine read */
#include "utils/utils.h"

#define SERVER_ADDRESS 's'
#define SERVER_PORT 'p'
#define MESSAGE 'm'

/*
    Reads command line arguments
    example: sendmsg -s 192.168.0.10 -p 12345 -m "hello server"
    s = server address
    p = server port
    m = message to be sent
*/
void readCommandLine(int argc, char *argv[], char **serverAddr, int *serverPort, char**message) ;
#endif