#include <openssl/rand.h>
#include <cstdio>
#include <cstdlib>

int main()
{
    unsigned char key[24];
    unsigned char iv[8];
    if (RAND_bytes(key, sizeof(key)) != 1 || RAND_bytes(iv, sizeof(iv)) != 1)
    {
        printf("Failed to generate key or IV!\n");
        return 1;
    }
    FILE* fkey = fopen("des3_key.bin", "wb");
    FILE* fiv = fopen("des3_iv.bin", "wb");
    if (!fkey || !fiv)
    {
        printf("Failed to open file for writing!\n");
        return 1;
    }
    fwrite(key, 1, sizeof(key), fkey);
    fwrite(iv, 1, sizeof(iv), fiv);
    fclose(fkey);
    fclose(fiv);
    printf("3DES key and IV generated and saved to des3_key.bin and des3_iv.bin\n");
    return 0;
}
