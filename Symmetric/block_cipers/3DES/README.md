# 3DES (Triple DES) Example (C++ & OpenSSL)

This example demonstrates how to encrypt and decrypt data using 3DES (Triple DES) in CBC mode with OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ des_ede3_cbc_example.cpp -o des_ede3_cbc_example -lssl -lcrypto
   ```
2. Run the program:
   ```sh
   ./des_ede3_cbc_example
   ```

## About 3DES
- 3DES (Triple DES) applies the DES cipher algorithm three times to each data block.
- Uses a 192-bit (24-byte) key and 64-bit (8-byte) block size.
- More secure than single DES, but slower and less secure than modern ciphers like AES.
- Not recommended for new applications, but still found in legacy systems.
