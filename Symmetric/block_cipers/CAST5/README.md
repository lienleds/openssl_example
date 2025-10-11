# CAST5 Encryption Example (OpenSSL)

This folder demonstrates how to use CAST5 (CAST-128) cipher in CBC mode for encryption and decryption using OpenSSL in C++.

## About CAST5 (CAST-128)

CAST5, also known as CAST-128, is a symmetric block cipher developed by Carlisle Adams and Stafford Tavares. It features:
- **Block Size:** 64 bits (8 bytes) - smaller than modern ciphers
- **Key Size:** Variable length from 40 bits to 128 bits (this example uses 128-bit keys)
- **Mode:** CBC (Cipher Block Chaining) mode in this example
- **Standard:** RFC 2144, used in various applications including PGP
- **Legacy Status:** Requires legacy provider in modern OpenSSL versions

## Files

- `cast5_example.cpp`: Main example for CAST5-CBC encryption/decryption with comprehensive multi-block demonstration. Loads key and IV from files.
- `cast5_create_key.cpp`: Utility to generate a random CAST5 key and IV, saving them to `cast5_key.bin` and `cast5_iv.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/IV generator utility.
- `cast5_key.bin`, `cast5_iv.bin`: Binary files containing the generated key and IV (created after running key generator).
- `out.txt`: Example output from running the main program (created after running example).
- `cast5_create_key`, `cast5_example`: Compiled executable files.

## Usage

1. **Generate Key and IV:**

   ```sh
   make -f Makefile.key create
   ```
   This creates `cast5_key.bin` (128 bits) and `cast5_iv.bin` (64 bits).

2. **Build and Run Example:**

   ```sh
   make
   ./cast5_example > out.txt
   cat out.txt
   ```

3. **Clean up:**

   ```sh
   make clean                    # Remove compiled binaries
   make -f Makefile.key clean    # Remove key files and key generator
   ```

## Example Output

The program will encrypt and decrypt a long sample text, displaying:
- Original plaintext (spans many 8-byte blocks)
- Detailed 64-bit block analysis and breakdown
- PKCS#7 padding demonstration with hex visualization
- CBC mode chaining explanation
- Key and IV in hexadecimal format
- Encrypted ciphertext in hexadecimal
- Decrypted plaintext
- Educational observations about CAST5 vs other block ciphers

Sample output (abbreviated):
```
=== CAST5-CBC Multi-Block Encryption Example ===
Original text: [Long demonstration text spanning multiple blocks...]
Text length: 473 bytes

=== Block Analysis ===
CAST5 block size: 64 bits (8 bytes)
Number of complete blocks: 59
Remaining bytes in last block: 1
Total blocks after padding: 60
Expected ciphertext length: 480 bytes

Block Breakdown (first 6 blocks shown):
Block  1 [bytes   0-  7]: "This is "
Block  2 [bytes   8- 15]: "a compre"
Block  3 [bytes  16- 23]: "hensive "
Block  4 [bytes  24- 31]: "CAST5 en"
Block  5 [bytes  32- 39]: "cryption"
Block  6 [bytes  40- 47]: " example"
... (54 more blocks)
Block 60 [bytes 472-472]: "!" + 7 padding bytes

=== PKCS#7 Padding Demonstration ===
Last block content: '!'
Padding needed: 7 bytes of value 0x07
Complete block: [1 byte] + [7 × 0x07 padding]

=== Key Observations ===
• CAST5 uses 64-bit (8-byte) blocks, smaller than AES/Camellia (128-bit)
• Text longer than 8 bytes is automatically split into multiple blocks
• More blocks needed for same text due to smaller block size
• Original text length: 473 bytes → Encrypted length: 480 bytes
```

## Troubleshooting

**Error: "Cannot open cast5_key.bin or cast5_iv.bin!"**
- Solution: Run `make -f Makefile.key create` first to generate the key files.

**Error: "Failed to load legacy provider!"**
- Solution: Ensure you have a modern OpenSSL installation that supports the legacy provider.
- CAST5 requires the legacy provider in OpenSSL 3.0+

**Compilation errors:**
- Ensure OpenSSL development headers are installed: `brew install openssl` (macOS)
- Adjust paths in Makefile if using Intel Mac (change `/opt/homebrew` to `/usr/local`)

**CAST5 cipher not found:**
- CAST5 is in the legacy provider, ensure it's available
- Test with: `openssl list -cipher-algorithms | grep -i cast`

## Technical Notes

- CAST5 uses a 64-bit block size, which is smaller than modern standards (AES: 128 bits)
- Variable key length support (40-128 bits), this example uses 128-bit keys
- CBC mode requires an Initialization Vector (IV) for security
- The legacy provider must be loaded for CAST5 support in modern OpenSSL versions
- CAST5 generates more blocks than AES/Camellia for the same plaintext due to smaller block size

## Security Considerations

- CAST5 is considered cryptographically secure but is largely superseded by AES
- The 64-bit block size makes it vulnerable to birthday attacks with large amounts of data (same as Blowfish)
- Always use a unique IV for each encryption operation
- Never reuse the same key-IV pair for different messages
- Consider using modern algorithms like AES for new applications
- CAST5 was designed in the 1990s and is primarily of historical interest today

## Algorithm Comparison

| Feature | CAST5 | AES-128 | Camellia-128 | Blowfish |
|---------|-------|---------|-------------|----------|
| Block Size | 64 bits | 128 bits | 128 bits | 64 bits |
| Key Size | 40-128 bits | 128 bits | 128 bits | 32-448 bits |
| Rounds | 12 or 16 | 10 | 18 | 16 |
| Standard | RFC 2144 | NIST FIPS 197 | ISO/IEC 18033-3 | No formal standard |
| Year | 1996 | 2001 | 2000 | 1993 |
| Provider | Legacy | Default | Default | Legacy |
| Performance | Medium | High | High | Medium |

## Historical Context

CAST5 was widely used in the 1990s and early 2000s, particularly in:
- Pretty Good Privacy (PGP) encryption software
- Various VPN implementations
- Legacy cryptographic systems

While secure, it has been largely replaced by AES in modern applications due to AES's larger block size, standardization, and better performance characteristics.