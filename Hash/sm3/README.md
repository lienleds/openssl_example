# SM3 Hash Example

This example demonstrates the SM3 cryptographic hash function using OpenSSL in C++.

## Overview

SM3 is a cryptographic hash function designed in China and standardized as part of the Chinese National Cryptographic Algorithm Suite. It's widely used in Chinese government and commercial cryptographic applications.

## Algorithm Details

### Basic Parameters
- **Hash size**: 256 bits (32 bytes)
- **Block size**: 512 bits (64 bytes)
- **Security level**: 128 bits (collision resistance)
- **Standard**: GB/T 32905-2016, ISO/IEC 10118-3:2018

### Design Characteristics
- **Merkle-Damgård construction**: Similar to SHA-2 family
- **Compression function**: Custom design with Chinese cryptographic principles
- **Message expansion**: 68-word expansion similar to SHA-256
- **Boolean functions**: Two different functions for different rounds

## Files

- `sm3_example.cpp` - Main hash computation demonstration
- `test.txt` - Sample input file for hashing
- `Makefile` - Build configuration with macOS OpenSSL support
- `out.txt` - Example output showing hash computation
- `README.md` - This documentation file

## Building and Running

### Prerequisites
- macOS with Homebrew
- OpenSSL 3.x: `brew install openssl`
- C++ compiler with C++11 support

### Step 1: Build
```bash
make
```

### Step 2: Run Example
```bash
./sm3_example test.txt
```

### Save Output
```bash
./sm3_example test.txt > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Block Size | Origin | Security Level |
|-----------|-----------|------------|---------|----------------|
| SM3       | 256 bits  | 512 bits   | China   | 128 bits      |
| SHA-256   | 256 bits  | 512 bits   | USA     | 128 bits      |
| SHA3-256  | 256 bits  | 1088 bits  | Belgium | 128 bits      |
| GOST R 34.11-2012 | 256 bits | 512 bits | Russia | 128 bits |

## Use Cases

### Recommended Applications
- **Chinese government systems**: Official cryptographic standard
- **Financial institutions**: Banking and payment systems in China
- **Digital certificates**: X.509 certificates for Chinese PKI
- **Blockchain applications**: Used in Chinese blockchain platforms
- **Industrial control**: Secure communications in Chinese infrastructure

### Regulatory Context
- **Mandatory usage**: Required in Chinese government cryptographic applications
- **Commercial adoption**: Widely implemented in Chinese software
- **International recognition**: ISO/IEC standard for global interoperability
- **Compliance**: Necessary for systems operating in Chinese regulatory environment

## Security Properties

### Cryptographic Strength
- **128-bit security level**: Equivalent to AES-128 and SHA-256
- **No known vulnerabilities**: Extensive analysis by Chinese and international researchers
- **Collision resistance**: No practical collision attacks known
- **Pre-image resistance**: Computationally secure against inversion

### Design Philosophy
- **National sovereignty**: Independent cryptographic capability
- **Transparent design**: Publicly available specification and analysis
- **Performance optimization**: Efficient implementation on various platforms
- **Security by design**: Conservative approach to cryptographic margins

## Troubleshooting

### Common Issues

1. **OpenSSL headers not found**
   ```
   Error: 'openssl/evp.h' file not found
   ```
   **Solution**: Install OpenSSL development libraries:
   ```bash
   brew install openssl
   ```

2. **SM3 not available**
   ```
   Error: Unknown message digest sm3
   ```
   **Solution**: Ensure OpenSSL 3.x is installed (SM3 support added in 1.1.1).

3. **Compilation errors on macOS**
   ```
   Error: cannot find -lssl -lcrypto
   ```
   **Solution**: Use provided Makefile with correct OpenSSL paths.

### Performance Notes
- Similar performance characteristics to SHA-256
- Optimized implementations available for various architectures
- Hardware acceleration support in Chinese cryptographic modules
- Suitable for high-throughput applications

## Historical Context

### Development Background
- **2010**: Initial design and standardization in China
- **2016**: Updated as GB/T 32905-2016 national standard
- **2018**: Adopted as ISO/IEC 10118-3:2018 international standard
- **Purpose**: Provide cryptographic independence and security assurance

### International Recognition
- **Cryptographic community**: Peer-reviewed and analyzed internationally
- **Standards bodies**: Accepted by ISO/IEC for global use
- **Research**: Extensive cryptanalysis published in international conferences
- **Implementation**: Available in major cryptographic libraries

## Implementation Notes

### OpenSSL Integration
- Available in default provider (OpenSSL 1.1.1+)
- Standard EVP interface compatibility
- Cross-platform implementation
- Performance comparable to other 256-bit hash functions

### Technical Details
- **Initialization vector**: Fixed 256-bit initial hash value
- **Compression rounds**: 64 rounds with varying Boolean functions
- **Message padding**: Similar to SHA-2 family padding scheme
- **Word operations**: 32-bit word-based operations for efficiency

### Chinese Cryptographic Context
- **SM2**: Elliptic curve cryptography (public key)
- **SM3**: Hash function (message digest)
- **SM4**: Block cipher (symmetric encryption)
- **Suite**: Complete cryptographic algorithm family for national use
