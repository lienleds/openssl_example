# DES Example (C & OpenSSL)

This example demonstrates how to generate a DES key and IV, save them to files, and use them for encryption/decryption with OpenSSL.

## Files
- `create_des_key.c`: Generates a random DES key and IV, saves them to `des_key.bin` and `des_iv.bin`.
- `des.cpp`: Loads the DES key and IV from files and performs encryption/decryption.
- `Makefile.key`: Build script for `create_des_key.c`.
- `Makefile`: Build script for `des.cpp`.

## Usage

1. **Generate DES key and IV:**
   ```sh
   make -f Makefile.key
   ./create_des_key
   ```
   This will create `des_key.bin` and `des_iv.bin` in the current directory.

2. **Encrypt/Decrypt with DES:**
   ```sh
   make
   ./des
   ```
   The program will use the key and IV from the generated files.

## Notes
- Make sure to run the key/iv generator before running the main DES program.
- The DES key and IV are stored in binary format.
- This example is for educational purposes and does not include all security best practices for production use.
