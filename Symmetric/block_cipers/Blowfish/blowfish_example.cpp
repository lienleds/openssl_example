#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/provider.h>
#include <cstring>
#include <iostream>
#include <iomanip>

void handleErrors()
{
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

int main()
{
    // Load legacy provider for Blowfish support
    OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
    if (!legacy)
    {
        std::cerr << "Failed to load legacy provider!" << std::endl;
        return 1;
    }

    // Load key and IV from files
    unsigned char key[16]; // Blowfish key (can be variable length, 16 bytes here)
    unsigned char iv[8];   // Blowfish IV (8 bytes for CBC mode)
    
    FILE* fkey = fopen("blowfish_key.bin", "rb");
    FILE* fiv = fopen("blowfish_iv.bin", "rb");
    if (!fkey || !fiv)
    {
        std::cerr << "Cannot open blowfish_key.bin or blowfish_iv.bin!\n";
        std::cerr << "Please run 'make -f Makefile.key' to generate keys first.\n";
        return 1;
    }
    
    if (fread(key, 1, sizeof(key), fkey) != sizeof(key) || 
        fread(iv, 1, sizeof(iv), fiv) != sizeof(iv))
    {
        std::cerr << "Failed to read key or IV from file!\n";
        fclose(fkey);
        fclose(fiv);
        return 1;
    }
    fclose(fkey);
    fclose(fiv);

    // Data to encrypt
    const char* plaintext = "This is Blowfish encryption example!";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[128];
    unsigned char decrypted[128];
    int len = 0, ciphertext_len = 0, decrypted_len = 0;

    std::cout << "=== Blowfish Encryption/Decryption Example ===" << std::endl;
    std::cout << "Original text: " << plaintext << std::endl;
    std::cout << "Text length: " << plaintext_len << " bytes" << std::endl;

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_bf_cbc(), NULL, key, iv)) handleErrors();
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, 
                              reinterpret_cast<const unsigned char*>(plaintext), 
                              plaintext_len)) handleErrors();
    ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Print key, IV, and ciphertext in hexadecimal
    std::cout << "\nKey (hex): ";
    for (int i = 0; i < sizeof(key); ++i)
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)key[i];
    
    std::cout << "\nIV (hex): ";
    for (int i = 0; i < sizeof(iv); ++i)
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)iv[i];
    
    std::cout << "\nCiphertext (hex): ";
    for (int i = 0; i < ciphertext_len; ++i)
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)ciphertext[i];
    
    std::cout << std::dec << "\nCiphertext length: " << ciphertext_len << " bytes" << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_bf_cbc(), NULL, key, iv)) handleErrors();
    if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
    decrypted_len = len;
    if (1 != EVP_DecryptFinal_ex(ctx, decrypted + len, &len)) handleErrors();
    decrypted_len += len;

    // Null-terminate and print decrypted text
    decrypted[decrypted_len] = '\0';
    std::cout << "\nDecrypted text: " << decrypted << std::endl;
    std::cout << "Decrypted length: " << decrypted_len << " bytes" << std::endl;

    // Verify decryption
    if (strcmp(plaintext, reinterpret_cast<const char*>(decrypted)) == 0)
        std::cout << "\n✓ Encryption/Decryption successful!" << std::endl;
    else
        std::cout << "\n✗ Encryption/Decryption failed!" << std::endl;

    EVP_CIPHER_CTX_free(ctx);
    OSSL_PROVIDER_unload(legacy);
    return 0;
}