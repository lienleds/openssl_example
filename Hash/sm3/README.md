# SM3 Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the SM3 hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ sm3_example.cpp -o sm3_example -lssl -lcrypto
   ```

2. Run the program:
   ```sh
   ./sm3_example test.txt
   ```
   Or to save the output:
   ```sh
   ./sm3_example test.txt > out.txt
   ```
   (A sample file `test.txt` is included for testing.)

## About SM3
- SM3 is a cryptographic hash function standardized in China, widely used in Chinese cryptographic applications.
- It produces a 256-bit (32-byte) hash value.
- Suitable for data integrity, digital signatures, and password hashing.
