# RC2 Encryption Example (OpenSSL)

This folder demonstrates how to use RC2 (Rivest Cipher 2) in CBC mode for encryption and decryption using OpenSSL in C++.

## About RC2 (Rivest Cipher 2)

RC2 is a symmetric block cipher designed by Ron Rivest for RSA Data Security in 1987. It features:
- **Block Size:** 64 bits (8 bytes) - same as CAST5, IDEA, and Blowfish
- **Key Size:** Variable length from 8 to 1024 bits (this example uses 128 bits)
- **Mode:** CBC (Cipher Block Chaining) mode in this example
- **Rounds:** 18 rounds of encryption
- **Operations:** XOR, addition, rotation, and S-box table lookup
- **Special Feature:** "Effective key length" parameter for export compliance
- **Legacy Status:** Requires legacy provider in modern OpenSSL versions

## Files

- `rc2_example.cpp`: Main example for RC2-CBC encryption/decryption with comprehensive multi-block demonstration and export compliance discussion. Loads key and IV from files.
- `rc2_create_key.cpp`: Utility to generate a random RC2 key and IV, saving them to `rc2_key.bin` and `rc2_iv.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/IV generator utility.
- `rc2_key.bin`, `rc2_iv.bin`: Binary files containing the generated key and IV (created after running key generator).
- `out.txt`: Example output from running the main program (created after running example).
- `rc2_create_key`, `rc2_example`: Compiled executable files.

## Usage

1. **Generate Key and IV:**

   ```sh
   make -f Makefile.key create
   ```
   This creates `rc2_key.bin` (128 bits) and `rc2_iv.bin` (64 bits).

2. **Build and Run Example:**

   ```sh
   make
   ./rc2_example > out.txt
   cat out.txt
   ```

3. **Clean up:**

   ```sh
   make clean                    # Remove compiled binaries
   make -f Makefile.key clean    # Remove key files and key generator
   ```

## Example Output

The program will encrypt and decrypt a long sample text, displaying:
- Original plaintext about RC2's history and export compliance features
- Detailed 64-bit block analysis and breakdown
- PKCS#7 padding demonstration with hex visualization
- CBC mode chaining explanation
- RC2 algorithm technical details (rounds, operations, key expansion)
- Export compliance feature explanation
- Key and IV in hexadecimal format
- Encrypted ciphertext in hexadecimal
- Decrypted plaintext
- Historical context and Microsoft CryptoAPI usage

Sample output (abbreviated):
```
=== RC2-CBC Multi-Block Encryption Example ===
Original text: This is a comprehensive RC2 (Rivest Cipher 2) encryption example that demonstrates this RSA Data Security algorithm...
Text length: 835 bytes

=== Block Analysis ===
RC2 block size: 64 bits (8 bytes)
Number of complete blocks: 104
Remaining bytes in last block: 3
Total blocks after padding: 105
Expected ciphertext length: 840 bytes

=== RC2 Algorithm Details ===
• RC2 uses 18 rounds of encryption with 64-bit blocks
• Variable key length from 8 to 1024 bits (this example uses 128 bits)
• Key expansion creates 64 16-bit subkeys from the master key
• Features 'effective key length' parameter for export compliance
• Uses simple operations: XOR, addition, rotation, and table lookup

=== Export Compliance Feature ===
• RC2 includes 'effective key length' to comply with export restrictions
• This parameter artificially limits security even with longer keys
• Allowed wider distribution while satisfying 1990s export controls
• Example: 128-bit key with 40-bit effective length for export compliance
```

## Troubleshooting

**Error: "Cannot open rc2_key.bin or rc2_iv.bin!"**
- Solution: Run `make -f Makefile.key create` first to generate the key files.

**Error: "Failed to load legacy provider!"**
- Solution: Ensure you have a modern OpenSSL installation that supports the legacy provider.
- RC2 requires the legacy provider in OpenSSL 3.0+

**Compilation errors:**
- Ensure OpenSSL development headers are installed: `brew install openssl` (macOS)
- Adjust paths in Makefile if using Intel Mac (change `/opt/homebrew` to `/usr/local`)

**RC2 cipher not found:**
- RC2 is in the legacy provider, ensure it's available
- Test with: `openssl list -cipher-algorithms | grep -i rc2`

## Technical Details

### Algorithm Structure
RC2 operates on 64-bit blocks through 18 rounds of encryption:
1. **Key Expansion**: Transforms variable-length key into 64 16-bit subkeys
2. **Mixing Rounds**: 16 rounds of mixing operations
3. **Mashing Rounds**: 2 additional rounds for enhanced security

### Operations Used
- **XOR**: Bitwise exclusive OR
- **Addition**: Modular addition
- **Rotation**: Bit rotation operations
- **S-box Lookup**: Substitution using predefined table

### Export Compliance Feature
RC2's unique "effective key length" parameter was designed for 1990s export regulations:
- Allows long keys while artificially limiting cryptographic strength
- Example: 128-bit key with 40-bit effective length
- Enabled wider international distribution under export controls
- Made RC2 suitable for commercial products requiring export approval

## Security Considerations

- RC2 is considered cryptographically weak by modern standards
- The 64-bit block size makes it vulnerable to birthday attacks with large amounts of data
- Export compliance feature can artificially weaken security
- Always use a unique IV for each encryption operation
- Never reuse the same key-IV pair for different messages
- Consider using modern algorithms like AES for new applications
- RC2 should only be used for compatibility with legacy systems

## Algorithm Comparison

| Feature | RC2 | AES-128 | IDEA | CAST5 | Blowfish |
|---------|-----|---------|------|--------|----------|
| Block Size | 64 bits | 128 bits | 64 bits | 64 bits | 64 bits |
| Key Size | 8-1024 bits | 128 bits | 128 bits | 40-128 bits | 32-448 bits |
| Rounds | 18 | 10 | 8.5 | 12/16 | 16 |
| Year | 1987 | 2001 | 1991 | 1996 | 1993 |
| Designer | Ron Rivest | Joan Daemen, Vincent Rijmen | Massey & Lai | Adams & Tavares | Bruce Schneier |
| Standard | RFC 2268 | NIST FIPS 197 | No formal | RFC 2144 | No formal |
| Provider | Legacy | Default | Legacy | Legacy | Legacy |
| Export Feature | Yes | No | No | No | No |
| Commercial Use | Microsoft CryptoAPI | Widespread | PGP (historical) | Some applications | Various |

## Historical Context

### Development and Secrecy
- **1987**: Developed by Ron Rivest at RSA Data Security
- **Proprietary Period**: Algorithm kept secret as trade secret
- **1996**: Anonymous posting to sci.crypt revealed the algorithm
- **1998**: RFC 2268 officially documented RC2

### Export Control Era
RC2 was designed during the height of US cryptographic export controls:
- **40-bit Limit**: Export regulations limited key strength to 40 bits
- **Effective Key Length**: RC2's solution to satisfy regulators while allowing longer keys
- **Commercial Adoption**: Enabled international software distribution
- **Microsoft Integration**: Became standard in Windows CryptoAPI

### Industry Impact
- **Widespread Deployment**: Used in numerous commercial applications
- **Email Security**: Integrated into various email encryption systems
- **Legacy Systems**: Still found in older applications requiring compatibility

### Reverse Engineering
The algorithm's secrecy led to an interesting chapter in cryptographic history:
- **Anonymous Disclosure**: Someone with access posted the algorithm anonymously
- **Verification**: Analysis confirmed the posted algorithm was correct
- **Standardization**: Eventually led to official RFC publication

## Modern Relevance

While RC2 is obsolete for new applications, it remains important for:
- **Legacy System Support**: Maintaining compatibility with older systems
- **Historical Understanding**: Learning about export control impacts on cryptography
- **Academic Study**: Understanding design tradeoffs in cipher development
- **Compliance Requirements**: Some legacy standards still reference RC2

RC2 represents an important period in cryptographic history when export controls significantly influenced algorithm design and adoption patterns.