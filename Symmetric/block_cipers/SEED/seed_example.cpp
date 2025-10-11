#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/provider.h>
#include <openssl/err.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

void handleErrors()
{
    unsigned long err = ERR_get_error();
    if (err) {
        char err_buf[256];
        ERR_error_string_n(err, err_buf, sizeof(err_buf));
        std::cerr << "OpenSSL Error: " << err_buf << std::endl;
    } else {
        std::cerr << "Unknown error occurred!" << std::endl;
    }
    exit(1);
}

void demonstratePadding(const char* text, int len)
{
    std::cout << "\n=== PKCS#7 Padding Demonstration ===" << std::endl;
    
    int remaining = len % 16;  // SEED uses 16-byte blocks
    int padding_needed = 16 - remaining;
    
    std::cout << "Last block content (before padding):" << std::endl;
    std::cout << "Bytes: ";
    
    int last_block_start = (len / 16) * 16;
    for (int i = 0; i < remaining; ++i) {
        std::cout << "'" << text[last_block_start + i] << "' ";
    }
    std::cout << std::endl;
    
    std::cout << "Hex:   ";
    for (int i = 0; i < remaining; ++i) {
        std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2) 
                  << (int)(unsigned char)text[last_block_start + i] << " ";
    }
    std::cout << std::dec << std::endl;
    
    std::cout << "\nPadding added:" << std::endl;
    std::cout << "Padding bytes needed: " << padding_needed << std::endl;
    std::cout << "Padding value: 0x" << std::hex << std::setfill('0') << std::setw(2) 
              << padding_needed << std::dec << " (decimal " << padding_needed << ")" << std::endl;
    
    std::cout << "\nComplete last block after padding:" << std::endl;
    std::cout << "Position: ";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::setw(2) << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Content:  ";
    for (int i = 0; i < remaining; ++i) {
        std::cout << " " << text[last_block_start + i] << " ";
    }
    for (int i = 0; i < padding_needed; ++i) {
        std::cout << std::setw(2) << padding_needed << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Hex:      ";
    for (int i = 0; i < remaining; ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) 
                  << (int)(unsigned char)text[last_block_start + i] << " ";
    }
    for (int i = 0; i < padding_needed; ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << padding_needed << " ";
    }
    std::cout << std::dec << std::endl;
}

int main()
{
    // Load both default and legacy providers to ensure SEED is available
    OSSL_PROVIDER *default_prov = OSSL_PROVIDER_load(NULL, "default");
    OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
    
    if (!default_prov) {
        std::cerr << "Failed to load default provider!" << std::endl;
        return 1;
    }
    
    if (!legacy) {
        std::cerr << "Warning: Failed to load legacy provider, continuing with default only." << std::endl;
    }

    // Load key and IV from files
    unsigned char key[16]; // SEED key (128 bits)
    unsigned char iv[16];  // SEED IV (128 bits for CBC mode)
    
    FILE* fkey = fopen("seed_key.bin", "rb");
    FILE* fiv = fopen("seed_iv.bin", "rb");
    if (!fkey || !fiv)
    {
        std::cerr << "Cannot open seed_key.bin or seed_iv.bin!\n";
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

    // Data to encrypt - SEED demonstration text with padding demonstration
    const char* plaintext = "This is a comprehensive SEED encryption example demonstrating the Korean cryptographic algorithm KISA-SEED-128. "
                           "SEED was developed by the Korea Information Security Agency (KISA) in 1998 as a national standard. "
                           "The algorithm uses 128-bit blocks and 128-bit keys with a Feistel structure operating over 16 rounds. "
                           "SEED was designed to replace DES in Korean applications, emphasizing security and efficiency. "
                           "It became ISO/IEC 18033-3 in 2005, demonstrating Korean cryptographic expertise!";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[1024];  // Buffer for multi-block text
    unsigned char decrypted[1024];   // Buffer for multi-block text
    int len = 0, ciphertext_len = 0, decrypted_len = 0;

    std::cout << "=== SEED-CBC Multi-Block Encryption Example ===" << std::endl;
    std::cout << "Original text: " << plaintext << std::endl;
    std::cout << "Text length: " << plaintext_len << " bytes" << std::endl;
    
    // Block analysis
    int full_blocks = plaintext_len / 16;  // SEED uses 16-byte blocks
    int remaining_bytes = plaintext_len % 16;
    int total_blocks = full_blocks + (remaining_bytes > 0 ? 1 : 0);
    
    std::cout << "\n=== Block Analysis ===" << std::endl;
    std::cout << "SEED block size: 128 bits (16 bytes)" << std::endl;
    std::cout << "Number of complete blocks: " << full_blocks << std::endl;
    std::cout << "Remaining bytes in last block: " << remaining_bytes << std::endl;
    std::cout << "Total blocks after padding: " << total_blocks << std::endl;
    std::cout << "Expected ciphertext length: " << (total_blocks * 16) << " bytes" << std::endl;

    // Fetch the SEED cipher explicitly
    const EVP_CIPHER *cipher = EVP_CIPHER_fetch(NULL, "SEED-CBC", NULL);
    if (!cipher) {
        std::cerr << "SEED cipher not available!" << std::endl;
        if (legacy) OSSL_PROVIDER_unload(legacy);
        OSSL_PROVIDER_unload(default_prov);
        return 1;
    }

    // Encrypt
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv)) handleErrors();
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
    for (int i = 0; i < ciphertext_len; ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)ciphertext[i];
        if ((i + 1) % 32 == 0) std::cout << "\n                  ";  // Line break every 32 bytes
    }
    
    std::cout << std::dec << "\nActual ciphertext length: " << ciphertext_len << " bytes (" << (ciphertext_len / 16) << " blocks)" << std::endl;

    // Decrypt (create fresh context)
    EVP_CIPHER_CTX* decrypt_ctx = EVP_CIPHER_CTX_new();
    if (!decrypt_ctx) handleErrors();

    if (1 != EVP_DecryptInit_ex(decrypt_ctx, cipher, NULL, key, iv)) handleErrors();
    if (1 != EVP_DecryptUpdate(decrypt_ctx, decrypted, &len, ciphertext, ciphertext_len)) handleErrors();
    decrypted_len = len;
    if (1 != EVP_DecryptFinal_ex(decrypt_ctx, decrypted + len, &len)) handleErrors();
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

    std::cout << "\n=== Detailed Block and Padding Explanation ===" << std::endl;
    
    // Show first few blocks visually
    std::cout << "\nBlock Breakdown (first 4 blocks shown):" << std::endl;
    for (int i = 0; i < std::min(4, total_blocks); ++i) {
        std::cout << "Block " << std::setw(2) << (i + 1) << " [bytes " << std::setw(3) << (i * 16) 
                  << "-" << std::setw(3) << std::min((i + 1) * 16 - 1, plaintext_len - 1) << "]: \"";
        
        // Show actual text in this block
        for (int j = 0; j < 16 && (i * 16 + j) < plaintext_len; ++j) {
            char c = plaintext[i * 16 + j];
            std::cout << (isprint(c) ? c : '.');
        }
        
        // Show if this block needs padding
        if (i == total_blocks - 1 && remaining_bytes > 0) {
            std::cout << "\" + " << (16 - remaining_bytes) << " padding bytes";
        } else {
            std::cout << "\"";
        }
        std::cout << std::endl;
    }
    
    if (total_blocks > 4) {
        std::cout << "... (" << (total_blocks - 4) << " more blocks)" << std::endl;
        
        // Show last block if it's different
        int last_block = total_blocks - 1;
        if (last_block >= 4) {
            std::cout << "Block " << std::setw(2) << (last_block + 1) << " [bytes " << std::setw(3) << (last_block * 16) 
                      << "-" << std::setw(3) << (plaintext_len - 1) << "]: \"";
            
            for (int j = 0; j < remaining_bytes; ++j) {
                char c = plaintext[last_block * 16 + j];
                std::cout << (isprint(c) ? c : '.');
            }
            std::cout << "\" + " << (16 - remaining_bytes) << " padding bytes" << std::endl;
        }
    }
    
    // Explain PKCS#7 padding
    std::cout << "\n=== PKCS#7 Padding Explanation ===" << std::endl;
    std::cout << "• Block size: 16 bytes (128 bits)" << std::endl;
    std::cout << "• Text length: " << plaintext_len << " bytes" << std::endl;
    std::cout << "• Bytes in last block: " << remaining_bytes << " bytes" << std::endl;
    std::cout << "• Padding needed: " << (16 - remaining_bytes) << " bytes" << std::endl;
    std::cout << "• PKCS#7 padding value: 0x" << std::hex << std::setfill('0') << std::setw(2) 
              << (16 - remaining_bytes) << std::dec << " (repeated " << (16 - remaining_bytes) << " times)" << std::endl;
    
    // Demonstrate the actual padding
    demonstratePadding(plaintext, plaintext_len);
    
    std::cout << "\n=== CBC Mode Chaining ===" << std::endl;
    std::cout << "• Block 1: PlainBlock₁ ⊕ IV → Encrypt → CipherBlock₁" << std::endl;
    std::cout << "• Block 2: PlainBlock₂ ⊕ CipherBlock₁ → Encrypt → CipherBlock₂" << std::endl;
    std::cout << "• Block 3: PlainBlock₃ ⊕ CipherBlock₂ → Encrypt → CipherBlock₃" << std::endl;
    std::cout << "• ... and so on for all " << total_blocks << " blocks" << std::endl;
    
    std::cout << "\n=== SEED Algorithm Details ===" << std::endl;
    std::cout << "• SEED uses 16 rounds of Feistel network with 128-bit blocks" << std::endl;
    std::cout << "• Fixed 128-bit key length for optimal security/performance balance" << std::endl;
    std::cout << "• Key schedule generates 32 subkeys (2 per round) using rotation and XOR" << std::endl;
    std::cout << "• Two 8×8 S-boxes provide excellent nonlinear transformation" << std::endl;
    std::cout << "• Round function uses F-function with G-function and key mixing" << std::endl;
    std::cout << "• Designed for efficient implementation in both software and hardware" << std::endl;
    
    std::cout << "\n=== Key Observations ===" << std::endl;
    std::cout << "• SEED uses 128-bit (16-byte) blocks, same as AES and Camellia" << std::endl;
    std::cout << "• Fixed 128-bit key provides strong security with good performance" << std::endl;
    std::cout << "• Text longer than 16 bytes is automatically split into multiple blocks" << std::endl;
    std::cout << "• Each 16-byte block is encrypted separately but chained together in CBC mode" << std::endl;
    std::cout << "• PKCS#7 padding ensures the last block is exactly 16 bytes" << std::endl;
    std::cout << "• Ciphertext length is always a multiple of the block size (16 bytes)" << std::endl;
    std::cout << "• Original text length: " << plaintext_len << " bytes → Encrypted length: " << ciphertext_len << " bytes" << std::endl;
    
    std::cout << "\n=== Korean Cryptographic Heritage ===" << std::endl;
    std::cout << "• Developed by KISA (Korea Information Security Agency) in 1998" << std::endl;
    std::cout << "• First Korean-designed block cipher to achieve international recognition" << std::endl;
    std::cout << "• Adopted as Korean national standard KS X 1213 in 1999" << std::endl;
    std::cout << "• Became ISO/IEC 18033-3 international standard in 2005" << std::endl;
    std::cout << "• Designed to replace DES in Korean government and financial systems" << std::endl;
    std::cout << "• Reflects South Korea's commitment to cryptographic sovereignty" << std::endl;
    
    std::cout << "\n=== Security Analysis ===" << std::endl;
    std::cout << "• Resistant to differential cryptanalysis (max probability 2^-52)" << std::endl;
    std::cout << "• Resistant to linear cryptanalysis (max bias 2^-26)" << std::endl;
    std::cout << "• No known practical attacks against full 16-round SEED" << std::endl;
    std::cout << "• S-boxes designed for optimal differential and linear properties" << std::endl;
    std::cout << "• Key schedule prevents related-key attacks" << std::endl;
    std::cout << "• Suitable for applications requiring long-term security" << std::endl;
    
    std::cout << "\n=== International Recognition ===" << std::endl;
    std::cout << "• Included in TLS cipher suites (RFC 4162)" << std::endl;
    std::cout << "• Supported by various cryptographic libraries and standards" << std::endl;
    std::cout << "• Used in Korean e-government and financial applications" << std::endl;
    std::cout << "• Example of successful national cryptographic standard development" << std::endl;
    std::cout << "• Demonstrates Korea's expertise in cryptographic algorithm design" << std::endl;

    if (ctx) EVP_CIPHER_CTX_free(ctx);
    if (decrypt_ctx) EVP_CIPHER_CTX_free(decrypt_ctx);
    if (cipher) EVP_CIPHER_free((EVP_CIPHER*)cipher);
    
    if (legacy) OSSL_PROVIDER_unload(legacy);
    if (default_prov) OSSL_PROVIDER_unload(default_prov);
    return 0;
}