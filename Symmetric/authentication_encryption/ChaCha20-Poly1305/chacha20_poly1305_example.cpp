#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>

int main() {
    // Key and nonce sizes for ChaCha20-Poly1305
    const int key_len = 32; // 256-bit key
    const int nonce_len = 12; // 96-bit nonce
    unsigned char key[key_len];
    unsigned char nonce[nonce_len];
    RAND_bytes(key, key_len);
    RAND_bytes(nonce, nonce_len);

    // Plaintext and AAD
    const char* plaintext = "OpenSSL ChaCha20-Poly1305 Example!";
    const char* aad = "header-data";
    int pt_len = strlen(plaintext);
    int aad_len = strlen(aad);

    // Buffers
    unsigned char ciphertext[128];
    unsigned char tag[16];
    unsigned char decrypted[128];

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_chacha20_poly1305(), NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, nonce_len, NULL);
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, nonce);
    int outlen;
    EVP_EncryptUpdate(ctx, NULL, &outlen, (unsigned char*)aad, aad_len); // AAD
    EVP_EncryptUpdate(ctx, ciphertext, &outlen, (unsigned char*)plaintext, pt_len);
    int ciphertext_len = outlen;
    EVP_EncryptFinal_ex(ctx, ciphertext + outlen, &outlen);
    ciphertext_len += outlen;
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, 16, tag);
    EVP_CIPHER_CTX_free(ctx);

    std::cout << "Ciphertext: ";
    for (int i = 0; i < ciphertext_len; ++i) printf("%02x", ciphertext[i]);
    std::cout << "\nTag: ";
    for (int i = 0; i < 16; ++i) printf("%02x", tag[i]);
    std::cout << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_chacha20_poly1305(), NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, nonce_len, NULL);
    EVP_DecryptInit_ex(ctx, NULL, NULL, key, nonce);
    EVP_DecryptUpdate(ctx, NULL, &outlen, (unsigned char*)aad, aad_len); // AAD
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, 16, tag);
    int len;
    int ret = EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len);
    if (ret > 0 && EVP_DecryptFinal_ex(ctx, decrypted + len, &outlen) > 0) {
        decrypted[len + outlen] = '\0';
        std::cout << "Decrypted: " << decrypted << std::endl;
    } else {
        std::cout << "Decryption failed!" << std::endl;
    }
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
