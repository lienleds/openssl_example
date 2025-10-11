#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>
#include <iomanip>

void handleErrors()
{
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

void printHex(const unsigned char* data, int len, const std::string& label)
{
    std::cout << label << ": ";
    for (int i = 0; i < len; ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)data[i];
        if ((i + 1) % 16 == 0 && i + 1 < len) std::cout << "\n" + std::string(label.length() + 2, ' ');
    }
    std::cout << std::dec << std::endl;
}

void analyzeBlocks(const char* text, int len)
{
    std::cout << "\n=== Block Analysis ===" << std::endl;
    std::cout << "Camellia block size: 128 bits (16 bytes)" << std::endl;
    std::cout << "Text length: " << len << " bytes" << std::endl;
    
    int full_blocks = len / 16;
    int remaining_bytes = len % 16;
    
    std::cout << "Number of complete 16-byte blocks: " << full_blocks << std::endl;
    std::cout << "Remaining bytes in last block: " << remaining_bytes << std::endl;
    std::cout << "Padding needed: " << (16 - remaining_bytes) << " bytes" << std::endl;
    std::cout << "Total encrypted length: " << ((full_blocks + 1) * 16) << " bytes" << std::endl;
    
    std::cout << "\nBlock breakdown:" << std::endl;
    for (int i = 0; i < full_blocks; ++i) {
        std::cout << "Block " << (i + 1) << " (bytes " << (i * 16) << "-" << (i * 16 + 15) << "): \"";
        for (int j = 0; j < 16; ++j) {
            char c = text[i * 16 + j];
            std::cout << (isprint(c) ? c : '.');
        }
        std::cout << "\"" << std::endl;
    }
    
    if (remaining_bytes > 0) {
        std::cout << "Block " << (full_blocks + 1) << " (bytes " << (full_blocks * 16) << "-" << (len - 1) << " + padding): \"";
        for (int j = 0; j < remaining_bytes; ++j) {
            char c = text[full_blocks * 16 + j];
            std::cout << (isprint(c) ? c : '.');
        }
        std::cout << "\" + " << (16 - remaining_bytes) << " padding bytes" << std::endl;
    }
}

int main()
{
    // Load key and IV from files
    unsigned char key[16]; // Camellia-128 key (16 bytes)
    unsigned char iv[16];  // Camellia IV (16 bytes for CBC mode)
    
    FILE* fkey = fopen("camellia_key.bin", "rb");
    FILE* fiv = fopen("camellia_iv.bin", "rb");
    if (!fkey || !fiv)
    {
        std::cerr << "Cannot open camellia_key.bin or camellia_iv.bin!\n";
        std::cerr << "Please run 'make -f Makefile.key create' to generate keys first.\n";
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

    // Test different text lengths
    const char* texts[] = {
        "Short",                                                    // 5 bytes - less than 1 block
        "Exactly16BytesX",                                         // 16 bytes - exactly 1 block  
        "This text is longer than one block",                     // 34 bytes - more than 2 blocks
        "This is a very long text that spans multiple blocks to demonstrate how Camellia handles data longer than 128 bits" // 115 bytes
    };
    
    for (int test = 0; test < 4; ++test) {
        const char* plaintext = texts[test];
        int plaintext_len = strlen(plaintext);
        unsigned char ciphertext[1024];
        unsigned char decrypted[1024];
        int len = 0, ciphertext_len = 0, decrypted_len = 0;

        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "TEST " << (test + 1) << ": " << plaintext_len << "-byte text" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        std::cout << "Original text: \"" << plaintext << "\"" << std::endl;
        
        analyzeBlocks(plaintext, plaintext_len);

        // Encrypt
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) handleErrors();

        if (1 != EVP_EncryptInit_ex(ctx, EVP_camellia_128_cbc(), NULL, key, iv)) handleErrors();
        if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, 
                                  reinterpret_cast<const unsigned char*>(plaintext), 
                                  plaintext_len)) handleErrors();
        ciphertext_len = len;
        if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
        ciphertext_len += len;

        EVP_CIPHER_CTX_free(ctx);

        std::cout << "\nEncryption Results:" << std::endl;
        printHex(ciphertext, ciphertext_len, "Ciphertext (hex)");
        std::cout << "Ciphertext length: " << ciphertext_len << " bytes (" << (ciphertext_len * 8) << " bits)" << std::endl;

        // Decrypt
        ctx = EVP_CIPHER_CTX_new();
        if (!ctx) handleErrors();

        if (1 != EVP_DecryptInit_ex(ctx, EVP_camellia_128_cbc(), NULL, key, iv)) handleErrors();
        if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
        decrypted_len = len;
        if (1 != EVP_DecryptFinal_ex(ctx, decrypted + len, &len)) handleErrors();
        decrypted_len += len;

        // Null-terminate and verify
        decrypted[decrypted_len] = '\0';
        std::cout << "Decrypted text: \"" << decrypted << "\"" << std::endl;
        std::cout << "Decrypted length: " << decrypted_len << " bytes" << std::endl;
        
        if (strcmp(plaintext, reinterpret_cast<const char*>(decrypted)) == 0)
            std::cout << "✓ Encryption/Decryption successful!" << std::endl;
        else
            std::cout << "✗ Encryption/Decryption failed!" << std::endl;

        EVP_CIPHER_CTX_free(ctx);
    }
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "KEY OBSERVATIONS:" << std::endl;
    std::cout << "1. All ciphertext lengths are multiples of 16 bytes (block size)" << std::endl;
    std::cout << "2. Even 16-byte plaintext becomes 32 bytes due to PKCS#7 padding" << std::endl;
    std::cout << "3. CBC mode chains blocks together for security" << std::endl;
    std::cout << "4. Longer texts are divided into multiple 16-byte blocks" << std::endl;
    std::cout << std::string(80, '=') << std::endl;

    return 0;
}