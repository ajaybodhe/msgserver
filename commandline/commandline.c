#include "commandline/commandline.h"

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