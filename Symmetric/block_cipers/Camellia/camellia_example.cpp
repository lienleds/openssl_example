#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

void handleErrors()
{
    std::cerr << "Error occurred!" << std::endl;
    exit(1);
}

void demonstratePadding(const char* text, int len)
{
    std::cout << "\n=== PKCS#7 Padding Demonstration ===" << std::endl;
    
    int remaining = len % 16;
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

    // Data to encrypt - Demonstration of multi-block encryption
    const char* plaintext = "This is a very long Camellia encryption example that is much longer than 128 bits (16 bytes). "
                           "Block ciphers like Camellia work on fixed-size blocks of 128 bits each. When the plaintext is longer "
                           "than one block, it gets divided into multiple blocks. In CBC mode, each block is XORed with the previous "
                           "ciphertext block before encryption, creating a chain effect. This is why it's called Cipher Block Chaining!";
    int plaintext_len = strlen(plaintext);
    unsigned char ciphertext[1024];  // Larger buffer for multi-block text
    unsigned char decrypted[1024];   // Larger buffer for multi-block text
    int len = 0, ciphertext_len = 0, decrypted_len = 0;

    std::cout << "=== Camellia-128-CBC Multi-Block Encryption Example ===" << std::endl;
    std::cout << "Original text: " << plaintext << std::endl;
    std::cout << "Text length: " << plaintext_len << " bytes" << std::endl;
    
    // Block analysis
    int full_blocks = plaintext_len / 16;
    int remaining_bytes = plaintext_len % 16;
    int total_blocks = full_blocks + (remaining_bytes > 0 ? 1 : 0);
    
    std::cout << "\n=== Block Analysis ===" << std::endl;
    std::cout << "Camellia block size: 128 bits (16 bytes)" << std::endl;
    std::cout << "Number of complete blocks: " << full_blocks << std::endl;
    std::cout << "Remaining bytes in last block: " << remaining_bytes << std::endl;
    std::cout << "Total blocks after padding: " << total_blocks << std::endl;
    std::cout << "Expected ciphertext length: " << (total_blocks * 16) << " bytes" << std::endl;

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
    
    std::cout << std::dec << "\nActual ciphertext length: " << ciphertext_len << " bytes (" << (ciphertext_len / 16) << " blocks)" << std::endl;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_camellia_128_cbc(), NULL, key, iv)) handleErrors();
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

    std::cout << "\n=== Detailed Block and Padding Explanation ===" << std::endl;
    
    // Show first few blocks visually
    std::cout << "\nBlock Breakdown (first 5 blocks shown):" << std::endl;
    for (int i = 0; i < std::min(5, total_blocks); ++i) {
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
    
    if (total_blocks > 5) {
        std::cout << "... (" << (total_blocks - 5) << " more blocks)" << std::endl;
        
        // Show last block if it's different
        int last_block = total_blocks - 1;
        std::cout << "Block " << std::setw(2) << (last_block + 1) << " [bytes " << std::setw(3) << (last_block * 16) 
                  << "-" << std::setw(3) << (plaintext_len - 1) << "]: \"";
        
        for (int j = 0; j < remaining_bytes; ++j) {
            char c = plaintext[last_block * 16 + j];
            std::cout << (isprint(c) ? c : '.');
        }
        std::cout << "\" + " << (16 - remaining_bytes) << " padding bytes" << std::endl;
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
    
    std::cout << "\n=== Key Observations ===" << std::endl;
    std::cout << "• Text longer than 16 bytes is automatically split into multiple blocks" << std::endl;
    std::cout << "• Each 16-byte block is encrypted separately but chained together in CBC mode" << std::endl;
    std::cout << "• PKCS#7 padding ensures the last block is exactly 16 bytes" << std::endl;
    std::cout << "• Ciphertext length is always a multiple of the block size (16 bytes)" << std::endl;
    std::cout << "• Original text length: " << plaintext_len << " bytes → Encrypted length: " << ciphertext_len << " bytes" << std::endl;

    EVP_CIPHER_CTX_free(ctx);
    return 0;
}