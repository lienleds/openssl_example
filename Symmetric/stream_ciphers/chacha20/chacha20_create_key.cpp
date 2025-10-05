#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[32];   // 256-bit key for ChaCha20
    unsigned char nonce[12]; // 96-bit nonce for ChaCha20
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating ChaCha20 key!" << std::endl;
        return 1;
    }
    if (!RAND_bytes(nonce, sizeof(nonce)))
    {
        std::cerr << "Error generating ChaCha20 nonce!" << std::endl;
        return 1;
    }
    FILE* kf = fopen("chacha20_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open chacha20_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    FILE* nf = fopen("chacha20_nonce.bin", "wb");
    if (!nf)
    {
        std::cerr << "Cannot open chacha20_nonce.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(nonce, 1, sizeof(nonce), nf);
    fclose(nf);
    std::cout << "ChaCha20 key and nonce generated and saved to chacha20_key.bin and chacha20_nonce.bin" << std::endl;
    return 0;
}
