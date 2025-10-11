#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/provider.h>
#include <cstring>
#include <iostream>
#include <iomanip>

void handleErrors()
{
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

int main()
{
    // Load default provider for SEED support (SEED is in default provider)
    OSSL_PROVIDER *default_prov = OSSL_PROVIDER_load(NULL, "default");
    if (!default_prov)
    {
        std::cerr << "Failed to load default provider!" << std::endl;
        return 1;
    }

    // Generate random key (128 bits for SEED)
    unsigned char key[16];
    if (1 != RAND_bytes(key, sizeof(key))) {
        std::cerr << "Failed to generate random key!" << std::endl;
        OSSL_PROVIDER_unload(default_prov);
        return 1;
    }

    // Generate random IV (128 bits for SEED CBC mode)
    unsigned char iv[16];
    if (1 != RAND_bytes(iv, sizeof(iv))) {
        std::cerr << "Failed to generate random IV!" << std::endl;
        OSSL_PROVIDER_unload(default_prov);
        return 1;
    }

    // Save key to file
    FILE* fkey = fopen("seed_key.bin", "wb");
    if (!fkey) {
        std::cerr << "Cannot create seed_key.bin!" << std::endl;
        OSSL_PROVIDER_unload(default_prov);
        return 1;
    }
    
    if (fwrite(key, 1, sizeof(key), fkey) != sizeof(key)) {
        std::cerr << "Failed to write key to file!" << std::endl;
        fclose(fkey);
        OSSL_PROVIDER_unload(default_prov);
        return 1;
    }
    fclose(fkey);

    // Save IV to file  
    FILE* fiv = fopen("seed_iv.bin", "wb");
    if (!fiv) {
        std::cerr << "Cannot create seed_iv.bin!" << std::endl;
        OSSL_PROVIDER_unload(default_prov);
        return 1;
    }
    
    if (fwrite(iv, 1, sizeof(iv), fiv) != sizeof(iv)) {
        std::cerr << "Failed to write IV to file!" << std::endl;
        fclose(fiv);
        OSSL_PROVIDER_unload(default_prov);
        return 1;
    }
    fclose(fiv);

    std::cout << "SEED key and IV generated successfully!" << std::endl;
    std::cout << "Key saved to: seed_key.bin (128 bits)" << std::endl;
    std::cout << "IV saved to: seed_iv.bin (128 bits)" << std::endl;
    
    std::cout << "\nGenerated key (hex): ";
    for (int i = 0; i < sizeof(key); ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)key[i];
    }
    
    std::cout << "\nGenerated IV (hex): ";
    for (int i = 0; i < sizeof(iv); ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)iv[i];
    }
    std::cout << std::dec << std::endl;

    OSSL_PROVIDER_unload(default_prov);
    return 0;
}