# 3DES CBC Example (OpenSSL)

This folder demonstrates how to use 3DES (Triple DES) in CBC mode for encryption and decryption using OpenSSL in C++.

## Files

- `des_ede3_cbc_example.cpp`: Main example for 3DES encryption/decryption. Loads key and IV from files.
- `des_create_key.cpp`: Utility to generate a random 3DES key and IV, saving them to `des3_key.bin` and `des3_iv.bin`.
- `Makefile`: Build script for the main example.
- `Makefile.key`: Build script for the key/IV generator utility.
- `des3_key.bin`, `des3_iv.bin`: Binary files containing the generated key and IV.
- `out.txt`: Example output from running the main program.

## Usage

1. **Generate Key and IV:**

   ```sh
   make -f Makefile.key
   ./des_create_key
   ```
   This creates `des3_key.bin` and `des3_iv.bin`.

2. **Build and Run Example:**

   ```sh
   make
   ./des_ede3_cbc_example > out.txt
   cat out.txt
   ```

3. **Output:**
   - The program prints the ciphertext (in hex) and the decrypted plaintext.

## Notes
- The key and IV are loaded from files for better security and modularity.
- Requires OpenSSL development libraries.
- All code is formatted in Allman style for readability.

## References
- [OpenSSL EVP documentation](https://www.openssl.org/docs/manmaster/man3/EVP_EncryptInit.html)
- [Wikipedia: Triple DES](https://en.wikipedia.org/wiki/Triple_DES)
