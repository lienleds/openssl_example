#include <openssl/dh.h>
#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <iostream>
#include <cstring>

void handleErrors()
{
    ERR_print_errors_fp(stderr);
    exit(1);
}

int main()
{
    // 1. Load DH parameters from file
    FILE* priv_fp = fopen("dh_private.pem", "rb");
    if (!priv_fp) { std::cerr << "Cannot open dh_private.pem for reading!\n"; return 1; }
    DH* dh1 = PEM_read_DHparams(priv_fp, NULL, NULL, NULL);
    fclose(priv_fp);
    if (!dh1) handleErrors();
    if (!DH_generate_key(dh1)) handleErrors();

    // 2. Copy parameters to second party
    DH* dh2 = DHparams_dup(dh1);
    if (!dh2) handleErrors();
    if (!DH_generate_key(dh2)) handleErrors();

    // 3. Exchange public keys and compute shared secrets
    const BIGNUM* pub_key1 = nullptr;
    const BIGNUM* pub_key2 = nullptr;
    DH_get0_key(dh1, &pub_key1, NULL);
    DH_get0_key(dh2, &pub_key2, NULL);

    unsigned char secret1[256];
    unsigned char secret2[256];
    int secret1_len = DH_compute_key(secret1, pub_key2, dh1);
    int secret2_len = DH_compute_key(secret2, pub_key1, dh2);

    if (secret1_len != secret2_len || memcmp(secret1, secret2, secret1_len) != 0)
    {
        std::cout << "Shared secrets do NOT match!" << std::endl;
    }
    else
    {
        std::cout << "Shared secret (hex): ";
        for (int i = 0; i < secret1_len; ++i)
            std::cout << std::hex << (int)secret1[i];
        std::cout << std::endl;
    }

    DH_free(dh1);
    DH_free(dh2);
    return 0;
}
