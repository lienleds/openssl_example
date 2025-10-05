# SHA3-224 Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the SHA3-224 hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ sha3_224_example.cpp -o sha3_224_example -lssl -lcrypto
   ```
2. Run the program:
   ```sh
   ./sha3_224_example <input_file>
   ```

## About SHA3-224
- SHA3-224 is part of the SHA-3 family, based on the Keccak algorithm.
- It produces a 224-bit (28-byte) hash value.
- Commonly used for data integrity and digital signatures.
