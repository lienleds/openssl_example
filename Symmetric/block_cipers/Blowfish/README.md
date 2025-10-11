# Blowfish Encryption Example (OpenSSL)

This folder demonstrates how to use Blowfish cipher in CBC mode for encryption and decryption using OpenSSL in C++.

## About Blowfish

Blowfish is a symmetric-key block cipher designed by Bruce Schneier in 1993. It features:
- **Block Size:** 64 bits (8 bytes)
- **Key Size:** Variable length from 32 bits to 448 bits (4 to 56 bytes)
- **Mode:** CBC (Cipher Block Chaining) mode in this example
- **Legacy Algorithm:** Requires legacy provider in modern OpenSSL versions

## Files

- `blowfish_example.cpp`: Main example for Blowfish-CBC encryption/decryption. Loads key and IV from files.
- `blowfish_create_key.cpp`: Utility to generate a random Blowfish key and IV, saving them to `blowfish_key.bin` and `blowfish_iv.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/IV generator utility.
- `blowfish_key.bin`, `blowfish_iv.bin`: Binary files containing the generated key and IV (created after running key generator).
- `out.txt`: Example output from running the main program (created after running example).
- `blowfish_create_key`, `blowfish_example`: Compiled executable files.

## Usage

1. **Generate Key and IV:**

   ```sh
   make -f Makefile.key
   ./blowfish_create_key
   ```
   This creates `blowfish_key.bin` (128 bits) and `blowfish_iv.bin` (64 bits).

2. **Build and Run Example:**

   ```sh
   make
   ./blowfish_example > out.txt
   cat out.txt
   ```

3. **Clean up:**

   ```sh
   make clean                    # Remove compiled binaries
   make -f Makefile.key clean    # Remove key files and key generator
   ```

## Example Output

The program will encrypt and decrypt a sample text, displaying:
- Original plaintext
- Key and IV in hexadecimal format
- Encrypted ciphertext in hexadecimal
- Decrypted plaintext
- Verification of successful encryption/decryption

Sample output:
```
=== Blowfish Encryption/Decryption Example ===
Original text: This is Blowfish encryption example!
Text length: 36 bytes

Key (hex): 6390cecbff6010e40de815de4b587060
IV (hex): b658b4c3f89919df
Ciphertext (hex): 242e33280551899ed011687e610e77ae0739be2b70cdaa9ced61b15f26b842df0927729137a80907
Ciphertext length: 40 bytes

Decrypted text: This is Blowfish encryption example!
Decrypted length: 36 bytes

✓ Encryption/Decryption successful!
```

Note: The key and IV will be different each time you generate new keys, resulting in different ciphertext.

## Troubleshooting

**Error: "Cannot open blowfish_key.bin or blowfish_iv.bin!"**
- Solution: Run `make -f Makefile.key create` first to generate the key files.

**Error: "Failed to load legacy provider!"**
- Solution: Ensure you have a modern OpenSSL installation that supports the legacy provider.
- Check your OpenSSL configuration allows loading the legacy provider.

**Compilation errors:**
- Ensure OpenSSL development headers are installed: `brew install openssl` (macOS)
- Adjust paths in Makefile if using Intel Mac (change `/opt/homebrew` to `/usr/local`)

## Technical Notes

- Blowfish uses a 64-bit block size, which is smaller than modern standards like AES (128-bit)
- The key length in this example is 128 bits, but Blowfish supports variable key lengths
- CBC mode requires an Initialization Vector (IV) for security
- The legacy provider must be loaded for Blowfish support in modern OpenSSL versions
- Blowfish is considered legacy; for new applications, consider using AES instead

## Security Considerations

- Blowfish is considered cryptographically secure but is largely superseded by AES
- The 64-bit block size makes it vulnerable to birthday attacks with large amounts of data
- Always use a unique IV for each encryption operation
- Never reuse the same key-IV pair for different messages