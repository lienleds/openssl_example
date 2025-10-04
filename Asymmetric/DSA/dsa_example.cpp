#include <openssl/dsa.h>
#include <openssl/engine.h>
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
    FILE* priv_fp = fopen("dsa_private.pem", "rb");
    if (!priv_fp) { std::cerr << "Cannot open dsa_private.pem for reading!\n"; return 1; }
    DSA* dsa = PEM_read_DSAPrivateKey(priv_fp, NULL, NULL, NULL);
    fclose(priv_fp);
    if (!dsa) handleErrors();

    // 4. Sign a message
    const char* message = "Hello, DSA!";
    unsigned char signature[256];
    unsigned int sig_len = 0;
    if (!DSA_sign(0, (const unsigned char*)message, strlen(message), signature, &sig_len, dsa)) handleErrors();
    std::cout << "Signature (hex): ";
    for (unsigned int i = 0; i < sig_len; ++i)
        std::cout << std::hex << (int)signature[i];
    std::cout << std::endl;

    // 5. Verify the signature với message đã bị thay đổi (giả mạo)
    const char* tampered_message = "Hello, DSA! (tampered)";
    int verify = DSA_verify(0, (const unsigned char*)tampered_message, strlen(tampered_message), signature, sig_len, dsa);
    if (verify == 1)
        std::cout << "Signature is valid!" << std::endl;
    else if (verify == 0)
        std::cout << "Signature is invalid!" << std::endl;
    else
        handleErrors();

    DSA_free(dsa);
    return 0;
}
