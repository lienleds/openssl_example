#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <cstring>
#include <iostream>

void handleErrors()
{
    ERR_print_errors_fp(stderr);
    exit(1);
}

int main()
{
    // 1. Load private key from file
    FILE* priv_fp = fopen("private_key.pem", "rb");
    if (!priv_fp) { std::cerr << "Cannot open private_key.pem for reading!\n"; return 1; }
    RSA* rsa = PEM_read_RSAPrivateKey(priv_fp, NULL, NULL, NULL);
    fclose(priv_fp);
    if (!rsa) handleErrors();

    // 4. Prepare plaintext
    const char* plaintext = "Hello, RSA!";
    int plaintext_len = strlen(plaintext);
    unsigned char encrypted[256];
    unsigned char decrypted[256];

    // 5. Encrypt with public key
    int enc_len = RSA_public_encrypt(plaintext_len, (const unsigned char*)plaintext, encrypted, rsa, RSA_PKCS1_OAEP_PADDING);
    if (enc_len == -1) handleErrors();
    std::cout << "Encrypted (hex): ";
    for (int i = 0; i < enc_len; ++i)
        std::cout << std::hex << (int)encrypted[i];
    std::cout << std::endl;

    // 6. Decrypt with private key
    int dec_len = RSA_private_decrypt(enc_len, encrypted, decrypted, rsa, RSA_PKCS1_OAEP_PADDING);
    if (dec_len == -1) handleErrors();
    decrypted[dec_len] = '\0';
    std::cout << "Decrypted: " << decrypted << std::endl;

    RSA_free(rsa);
    return 0;
}
