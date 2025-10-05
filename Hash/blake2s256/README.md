# BLAKE2s256 Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the BLAKE2s256 hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ blake2s256_example.cpp -o blake2s256_example -lssl -lcrypto
   ```
2. Run the program:
   ```sh
   ./blake2s256_example <input_file>
   ```

## About BLAKE2s256
- BLAKE2s256 is a member of the BLAKE2 family, optimized for 8- to 32-bit platforms.
- It produces a 256-bit (32-byte) hash value.
- Suitable for data integrity, digital signatures, and password hashing.
