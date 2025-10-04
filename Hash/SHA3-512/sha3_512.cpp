#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <cstring>

int main()
{
    const char* data = "Hello, SHA3-512!";
    unsigned char hash[64]; // SHA3-512 output is 64 bytes
    unsigned int hash_len = 0;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx)
    {
        std::cerr << "Error: EVP_MD_CTX_new failed!" << std::endl;
        return 1;
    }

    if (1 != EVP_DigestInit_ex(ctx, EVP_sha3_512(), NULL))
    {
        std::cerr << "Error: EVP_DigestInit_ex failed!" << std::endl;
        EVP_MD_CTX_free(ctx);
        return 1;
    }

    if (1 != EVP_DigestUpdate(ctx, data, strlen(data)))
    {
        std::cerr << "Error: EVP_DigestUpdate failed!" << std::endl;
        EVP_MD_CTX_free(ctx);
        return 1;
    }

    if (1 != EVP_DigestFinal_ex(ctx, hash, &hash_len))
    {
        std::cerr << "Error: EVP_DigestFinal_ex failed!" << std::endl;
        EVP_MD_CTX_free(ctx);
        return 1;
    }
    EVP_MD_CTX_free(ctx);

    std::cout << "Input: " << data << std::endl;
    std::cout << "SHA3-512 length: " << hash_len << std::endl;
    std::cout << "SHA3-512: ";
    for (unsigned int i = 0; i < hash_len; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::endl;
    return 0;
}
