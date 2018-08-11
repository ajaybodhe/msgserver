#include "tripledes/tripledes.h"

DES_cblock TripleDesKey1 =  { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
DES_cblock TripleDesKey2 = { 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p' };
DES_cblock TripleDesKey3 = { 'q', 'r', 's', 't', 'u', 'v', 'w', 'x' };

DES_key_schedule SchKey1,SchKey2,SchKey3;

void initDes() 
{
	/* Check for Weak key generation */
	if ( -2 == (DES_set_key_checked(&TripleDesKey1, &SchKey1) || DES_set_key_checked(&TripleDesKey2, &SchKey2) || DES_set_key_checked(&TripleDesKey3, &SchKey3)))
	{
		printf(" Weak key ....\n");
	}
}

/*
    encrypts data with triple des
*/
unsigned char *encryptTripleDes(unsigned char *input_data) 
{
    int input_data_len = strlen(input_data)+1;
	
	/* Init vector */
	DES_cblock iv = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	DES_set_odd_parity(&iv);

    /* Buffers for Encryption */
	unsigned char* cipher = (unsigned char*) calloc(input_data_len*3, sizeof(char));

    /* Triple-DES CBC Encryption */
	DES_ede3_cbc_encrypt( (unsigned char*)input_data, (unsigned char*)cipher, input_data_len, &SchKey1, &SchKey2, &SchKey3, &iv, DES_ENCRYPT);

    return cipher;
}

/*
    decrypts data with triple des
*/
unsigned char *decryptTripleDes(unsigned char *input_data) 
{
	int input_data_len = strlen(input_data)+1;

    /* Init vector */
	DES_cblock iv = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	DES_set_odd_parity(&iv);

    /* Buffers for Decryption */
	unsigned char* text = (unsigned char*) calloc(input_data_len, sizeof(char));

    DES_ede3_cbc_encrypt( (unsigned char*)input_data, (unsigned char*)text, input_data_len, &SchKey1, &SchKey2, &SchKey3, &iv, DES_DECRYPT);
	
    return text;
}