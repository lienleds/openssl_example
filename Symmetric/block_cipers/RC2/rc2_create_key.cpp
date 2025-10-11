#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[16]; // 128-bit key for RC2 (RC2 supports variable length 8-1024 bits)
    unsigned char iv[8];   // 64-bit IV for RC2 CBC mode
    
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating RC2 key!" << std::endl;
        return 1;
    }
    
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        std::cerr << "Error generating RC2 IV!" << std::endl;
        return 1;
    }
    
    // Save key to file
    FILE* kf = fopen("rc2_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open rc2_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    
    // Save IV to file
    FILE* ivf = fopen("rc2_iv.bin", "wb");
    if (!ivf)
    {
        std::cerr << "Cannot open rc2_iv.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(iv, 1, sizeof(iv), ivf);
    fclose(ivf);
    
    std::cout << "RC2 key and IV generated successfully!" << std::endl;
    std::cout << "Key saved to: rc2_key.bin (128 bits)" << std::endl;
    std::cout << "IV saved to: rc2_iv.bin (64 bits)" << std::endl;
    
    return 0;
}