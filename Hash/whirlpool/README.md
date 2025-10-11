# Whirlpool Hash Example

This example demonstrates the Whirlpool cryptographic hash function using OpenSSL in C++.

## Overview

Whirlpool is a cryptographic hash function designed by Vincent Rijmen (co-designer of AES) and Paulo S.L.M. Barreto. It's based on a modified Advanced Encryption Standard (AES) in Miyaguchi-Preneel mode.

## Algorithm Details

### Basic Parameters
- **Hash size**: 512 bits (64 bytes)
- **Block size**: 512 bits (64 bytes)
- **Security level**: 256 bits (collision resistance)
- **Standard**: ISO/IEC 10118-3:2004

### Design Innovation
- **AES-based**: Uses modified AES cipher as compression function
- **Miyaguchi-Preneel**: Secure construction for hash functions from block ciphers
- **Square structure**: Based on Square cipher design principles
- **Academic pedigree**: Designed by renowned cryptographers

## Files

- `whirlpool_example.cpp` - Main hash computation demonstration
- `test.txt` - Sample input file for hashing
- `Makefile` - Build configuration with macOS OpenSSL support
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
./whirlpool_example test.txt
```

### Save Output
```bash
./whirlpool_example test.txt > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Block Size | Construction | Security Level |
|-----------|-----------|------------|--------------|----------------|
| Whirlpool | 512 bits  | 512 bits   | Miyaguchi-Preneel | 256 bits |
| SHA-512   | 512 bits  | 1024 bits  | Merkle-Damgård    | 256 bits |
| SHA3-512  | 512 bits  | 576 bits   | Sponge            | 256 bits |
| BLAKE2b512| 512 bits  | 1024 bits  | HAIFA             | 256 bits |

## Use Cases

### Recommended Applications
- **Digital forensics**: Strong hash for evidence integrity
- **Academic research**: Well-studied algorithm with clear design
- **Long-term archival**: 512-bit output provides future security
- **Cryptographic diversity**: Alternative to SHA-2 and SHA-3 families
- **Educational purposes**: Demonstrates block cipher to hash function conversion

### Historical Significance
- **Bridge design**: Connects block cipher and hash function research
- **AES relationship**: Shows how AES principles apply to hash functions
- **Academic impact**: Influential in cryptographic research community
- **Standards adoption**: Recognized by ISO/IEC international standards

## Security Properties

### Cryptographic Strength
- **256-bit security level**: High security margin for long-term use
- **No known attacks**: Resistant to all known cryptanalytic techniques
- **AES foundation**: Benefits from extensive AES security analysis
- **Conservative design**: Large security margins built into construction

### Theoretical Foundation
- **Provable security**: Security reduces to underlying block cipher
- **Miyaguchi-Preneel**: Well-understood and analyzed construction
- **Academic rigor**: Extensive peer review and cryptanalysis
- **Design transparency**: Open design process and public scrutiny

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

2. **Whirlpool not available**
   ```
   Error: Unknown message digest whirlpool
   ```
   **Solution**: May require legacy provider in some OpenSSL 3.x builds:
   ```cpp
   OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
   ```

3. **Performance considerations**
   ```
   Warning: Whirlpool slower than SHA-2
   ```
   **Note**: Whirlpool is computationally intensive due to AES-based design.

### Implementation Notes
- Whirlpool is slower than SHA-2 but provides different security foundation
- Memory usage is moderate
- Benefits from AES hardware acceleration on some platforms
- Constant-time implementations possible

## Historical Context

### Development Timeline
- **2000**: Initial design by Rijmen and Barreto
- **2001**: Submitted to NESSIE European cryptographic competition
- **2003**: Selected by NESSIE for recommendation
- **2004**: Adopted as ISO/IEC 10118-3:2004 standard

### Design Philosophy
- **Academic excellence**: Created by leading cryptographic researchers
- **Theoretical foundation**: Based on solid cryptographic theory
- **Innovation**: Novel application of block cipher to hash function design
- **Peer review**: Extensive analysis by cryptographic community

### NESSIE Competition
- **European initiative**: EU-sponsored cryptographic algorithm evaluation
- **Rigorous process**: Multi-year evaluation by international experts
- **Selection criteria**: Security, performance, and implementation considerations
- **Legacy**: Established Whirlpool as academically respected algorithm

## Implementation Notes

### OpenSSL Integration
- Available in legacy provider (OpenSSL 3.x)
- Standard EVP interface support
- Cross-platform implementation
- May require explicit provider loading

### Technical Details
- **Rounds**: 10 rounds in compression function
- **Key schedule**: Derives round keys from hash state
- **S-boxes**: Uses AES S-box for substitution
- **MixColumns**: Uses modified AES MixColumns operation

### Performance Characteristics
- **CPU intensive**: More computationally expensive than SHA-2
- **Memory efficient**: Reasonable memory usage
- **Hardware friendly**: Can benefit from AES instruction sets
- **Academic implementation**: Focus on correctness over speed optimization

### Cryptographic Context
- Demonstrates versatility of AES design principles
- Shows how block ciphers can be converted to hash functions
- Provides alternative mathematical foundation to SHA-2
- Represents high-quality academic cryptographic design
