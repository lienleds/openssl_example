#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/provider.h>
#include <cstring>
#include <iostream>

void handleErrors()
{
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

int main()
{
    // Load legacy provider for DES support
    OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
    if (!legacy)
    {
        std::cerr << "Failed to load legacy provider!" << std::endl;
        return 1;
    }


    // Load key and IV from files
    unsigned char key[8];
    unsigned char iv[8];
    FILE* fkey = fopen("des_key.bin", "rb");
    FILE* fiv = fopen("des_iv.bin", "rb");
    if (!fkey || !fiv)
    {
        std::cerr << "Cannot open des_key.bin or des_iv.bin!\n";
        return 1;
    }
    if (fread(key, 1, sizeof(key), fkey) != sizeof(key) || fread(iv, 1, sizeof(iv), fiv) != sizeof(iv))
    {
        std::cerr << "Failed to read key or IV from file!\n";
        fclose(fkey);
        fclose(fiv);
        return 1;
    }
    fclose(fkey);
    fclose(fiv);

    // Data
    const char* plaintext = "This is DES";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[128];
    unsigned char decrypted[128];
    int len = 0, ciphertext_len = 0, decrypted_len = 0;

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv)) handleErrors();
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, reinterpret_cast<const unsigned char*>(plaintext), plaintext_len)) handleErrors();
    ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Print key, IV, and ciphertext
    std::cout << "Key: ";
    for (unsigned char b : key)
        std::cout << std::hex << (int)b;
    std::cout << "\nIV: ";
    for (unsigned char b : iv)
        std::cout << std::hex << (int)b;
    std::cout << "\nCiphertext: ";
    for (int i = 0; i < ciphertext_len; ++i)
        std::cout << std::hex << (int)ciphertext[i];
    std::cout << "\nCiphertext length: " << ciphertext_len << std::endl;
    std::cout << "Plaintext length: " << plaintext_len << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv)) handleErrors();
    if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
    decrypted_len = len;
    if (1 != EVP_DecryptFinal_ex(ctx, decrypted + len, &len)) handleErrors();
    decrypted_len += len;

    // Null-terminate and print decrypted text
    decrypted[decrypted_len] = '\0';
    std::cout << "Decrypted text: " << decrypted << std::endl;

    EVP_CIPHER_CTX_free(ctx);
    OSSL_PROVIDER_unload(legacy);
    return 0;
}
