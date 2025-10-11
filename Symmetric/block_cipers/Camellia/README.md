# Camellia Encryption Example (OpenSSL)

This folder demonstrates how to use Camellia cipher in CBC mode for encryption and decryption using OpenSSL in C++.

## About Camellia

Camellia is a symmetric block cipher developed by Mitsubishi Electric and NTT. It features:
- **Block Size:** 128 bits (16 bytes)
- **Key Sizes:** 128, 192, or 256 bits (this example uses 128-bit keys)
- **Mode:** CBC (Cipher Block Chaining) mode in this example
- **Standard:** ISO/IEC 18033-3, NESSIE, and CRYPTREC approved
- **Performance:** Similar to AES with comparable security

## Files

- `camellia_example.cpp`: Main example for Camellia-128-CBC encryption/decryption with multi-block demonstration. Loads key and IV from files.
- `camellia_block_demo.cpp`: Advanced demonstration showing how different text lengths are handled in block encryption.
- `camellia_create_key.cpp`: Utility to generate a random Camellia key and IV, saving them to `camellia_key.bin` and `camellia_iv.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/IV generator utility.
- `camellia_key.bin`, `camellia_iv.bin`: Binary files containing the generated key and IV (created after running key generator).
- `out.txt`: Example output from running the main program (created after running example).
- `camellia_create_key`, `camellia_example`: Compiled executable files.

## Usage

1. **Generate Key and IV:**

   ```sh
   make -f Makefile.key create
   ```
   This creates `camellia_key.bin` (128 bits) and `camellia_iv.bin` (128 bits).

2. **Build and Run Example:**

   ```sh
   make
   ./camellia_example > out.txt
   cat out.txt
   ```

3. **Advanced Block Analysis (Optional):**

   ```sh
   # Compile and run the detailed block demonstration
   g++ -std=c++11 -Wall -Wextra -I/opt/homebrew/include -o camellia_block_demo camellia_block_demo.cpp -L/opt/homebrew/lib -lssl -lcrypto
   ./camellia_block_demo
   ```
   This shows how texts of different lengths (5, 15, 34, and 113 bytes) are handled.

4. **Clean up:**

   ```sh
   make clean                    # Remove compiled binaries
   make -f Makefile.key clean    # Remove key files and key generator
   rm -f camellia_block_demo     # Remove block demo (if built)
   ```

## Example Output

The program will encrypt and decrypt a sample text, displaying:
- Original plaintext (407 bytes - spans multiple blocks)
- Detailed block analysis and breakdown
- PKCS#7 padding demonstration with hex visualization
- CBC mode chaining explanation
- Key and IV in hexadecimal format
- Encrypted ciphertext in hexadecimal
- Decrypted plaintext
- Educational observations about block cipher mechanics

Sample output (Multi-Block Demonstration):
```
=== Camellia-128-CBC Multi-Block Encryption Example ===
Original text: This is a very long Camellia encryption example that is much longer than 128 bits (16 bytes). Block ciphers like Camellia work on fixed-size blocks of 128 bits each. When the plaintext is longer than one block, it gets divided into multiple blocks. In CBC mode, each block is XORed with the previous ciphertext block before encryption, creating a chain effect. This is why it's called Cipher Block Chaining!
Text length: 407 bytes

=== Block Analysis ===
Camellia block size: 128 bits (16 bytes)
Number of complete blocks: 25
Remaining bytes in last block: 7
Total blocks after padding: 26
Expected ciphertext length: 416 bytes

Key (hex): 3d376fe4d364d61420486c03d33b4dea
IV (hex): d4d8031771e7f46189bc81f57ac2209e
Ciphertext (hex): [416 bytes of encrypted data...]
Actual ciphertext length: 416 bytes (26 blocks)

Decrypted text: [Original 407-byte text successfully recovered]
Decrypted length: 407 bytes

✓ Encryption/Decryption successful!

=== Key Observations ===
• Text longer than 16 bytes is automatically split into multiple blocks
• Each 16-byte block is encrypted separately but chained together in CBC mode
• PKCS#7 padding ensures the last block is exactly 16 bytes
• Ciphertext length is always a multiple of the block size (16 bytes)
• Original text length: 407 bytes → Encrypted length: 416 bytes

=== Detailed Block and Padding Explanation ===
Block Breakdown (first 5 blocks shown):
Block 01: "This is a very l"
Block 02: "ong Camellia enc" 
Block 03: "ryption example "
...
Block 26: "aining!" + 9 padding bytes

=== PKCS#7 Padding Demonstration ===
Last block content: 'a' 'i' 'n' 'i' 'n' 'g' '!'
Padding needed: 9 bytes of value 0x09
Complete block: [original 7 bytes] + [9 × 0x09 padding]

=== CBC Mode Chaining ===
Block₁ ⊕ IV → Encrypt → CipherBlock₁
Block₂ ⊕ CipherBlock₁ → Encrypt → CipherBlock₂
... (chaining continues for all 26 blocks)
```

Note: The key and IV will be different each time you generate new keys, resulting in different ciphertext.

## Troubleshooting

**Error: "Cannot open camellia_key.bin or camellia_iv.bin!"**
- Solution: Run `make -f Makefile.key create` first to generate the key files.

**Compilation errors:**
- Ensure OpenSSL development headers are installed: `brew install openssl` (macOS)
- Adjust paths in Makefile if using Intel Mac (change `/opt/homebrew` to `/usr/local`)

**Camellia cipher not found:**
- Camellia is included in standard OpenSSL builds, but verify your OpenSSL version supports it
- Test with: `openssl list -cipher-algorithms | grep -i camellia`

## Technical Notes

- Camellia-128 uses a 128-bit key and 128-bit block size, same as AES-128
- CBC mode requires an Initialization Vector (IV) for security
- Camellia is considered as secure as AES and is approved by several international standards
- The algorithm was designed to be efficient on both software and hardware implementations
- Camellia supports key sizes of 128, 192, and 256 bits (this example uses 128-bit)

## Security Considerations

- Camellia provides the same level of security as AES
- Always use a unique IV for each encryption operation
- Never reuse the same key-IV pair for different messages
- Camellia is royalty-free and can be used without licensing restrictions
- Consider using authenticated encryption modes (like GCM) for enhanced security in production applications

## Algorithm Comparison

| Feature | Camellia-128 | AES-128 | Blowfish |
|---------|-------------|---------|----------|
| Block Size | 128 bits | 128 bits | 64 bits |
| Key Size | 128 bits | 128 bits | 32-448 bits |
| Rounds | 18 | 10 | 16 |
| Standard | ISO/IEC 18033-3 | NIST FIPS 197 | No formal standard |
| Performance | High | High | Medium |