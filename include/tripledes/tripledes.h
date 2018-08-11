#ifndef _TRIPLE_DES_H
#define _TRIPLE_DES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

/* 3des encrypt decrypt */
void initDes();
unsigned char *encryptTripleDes(unsigned char *input_data);
unsigned char *decryptTripleDes(unsigned char *input_data);

#endif