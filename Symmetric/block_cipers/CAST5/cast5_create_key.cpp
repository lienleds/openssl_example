#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[16]; // 128-bit key for CAST5 (CAST5 supports 40-128 bit keys)
    unsigned char iv[8];   // 64-bit IV for CAST5 CBC mode
    
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating CAST5 key!" << std::endl;
        return 1;
    }
    
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        std::cerr << "Error generating CAST5 IV!" << std::endl;
        return 1;
    }
    
    // Save key to file
    FILE* kf = fopen("cast5_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open cast5_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    
    // Save IV to file
    FILE* ivf = fopen("cast5_iv.bin", "wb");
    if (!ivf)
    {
        std::cerr << "Cannot open cast5_iv.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(iv, 1, sizeof(iv), ivf);
    fclose(ivf);
    
    std::cout << "CAST5 key and IV generated successfully!" << std::endl;
    std::cout << "Key saved to: cast5_key.bin (128 bits)" << std::endl;
    std::cout << "IV saved to: cast5_iv.bin (64 bits)" << std::endl;
    
    return 0;
}