# IDEA Encryption Example (OpenSSL)

This folder demonstrates how to use IDEA (International Data Encryption Algorithm) cipher in CBC mode for encryption and decryption using OpenSSL in C++.

## About IDEA (International Data Encryption Algorithm)

IDEA is a symmetric block cipher developed by James Massey and Xuejia Lai at ETH Zurich in 1991. It features:
- **Block Size:** 64 bits (8 bytes) - same as CAST5 and Blowfish
- **Key Size:** Fixed 128 bits (16 bytes) - no variable length
- **Mode:** CBC (Cipher Block Chaining) mode in this example
- **Operations:** Uses XOR, addition mod 2^16, and multiplication mod 2^16+1
- **Rounds:** 8.5 rounds (8 full rounds + output transformation)
- **Legacy Status:** Requires legacy provider in modern OpenSSL versions
- **Patent History:** Was patent-protected until 2012, limiting adoption

## Files

- `idea_example.cpp`: Main example for IDEA-CBC encryption/decryption with comprehensive multi-block demonstration and algorithm details. Loads key and IV from files.
- `idea_create_key.cpp`: Utility to generate a random IDEA key and IV, saving them to `idea_key.bin` and `idea_iv.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/IV generator utility.
- `idea_key.bin`, `idea_iv.bin`: Binary files containing the generated key and IV (created after running key generator).
- `out.txt`: Example output from running the main program (created after running example).
- `idea_create_key`, `idea_example`: Compiled executable files.

## Usage

1. **Generate Key and IV:**

   ```sh
   make -f Makefile.key create
   ```
   This creates `idea_key.bin` (128 bits) and `idea_iv.bin` (64 bits).

2. **Build and Run Example:**

   ```sh
   make
   ./idea_example > out.txt
   cat out.txt
   ```

3. **Clean up:**

   ```sh
   make clean                    # Remove compiled binaries
   make -f Makefile.key clean    # Remove key files and key generator
   ```

## Example Output

The program will encrypt and decrypt a long sample text, displaying:
- Original plaintext about IDEA's history and technical details
- Detailed 64-bit block analysis and breakdown
- PKCS#7 padding demonstration with hex visualization
- CBC mode chaining explanation
- IDEA algorithm technical details (operations, rounds, key schedule)
- Key and IV in hexadecimal format
- Encrypted ciphertext in hexadecimal
- Decrypted plaintext
- Historical significance and patent information

Sample output (abbreviated):
```
=== IDEA-CBC Multi-Block Encryption Example ===
Original text: This is a detailed IDEA (International Data Encryption Algorithm) example that showcases how this patented Swiss algorithm handles multi-block encryption...
Text length: 780 bytes

=== Block Analysis ===
IDEA block size: 64 bits (8 bytes)
Number of complete blocks: 97
Remaining bytes in last block: 4
Total blocks after padding: 98
Expected ciphertext length: 784 bytes

Block Breakdown (first 6 blocks shown):
Block  1 [bytes   0-  7]: "This is "
Block  2 [bytes   8- 15]: "a detail"
Block  3 [bytes  16- 23]: "ed IDEA "
...

=== IDEA Algorithm Details ===
• IDEA uses three different operations for confusion and diffusion:
  - XOR (⊕): Bitwise exclusive OR
  - Addition modulo 2^16: Integer addition with wraparound
  - Multiplication modulo 2^16+1: Multiplication in finite field
• 8.5 rounds of encryption (8 full rounds + 1 output transformation)
• Key schedule generates 52 subkeys from the 128-bit master key

=== Historical Significance ===
• Developed in Switzerland (ETH Zurich) by Massey and Lai (1991)
• Used in PGP (Pretty Good Privacy) for many years
• Was patent-protected until 2012 (limited adoption)
• Considered very secure but replaced by AES due to patents and performance
```

## Troubleshooting

**Error: "Cannot open idea_key.bin or idea_iv.bin!"**
- Solution: Run `make -f Makefile.key create` first to generate the key files.

**Error: "Failed to load legacy provider!"**
- Solution: Ensure you have a modern OpenSSL installation that supports the legacy provider.
- IDEA requires the legacy provider in OpenSSL 3.0+

**Compilation errors:**
- Ensure OpenSSL development headers are installed: `brew install openssl` (macOS)
- Adjust paths in Makefile if using Intel Mac (change `/opt/homebrew` to `/usr/local`)

**IDEA cipher not found:**
- IDEA is in the legacy provider, ensure it's available
- Test with: `openssl list -cipher-algorithms | grep -i idea`

## Technical Details

### Algorithm Operations
IDEA's strength comes from mixing three incompatible mathematical operations:
1. **XOR (⊕)**: Bitwise exclusive OR operation
2. **Addition modulo 2^16**: Integer addition with wraparound at 65536
3. **Multiplication modulo 2^16+1**: Multiplication in the finite field GF(2^16+1)

### Key Schedule
- Takes a 128-bit master key and generates 52 subkeys (16 bits each)
- Uses bit rotation and selection to create encryption subkeys
- Decryption subkeys are derived from encryption subkeys using multiplicative and additive inverses

### Security Properties
- Designed to be resistant to differential and linear cryptanalysis
- No known practical attacks against the full algorithm
- 64-bit block size limits security with large amounts of data (birthday paradox)

## Security Considerations

- IDEA is still considered cryptographically secure
- The 64-bit block size makes it vulnerable to birthday attacks with large amounts of data (same limitation as CAST5 and Blowfish)
- Always use a unique IV for each encryption operation
- Never reuse the same key-IV pair for different messages
- Consider using modern algorithms like AES for new applications
- Patent restrictions limited adoption until 2012

## Algorithm Comparison

| Feature | IDEA | AES-128 | Camellia-128 | CAST5 | Blowfish |
|---------|------|---------|-------------|--------|----------|
| Block Size | 64 bits | 128 bits | 128 bits | 64 bits | 64 bits |
| Key Size | 128 bits (fixed) | 128 bits | 128 bits | 40-128 bits | 32-448 bits |
| Rounds | 8.5 | 10 | 18 | 12/16 | 16 |
| Year | 1991 | 2001 | 2000 | 1996 | 1993 |
| Standard | No formal standard | NIST FIPS 197 | ISO/IEC 18033-3 | RFC 2144 | No formal |
| Patents | Expired 2012 | Royalty-free | Royalty-free | No patents | No patents |
| Provider | Legacy | Default | Default | Legacy | Legacy |
| Performance | Medium | High | High | Medium | Medium |
| PGP Usage | Yes (historically) | Yes (current) | No | Some versions | Some versions |

## Historical Context

IDEA has significant historical importance in cryptography:

### Development
- Created at ETH Zurich as part of PhD research
- Originally called IPES (Improved Proposed Encryption Standard)
- Renamed to IDEA in 1992

### Adoption and Usage
- **PGP Integration**: Became the standard cipher in PGP 2.0 and later versions
- **Patent Issues**: Mediacrypt AG held patents, requiring licensing for commercial use
- **Academic Use**: Free for non-commercial and academic purposes
- **Industry Impact**: Patent restrictions led many to choose other algorithms

### Legacy
- Influenced development of other block ciphers
- Demonstrated importance of mixing different algebraic operations
- Showed how patent restrictions can limit cryptographic adoption
- Now primarily of historical and educational interest

IDEA represents an important chapter in cryptographic history, demonstrating both excellent algorithm design and the impact of intellectual property on cryptographic adoption.