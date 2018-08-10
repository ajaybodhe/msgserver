
#include "commandline/commandline.h"
#include "sendmessage/sendmessage.h"

int main(int argc, char *argv[]) 
{
    char *s=NULL;
    int p=-1;
    char *m=NULL;
    readCommandLine(argc, argv, &s, &p, &m);
    sendMessage(s, p, m);
    return 0;
}