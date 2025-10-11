#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>
#include <cstdio>

void handleErrors()
{
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

int main()
{
    // RC4 key (128 bits)
    unsigned char key[16];
    FILE* kf = fopen("rc4_key.bin", "rb");
    if (!kf)
    {
        std::cerr << "Cannot open rc4_key.bin for reading!" << std::endl;
        return 1;
    }
    if (fread(key, 1, sizeof(key), kf) != sizeof(key))
    {
        std::cerr << "Error reading RC4 key from file!" << std::endl;
        fclose(kf);
        return 1;
    }
    fclose(kf);

    // Data
    const char* plaintext = "This is RC4 example";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[128];
    unsigned char decrypted[128];
    int len = 0, ciphertext_len = 0, decrypted_len = 0;

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, EVP_rc4(), NULL, key, NULL)) handleErrors();
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, reinterpret_cast<const unsigned char*>(plaintext), plaintext_len)) handleErrors();
    ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    std::cout << "Key: ";
    for (int i = 0; i < 16; ++i) std::cout << std::hex << (int)key[i];
    std::cout << "\nCiphertext: ";
    for (int i = 0; i < ciphertext_len; ++i) std::cout << std::hex << (int)ciphertext[i];
    std::cout << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();
    if (1 != EVP_DecryptInit_ex(ctx, EVP_rc4(), NULL, key, NULL)) handleErrors();
    if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
    decrypted_len = len;
    if (1 != EVP_DecryptFinal_ex(ctx, decrypted + len, &len)) handleErrors();
    decrypted_len += len;
    decrypted[decrypted_len] = '\0';
    std::cout << "Decrypted: " << decrypted << std::endl;
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
