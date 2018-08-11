
#include "commandline/commandline.h"
#include "sendmessage/sendmessage.h"
#include "tripledes/tripledes.h"

int main(int argc, char *argv[]) 
{
    char *s=NULL;
    int p=-1;
    char *m=NULL;
    unsigned char * eData = NULL;
    unsigned char *dData = NULL;
    
    /*
    init 3des keys
    */
    initDes();

    /*
    read params from command line
    */
    readCommandLine(argc, argv, &s, &p, &m);

    /*
    encrypt message using 3 des
    */
    printf("original data:%s\n", m);
    eData = encryptTripleDes((unsigned char *)m);
    printf("Encrypted data:%s\n", eData);
    dData = decryptTripleDes((unsigned char *)eData);
    printf("decrypted data:%s\n", dData);
    
    /*
    send encrypted message to upstream server
    */
    sendMessage(s, p, eData);
    return 0;
}