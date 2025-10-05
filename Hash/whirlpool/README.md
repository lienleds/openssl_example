# Whirlpool Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the Whirlpool hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ whirlpool_example.cpp -o whirlpool_example -lssl -lcrypto
   ```

2. Run the program:
   ```sh
   ./whirlpool_example test.txt
   ```
   Or to save the output:
   ```sh
   ./whirlpool_example test.txt > out.txt
   ```
   (A sample file `test.txt` is included for testing.)

## About Whirlpool
- Whirlpool is a cryptographic hash function designed by Vincent Rijmen and Paulo Barreto.
- It produces a 512-bit (64-byte) hash value.
- Used for data integrity and digital signatures.
