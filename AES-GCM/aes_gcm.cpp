#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>

void handleErrors() {
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

int main() {
    // Key and IV
    unsigned char key[16]; // 128-bit key
    unsigned char iv[12];  // 96-bit nonce for GCM
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) handleErrors();

    // Data
    const char* plaintext = "This is AES gcm.";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[128];
    unsigned char tag[16];

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, NULL, NULL)) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();

    int len;
    int ciphertext_len;
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext, plaintext_len)) handleErrors();
    ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag)) handleErrors();

    std::cout << "Key: ";
    for (int i = 0; i < 16; ++i) std::cout << std::hex << (int)key[i];
    std::cout << "\nIV: ";
    for (int i = 0; i < 12; ++i) std::cout << std::hex << (int)iv[i];
    std::cout << "\nCiphertext: ";
    for (int i = 0; i < ciphertext_len; ++i) std::cout << std::hex << (int)ciphertext[i];
    std::cout << "\nTag: ";
    for (int i = 0; i < 16; ++i) std::cout << std::hex << (int)tag[i];
    std::cout << std::endl;

    EVP_CIPHER_CTX_free(ctx);

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, NULL, NULL)) handleErrors();
    if (1 != EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv)) handleErrors();
    unsigned char decrypted[128];
    if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, tag)) handleErrors();
    int ret = EVP_DecryptFinal_ex(ctx, decrypted + len, &len);
    if (ret > 0) {
        decrypted[plaintext_len] = '\0';
        std::cout << "Decrypted: " << decrypted << std::endl;
    } else {
        std::cout << "Decryption failed!" << std::endl;
    }
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
