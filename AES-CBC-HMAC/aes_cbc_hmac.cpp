#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/hmac.h>
#include <cstring>
#include <iostream>

void handleErrors() {
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

int main()
{
    // Key and IV
    unsigned char key[16];      // 128-bit key
    unsigned char hmac_key[32]; // 256-bit key for HMAC
    unsigned char iv[16];       // 128-bit IV for CBC
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(hmac_key, sizeof(hmac_key)) || !RAND_bytes(iv, sizeof(iv))) handleErrors();

    // Data
    const char* plaintext = "This is AES CBC";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[128];
    // No tag needed for CBC

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, NULL, NULL)) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();

    int len;
    int ciphertext_len;
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext, plaintext_len)) handleErrors();
    ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    std::cout << "Key: ";
    for (int i = 0; i < 16; ++i) std::cout << std::hex << (int)key[i];
    std::cout << "\nHMAC Key: ";
    for (int i = 0; i < 32; ++i) std::cout << std::hex << (int)hmac_key[i];
    std::cout << "\nIV: ";
    for (int i = 0; i < 16; ++i) std::cout << std::hex << (int)iv[i];
    std::cout << "\nCiphertext: ";
    for (int i = 0; i < ciphertext_len; ++i) std::cout << std::hex << (int)ciphertext[i];

    // Calculate HMAC over (IV + ciphertext)
    unsigned char hmac[EVP_MAX_MD_SIZE];
    unsigned int hmac_len;
    HMAC(EVP_sha256(), hmac_key, sizeof(hmac_key), iv, sizeof(iv), hmac, &hmac_len);
    std::cout << "\nHMAC1: ";
    for (unsigned int i = 0; i < hmac_len; ++i) std::cout << std::hex << (int)hmac[i];
    HMAC(EVP_sha256(), hmac_key, sizeof(hmac_key), ciphertext, ciphertext_len, hmac, &hmac_len);
    std::cout << "\nHMAC2: ";
    for (unsigned int i = 0; i < hmac_len; ++i) std::cout << std::hex << (int)hmac[i];
    std::cout << std::endl;

    EVP_CIPHER_CTX_free(ctx);

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, NULL, NULL)) handleErrors();
    if (1 != EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();
    unsigned char decrypted[128];
    if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
    int decrypted_len = len;
    int ret = EVP_DecryptFinal_ex(ctx, decrypted + len, &len);
    if (ret > 0)
    {
        decrypted_len += len;
        decrypted[decrypted_len] = '\0';
        std::cout << "Decrypted: " << decrypted << std::endl;
    }
    else
    {
        std::cout << "Decryption failed!" << std::endl;
    }
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
