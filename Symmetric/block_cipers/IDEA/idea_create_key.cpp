#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[16]; // 128-bit key for IDEA (fixed size)
    unsigned char iv[8];   // 64-bit IV for IDEA CBC mode
    
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating IDEA key!" << std::endl;
        return 1;
    }
    
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        std::cerr << "Error generating IDEA IV!" << std::endl;
        return 1;
    }
    
    // Save key to file
    FILE* kf = fopen("idea_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open idea_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    
    // Save IV to file
    FILE* ivf = fopen("idea_iv.bin", "wb");
    if (!ivf)
    {
        std::cerr << "Cannot open idea_iv.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(iv, 1, sizeof(iv), ivf);
    fclose(ivf);
    
    std::cout << "IDEA key and IV generated successfully!" << std::endl;
    std::cout << "Key saved to: idea_key.bin (128 bits)" << std::endl;
    std::cout << "IV saved to: idea_iv.bin (64 bits)" << std::endl;
    
    return 0;
}