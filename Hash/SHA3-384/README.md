# SHA3-384 Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the SHA3-384 hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ sha3_384_example.cpp -o sha3_384_example -lssl -lcrypto
   ```
2. Run the program:
   ```sh
   ./sha3_384_example <input_file>
   ```

## About SHA3-384
- SHA3-384 is part of the SHA-3 family, based on the Keccak algorithm.
- It produces a 384-bit (48-byte) hash value.
- Commonly used for data integrity and digital signatures.
