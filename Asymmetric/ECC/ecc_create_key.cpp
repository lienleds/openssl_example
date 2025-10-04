#include <openssl/ec.h>
#include <openssl/obj_mac.h>
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
    // 1. Generate EC key pair (using curve prime256v1)
    EC_KEY* ec_key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if (!ec_key) handleErrors();
    if (!EC_KEY_generate_key(ec_key)) handleErrors();

    // 2. Save private key
    FILE* priv_fp = fopen("ec_private.pem", "wb");
    if (!priv_fp) { std::cerr << "Cannot open ec_private.pem for writing!\n"; return 1; }
    if (!PEM_write_ECPrivateKey(priv_fp, ec_key, NULL, NULL, 0, NULL, NULL)) handleErrors();
    fclose(priv_fp);

    // 3. Save public key
    FILE* pub_fp = fopen("ec_public.pem", "wb");
    if (!pub_fp) { std::cerr << "Cannot open ec_public.pem for writing!\n"; return 1; }
    if (!PEM_write_EC_PUBKEY(pub_fp, ec_key)) handleErrors();
    fclose(pub_fp);

    std::cout << "ECC keys generated and saved to ec_private.pem and ec_public.pem" << std::endl;
    EC_KEY_free(ec_key);
    return 0;
}
