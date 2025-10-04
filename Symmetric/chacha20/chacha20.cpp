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
    // Key and nonce for ChaCha20
    unsigned char key[32];
    unsigned char nonce[12];
    // Generate random key and nonce (or you can set static values for testing)
    if (1 != RAND_bytes(key, sizeof(key))) handleErrors();
    if (1 != RAND_bytes(nonce, sizeof(nonce))) handleErrors();

    // Data
    const char* plaintext = "This is ChaCha20";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[128];
    unsigned char decrypted[128];
    int len = 0, ciphertext_len = 0, decrypted_len = 0;

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_chacha20(), NULL, key, nonce)) handleErrors();
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, reinterpret_cast<const unsigned char*>(plaintext), plaintext_len)) handleErrors();
    ciphertext_len = len;
    // ChaCha20 is a stream cipher, no padding, so EncryptFinal_ex is a no-op but should still be called
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Print key, nonce, and ciphertext
    std::cout << "Key: ";
    for (int i = 0; i < 32; ++i)
        std::cout << std::hex << (int)key[i];
    std::cout << "\nNonce: ";
    for (int i = 0; i < 12; ++i)
        std::cout << std::hex << (int)nonce[i];
    std::cout << "\nCiphertext: ";
    for (int i = 0; i < ciphertext_len; ++i)
        std::cout << std::hex << (int)ciphertext[i];
    std::cout << "\nCiphertext length: " << ciphertext_len << std::endl;
    std::cout << "Plaintext length: " << plaintext_len << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_chacha20(), NULL, key, nonce)) handleErrors();
    if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
    decrypted_len = len;
    // ChaCha20 is a stream cipher, no padding, so DecryptFinal_ex is a no-op but should still be called
    if (1 != EVP_DecryptFinal_ex(ctx, decrypted + len, &len)) handleErrors();
    decrypted_len += len;

    // Null-terminate and print decrypted text
    decrypted[decrypted_len] = '\0';
    std::cout << "Decrypted text: " << decrypted << std::endl;

    EVP_CIPHER_CTX_free(ctx);
    // No provider unload needed for ChaCha20
    return 0;
}
