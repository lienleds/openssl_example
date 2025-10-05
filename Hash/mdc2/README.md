# MDC2 Hash Example (C++ & OpenSSL)

This example demonstrates how to compute the MDC2 hash of a file using OpenSSL in C++.

## Usage

1. Build the program:
   ```sh
   g++ mdc2_example.cpp -o mdc2_example -lssl -lcrypto
   ```
2. Run the program:
   ```sh
   ./mdc2_example <input_file>
   ```

## About MDC2
- MDC2 (Modification Detection Code 2) is a cryptographic hash function based on DES.
- It produces a 128-bit (16-byte) hash value.
- Used for data integrity and digital signatures, but is less common than modern hash functions.
