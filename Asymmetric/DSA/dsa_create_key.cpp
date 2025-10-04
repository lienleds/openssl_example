#include <openssl/dsa.h>
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
    // 1. Generate DSA parameters and key
    DSA* dsa = DSA_new();
    if (!DSA_generate_parameters_ex(dsa, 2048, NULL, 0, NULL, NULL, NULL)) handleErrors();
    if (!DSA_generate_key(dsa)) handleErrors();

    // 2. Save private key
    FILE* priv_fp = fopen("dsa_private.pem", "wb");
    if (!priv_fp) { std::cerr << "Cannot open dsa_private.pem for writing!\n"; return 1; }
    if (!PEM_write_DSAPrivateKey(priv_fp, dsa, NULL, NULL, 0, NULL, NULL)) handleErrors();
    fclose(priv_fp);

    // 3. Save public key
    FILE* pub_fp = fopen("dsa_public.pem", "wb");
    if (!pub_fp) { std::cerr << "Cannot open dsa_public.pem for writing!\n"; return 1; }
    if (!PEM_write_DSA_PUBKEY(pub_fp, dsa)) handleErrors();
    fclose(pub_fp);

    std::cout << "DSA keys generated and saved to dsa_private.pem and dsa_public.pem" << std::endl;
    DSA_free(dsa);
    return 0;
}
