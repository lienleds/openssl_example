#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[16]; // 128-bit key
    unsigned char iv[16];  // 128-bit IV
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating AES key!" << std::endl;
        return 1;
    }
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        std::cerr << "Error generating AES IV!" << std::endl;
        return 1;
    }
    FILE* kf = fopen("aes_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open aes_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    FILE* ivf = fopen("aes_iv.bin", "wb");
    if (!ivf)
    {
        std::cerr << "Cannot open aes_iv.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(iv, 1, sizeof(iv), ivf);
    fclose(ivf);
    std::cout << "AES key and IV generated and saved to aes_key.bin and aes_iv.bin" << std::endl;
    return 0;
}
