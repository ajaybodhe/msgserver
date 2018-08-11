#include "tripledes/tripledes.h"

DES_cblock TripleDesKey1 =  { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68 };
DES_cblock TripleDesKey2 = { 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70 };
DES_cblock TripleDesKey3 = { 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78 };

DES_key_schedule SchKey1,SchKey2,SchKey3;

void initDes() 
{
	DES_set_key_checked(&TripleDesKey1, &SchKey1);
	DES_set_key_checked(&TripleDesKey2, &SchKey2);
	DES_set_key_checked(&TripleDesKey3, &SchKey3);
}

/*
    encrypts data with triple des
*/
unsigned char *encryptTripleDes(unsigned char *input_data) 
{
    int input_data_len = strlen(input_data)+1;
	
	/* Init vector */
	DES_cblock iv = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//DES_set_odd_parity(&iv);

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
	//DES_set_odd_parity(&iv);

    /* Buffers for Decryption */
	unsigned char* text = (unsigned char*) calloc(input_data_len, sizeof(char));

    DES_ede3_cbc_encrypt( (unsigned char*)input_data, (unsigned char*)text, input_data_len, &SchKey1, &SchKey2, &SchKey3, &iv, DES_DECRYPT);
	
    return text;
}