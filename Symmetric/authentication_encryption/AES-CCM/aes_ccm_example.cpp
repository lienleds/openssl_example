#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>

int main() {
    // Key and IV sizes for AES-CCM
    const int key_len = 16; // 128-bit key
    const int iv_len = 12;  // 96-bit nonce (recommended for CCM)
    unsigned char key[key_len];
    unsigned char iv[iv_len];
    RAND_bytes(key, key_len);
    RAND_bytes(iv, iv_len);

    // Plaintext and AAD
    const char* plaintext = "OpenSSL AES-CCM Example!";
    const char* aad = "header-data";
    int pt_len = strlen(plaintext);
    int aad_len = strlen(aad);

    // Buffers
    unsigned char ciphertext[128];
    unsigned char tag[16];
    unsigned char decrypted[128];

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ccm(), NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_IVLEN, iv_len, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_TAG, 16, NULL);
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);
    EVP_EncryptUpdate(ctx, NULL, &pt_len, NULL, pt_len);
    EVP_EncryptUpdate(ctx, NULL, &aad_len, (unsigned char*)aad, aad_len);
    int outlen;
    EVP_EncryptUpdate(ctx, ciphertext, &outlen, (unsigned char*)plaintext, pt_len);
    EVP_EncryptFinal_ex(ctx, NULL, &outlen);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_GET_TAG, 16, tag);
    EVP_CIPHER_CTX_free(ctx);

    std::cout << "Ciphertext: ";
    for (int i = 0; i < pt_len; ++i) printf("%02x", ciphertext[i]);
    std::cout << "\nTag: ";
    for (int i = 0; i < 16; ++i) printf("%02x", tag[i]);
    std::cout << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ccm(), NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_IVLEN, iv_len, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_TAG, 16, tag);
    EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);
    EVP_DecryptUpdate(ctx, NULL, &pt_len, NULL, pt_len);
    EVP_DecryptUpdate(ctx, NULL, &aad_len, (unsigned char*)aad, aad_len);
    int len;
    int ret = EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, pt_len);
    EVP_CIPHER_CTX_free(ctx);

    if (ret > 0) {
        decrypted[len] = '\0';
        std::cout << "Decrypted: " << decrypted << std::endl;
    } else {
        std::cout << "Decryption failed!" << std::endl;
    }
    return 0;
}
