#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[16]; // 128-bit RC4 key
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating RC4 key!" << std::endl;
        return 1;
    }
    FILE* kf = fopen("rc4_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open rc4_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    std::cout << "RC4 key generated and saved to rc4_key.bin" << std::endl;
    return 0;
}
