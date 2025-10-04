#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
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
    // 1. Load EC private key from file
    FILE* priv_fp = fopen("ec_private.pem", "rb");
    if (!priv_fp) { std::cerr << "Cannot open ec_private.pem for reading!\n"; return 1; }
    EC_KEY* ec_key = PEM_read_ECPrivateKey(priv_fp, NULL, NULL, NULL);
    fclose(priv_fp);
    if (!ec_key) handleErrors();

    // 4. Sign a message
    const char* message = "Hello, ECC!";
    unsigned char signature[256];
    unsigned int sig_len = 0;
    if (!ECDSA_sign(0, (const unsigned char*)message, strlen(message), signature, &sig_len, ec_key)) handleErrors();
    std::cout << "Signature (hex): ";
    for (unsigned int i = 0; i < sig_len; ++i)
        std::cout << std::hex << (int)signature[i];
    std::cout << std::endl;


    // 5. Verify the signature (valid case)
    int verify = ECDSA_verify(0, (const unsigned char*)message, strlen(message), signature, sig_len, ec_key);
    if (verify == 1)
        std::cout << "Signature is valid!" << std::endl;
    else if (verify == 0)
        std::cout << "Signature is invalid!" << std::endl;
    else
        handleErrors();

    // 6. Verify the signature with a tampered message (invalid case)
    const char* tampered_message = "Hello, ECC! (tampered)";
    int verify_invalid = ECDSA_verify(0, (const unsigned char*)tampered_message, strlen(tampered_message), signature, sig_len, ec_key);
    if (verify_invalid == 1)
        std::cout << "[Invalid case] Signature is valid! (unexpected)" << std::endl;
    else if (verify_invalid == 0)
        std::cout << "[Invalid case] Signature is invalid! (expected)" << std::endl;
    else
        handleErrors();

    EC_KEY_free(ec_key);
    return 0;
}
