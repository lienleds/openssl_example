#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[16]; // 128-bit key for Camellia-128
    unsigned char iv[16];  // 128-bit IV for Camellia CBC mode
    
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating Camellia key!" << std::endl;
        return 1;
    }
    
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        std::cerr << "Error generating Camellia IV!" << std::endl;
        return 1;
    }
    
    // Save key to file
    FILE* kf = fopen("camellia_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open camellia_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    
    // Save IV to file
    FILE* ivf = fopen("camellia_iv.bin", "wb");
    if (!ivf)
    {
        std::cerr << "Cannot open camellia_iv.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(iv, 1, sizeof(iv), ivf);
    fclose(ivf);
    
    std::cout << "Camellia key and IV generated successfully!" << std::endl;
    std::cout << "Key saved to: camellia_key.bin (128 bits)" << std::endl;
    std::cout << "IV saved to: camellia_iv.bin (128 bits)" << std::endl;
    
    return 0;
}