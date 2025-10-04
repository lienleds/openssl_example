#include <openssl/dh.h>
#include <openssl/bn.h>
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
    // 1. Generate DH parameters (2048 bits)
    DH* dh = DH_new();
    if (!dh) handleErrors();
    if (!DH_generate_parameters_ex(dh, 2048, DH_GENERATOR_2, NULL)) handleErrors();
    if (!DH_generate_key(dh)) handleErrors();

    // 2. Save private key
    FILE* priv_fp = fopen("dh_private.pem", "wb");
    if (!priv_fp) { std::cerr << "Cannot open dh_private.pem for writing!\n"; return 1; }
    if (!PEM_write_DHparams(priv_fp, dh)) handleErrors();
    fclose(priv_fp);

    // 3. Save public key
    const BIGNUM* pub_key = nullptr;
    DH_get0_key(dh, &pub_key, NULL);
    FILE* pub_fp = fopen("dh_public.pem", "wb");
    if (!pub_fp) { std::cerr << "Cannot open dh_public.pem for writing!\n"; return 1; }
    if (!BN_print_fp(pub_fp, pub_key)) handleErrors();
    fclose(pub_fp);

    std::cout << "DH parameters and keys saved to dh_private.pem and dh_public.pem" << std::endl;
    DH_free(dh);
    return 0;
}
