# BLAKE2b512 Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the BLAKE2b512 hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ blake2b512_example.cpp -o blake2b512_example -lssl -lcrypto
   ```
2. Run the program:
   ```sh
   ./blake2b512_example <input_file>
   ```

## About BLAKE2b512
- BLAKE2b512 is a member of the BLAKE2 family, designed as a fast and secure cryptographic hash function.
- It produces a 512-bit (64-byte) hash value.
- Suitable for data integrity, digital signatures, and password hashing.
