#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>

int main() {
    // Key and IV sizes for 3DES
    const int key_len = 24; // 3DES uses 24 bytes (192 bits)
    const int iv_len = 8;   // 3DES block size is 8 bytes
    unsigned char key[key_len];
    unsigned char iv[iv_len];
    
    // Load key from file
    FILE* key_file = fopen("des3_key.bin", "rb");
    if (!key_file)
    {
        std::cerr << "Error: Cannot open des3_key.bin for reading." << std::endl;
        return 1;
    }

    if (fread(key, 1, key_len, key_file) != key_len)
    {
        std::cerr << "Error: Failed to read 3DES key from file." << std::endl;
        fclose(key_file);
        return 1;
    }
    fclose(key_file);

    // Load IV from file
    FILE* iv_file = fopen("des3_iv.bin", "rb");
    if (!iv_file)
    {
        std::cerr << "Error: Cannot open des3_iv.bin for reading." << std::endl;
        return 1;
    }

    if (fread(iv, 1, iv_len, iv_file) != iv_len)
    {
        std::cerr << "Error: Failed to read 3DES IV from file." << std::endl;
        fclose(iv_file);
        return 1;
    }
    fclose(iv_file);

    // Plaintext
    const char* plaintext = "OpenSSL 3DES Example!";
    int pt_len = strlen(plaintext);
    unsigned char ciphertext[128];
    unsigned char decrypted[128];

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key, iv);
    int outlen1, outlen2;
    EVP_EncryptUpdate(ctx, ciphertext, &outlen1, (unsigned char*)plaintext, pt_len);
    EVP_EncryptFinal_ex(ctx, ciphertext + outlen1, &outlen2);
    int ct_len = outlen1 + outlen2;
    EVP_CIPHER_CTX_free(ctx);

    std::cout << "Ciphertext: ";
    for (int i = 0; i < ct_len; ++i) printf("%02x", ciphertext[i]);
    std::cout << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key, iv);
    int declen1, declen2;
    EVP_DecryptUpdate(ctx, decrypted, &declen1, ciphertext, ct_len);
    EVP_DecryptFinal_ex(ctx, decrypted + declen1, &declen2);
    decrypted[declen1 + declen2] = '\0';
    EVP_CIPHER_CTX_free(ctx);

    std::cout << "Decrypted: " << decrypted << std::endl;
    return 0;
}
