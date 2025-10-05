# AES-CBC-HMAC Example (OpenSSL)

This folder demonstrates how to use AES in CBC mode with HMAC (SHA-256) for authenticated encryption using OpenSSL in C++.

## Files

- `aes_cbc_hmac.cpp`: Main example for AES-CBC encryption/decryption with HMAC authentication. Loads key, HMAC key, and IV from files.
- `aes_create_key.cpp`: Utility to generate a random AES key, HMAC key, and IV, saving them to `aes_key.bin`, `hmac_key.bin`, and `aes_iv.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/IV generator utility.
- `aes_key.bin`, `hmac_key.bin`, `aes_iv.bin`: Binary files containing the generated keys and IV.
- `out.txt`: Example output from running the main program.

## Usage

1. **Generate Keys and IV:**

   ```sh
   make -f Makefile.key
   ./aes_create_key
   ```
   This creates `aes_key.bin`, `hmac_key.bin`, and `aes_iv.bin`.

2. **Build and Run Example:**

   ```sh
   make
   ./aes_cbc_hmac > out.txt
   cat out.txt
   ```

3. **Output:**
   - The program prints the key, HMAC key, IV, ciphertext (in hex), HMACs, and the decrypted plaintext.

## Notes
- The keys and IV are loaded from files for better security and modularity.
- Requires OpenSSL development libraries.
- All code is formatted in Allman style for readability.

## References
- [OpenSSL EVP documentation](https://www.openssl.org/docs/manmaster/man3/EVP_EncryptInit.html)
- [Wikipedia: AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)
- [Wikipedia: HMAC](https://en.wikipedia.org/wiki/HMAC)
