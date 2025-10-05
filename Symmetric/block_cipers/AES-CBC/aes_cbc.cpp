#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>

void handleErrors() {
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

int main()
{
    // Key and IV
    unsigned char key[16]; // 128-bit key for AES
    unsigned char iv[16];  // 128-bit IV for CBC
    // Load key from file
    FILE* kf = fopen("aes_key.bin", "rb");
    if (!kf)
    {
        std::cerr << "Error: Cannot open aes_key.bin for reading!" << std::endl;
        return 1;
    }
    if (fread(key, 1, sizeof(key), kf) != sizeof(key))
    {
        std::cerr << "Error: Failed to read AES key from file!" << std::endl;
        fclose(kf);
        return 1;
    }
    fclose(kf);
    // Load IV from file
    FILE* ivf = fopen("aes_iv.bin", "rb");
    if (!ivf)
    {
        std::cerr << "Error: Cannot open aes_iv.bin for reading!" << std::endl;
        return 1;
    }
    if (fread(iv, 1, sizeof(iv), ivf) != sizeof(iv))
    {
        std::cerr << "Error: Failed to read AES IV from file!" << std::endl;
        fclose(ivf);
        return 1;
    }
    fclose(ivf);

    // Data
    const char* plaintext = "This is AES CBC HMAC";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[128];

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
    std::cout << "\nIV: ";
    for (int i = 0; i < 16; ++i) std::cout << std::hex << (int)iv[i];
    std::cout << "\nCiphertext: ";
    for (int i = 0; i < ciphertext_len; ++i) std::cout << std::hex << (int)ciphertext[i];
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
