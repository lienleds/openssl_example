# ChaCha20 Example (OpenSSL)

This folder demonstrates how to use the ChaCha20 stream cipher for encryption and decryption using OpenSSL in C++.

## Files

- `chacha20.cpp`: Main example for ChaCha20 encryption/decryption. Loads key and nonce from files.
- `chacha20_create_key.cpp`: Utility to generate a random ChaCha20 key and nonce, saving them to `chacha20_key.bin` and `chacha20_nonce.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/nonce generator utility.
- `chacha20_key.bin`, `chacha20_nonce.bin`: Binary files containing the generated key and nonce.
- `out.txt`: Example output from running the main program.

## Usage

1. **Generate Key and Nonce:**

   ```sh
   make -f Makefile.key
   ./chacha20_create_key
   ```
   This creates `chacha20_key.bin` and `chacha20_nonce.bin`.

2. **Build and Run Example:**

   ```sh
   make
   ./chacha20 > out.txt
   cat out.txt
   ```

3. **Output:**
   - The program prints the key, nonce, ciphertext (in hex), ciphertext length, plaintext length, and the decrypted text.

## Notes
- The key and nonce are loaded from files for better security and modularity.
- Requires OpenSSL development libraries.
- All code is formatted in Allman style for readability.

## References
- [OpenSSL EVP documentation](https://www.openssl.org/docs/manmaster/man3/EVP_EncryptInit.html)
- [Wikipedia: ChaCha20](https://en.wikipedia.org/wiki/Salsa20#ChaCha_variant)
