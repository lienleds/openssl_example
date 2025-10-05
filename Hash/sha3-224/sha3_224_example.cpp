#include <openssl/evp.h>
#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    FILE* file = fopen(argv[1], "rb");
    if (!file)
    {
        std::cerr << "Cannot open file!\n";
        return 1;
    }
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha3_224();
    EVP_DigestInit_ex(ctx, md, NULL);
    unsigned char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
        EVP_DigestUpdate(ctx, buffer, bytesRead);
    }
    fclose(file);
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    EVP_DigestFinal_ex(ctx, hash, &hashLen);
    EVP_MD_CTX_free(ctx);
    std::cout << "SHA3-224: ";
    for (unsigned int i = 0; i < hashLen; ++i)
    {
        printf("%02x", hash[i]);
    }
    std::cout << std::endl;
    return 0;
}
