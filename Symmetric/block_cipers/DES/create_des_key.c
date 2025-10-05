
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    unsigned char key[8];
    unsigned char iv[8];
    if (RAND_bytes(key, sizeof(key)) != 1 || RAND_bytes(iv, sizeof(iv)) != 1)
    {
        printf("Failed to generate key or IV!\n");
        return 1;
    }
    FILE* fkey = fopen("des_key.bin", "wb");
    FILE* fiv = fopen("des_iv.bin", "wb");
    if (!fkey || !fiv)
    {
        printf("Failed to open file for writing!\n");
        return 1;
    }
    fwrite(key, 1, sizeof(key), fkey);
    fwrite(iv, 1, sizeof(iv), fiv);
    fclose(fkey);
    fclose(fiv);
    printf("DES key and IV generated and saved to des_key.bin and des_iv.bin\n");
    return 0;
}
