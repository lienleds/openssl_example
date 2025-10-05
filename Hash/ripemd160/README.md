# RIPEMD160 Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the RIPEMD160 hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ ripemd160_example.cpp -o ripemd160_example -lssl -lcrypto
   ```
2. Run the program:
   ```sh
   ./ripemd160_example <input_file>
   ```

## About RIPEMD160
- RIPEMD160 is a cryptographic hash function designed as an alternative to SHA-1.
- It produces a 160-bit (20-byte) hash value.
- Used in various applications, including Bitcoin addresses.
