#include <openssl/rand.h>
#include <iostream>
#include <cstdio>

int main()
{
    unsigned char key[16]; // 128-bit key (Blowfish supports variable key length 32-448 bits)
    unsigned char iv[8];   // 64-bit IV for Blowfish CBC mode
    
    if (!RAND_bytes(key, sizeof(key)))
    {
        std::cerr << "Error generating Blowfish key!" << std::endl;
        return 1;
    }
    
    if (!RAND_bytes(iv, sizeof(iv)))
    {
        std::cerr << "Error generating Blowfish IV!" << std::endl;
        return 1;
    }
    
    // Save key to file
    FILE* kf = fopen("blowfish_key.bin", "wb");
    if (!kf)
    {
        std::cerr << "Cannot open blowfish_key.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(key, 1, sizeof(key), kf);
    fclose(kf);
    
    // Save IV to file
    FILE* ivf = fopen("blowfish_iv.bin", "wb");
    if (!ivf)
    {
        std::cerr << "Cannot open blowfish_iv.bin for writing!" << std::endl;
        return 1;
    }
    fwrite(iv, 1, sizeof(iv), ivf);
    fclose(ivf);
    
    std::cout << "Blowfish key and IV generated successfully!" << std::endl;
    std::cout << "Key saved to: blowfish_key.bin (128 bits)" << std::endl;
    std::cout << "IV saved to: blowfish_iv.bin (64 bits)" << std::endl;
    
    return 0;
}