#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>

void handleErrors()
{
    ERR_print_errors_fp(stderr);
    exit(1);
}

int main()
{
    // 1. Generate RSA key pair
    int bits = 2048;
    unsigned long e = RSA_F4;
    RSA* rsa = RSA_new();
    BIGNUM* bn = BN_new();
    if (!BN_set_word(bn, e)) handleErrors();
    if (!RSA_generate_key_ex(rsa, bits, bn, NULL)) handleErrors();
    BN_free(bn);

    // 2. Save private key to file
    FILE* priv_fp = fopen("private_key.pem", "wb");
    if (!priv_fp) { std::cerr << "Cannot open private_key.pem for writing!\n"; return 1; }
    if (!PEM_write_RSAPrivateKey(priv_fp, rsa, NULL, NULL, 0, NULL, NULL)) handleErrors();
    fclose(priv_fp);

    // 3. Save public key to file
    FILE* pub_fp = fopen("public_key.pem", "wb");
    if (!pub_fp) { std::cerr << "Cannot open public_key.pem for writing!\n"; return 1; }
    if (!PEM_write_RSA_PUBKEY(pub_fp, rsa)) handleErrors();
    fclose(pub_fp);

    std::cout << "Keys generated and saved to private_key.pem and public_key.pem" << std::endl;
    RSA_free(rsa);
    return 0;
}
