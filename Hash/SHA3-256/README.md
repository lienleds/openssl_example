# SHA3-256 Hash Example

This example demonstrates the SHA3-256 cryptographic hash function using OpenSSL in C++.

## Overview

SHA3-256 is part of the SHA-3 family, standardized by NIST in 2015. Based on the Keccak algorithm, it provides an alternative to SHA-2 with a fundamentally different mathematical construction.

## Algorithm Details

### Basic Parameters
- **Hash size**: 256 bits (32 bytes)
- **Rate**: 1088 bits (136 bytes) - data processed per round
- **Capacity**: 512 bits - security parameter
- **Security level**: 128 bits (collision resistance)
- **Standard**: FIPS 202, ISO/IEC 10118-3

### Keccak Sponge Construction
- **Absorbing phase**: Input data absorbed into state
- **Squeezing phase**: Output hash extracted from state
- **Permutation**: Keccak-f[1600] with 24 rounds
- **State size**: 1600 bits (5×5×64 bit array)

## Files

- `sha3_256.cpp` - Main hash computation demonstration
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
./sha3_256
```

### Save Output
```bash
./sha3_256 > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Construction | Security Level | Performance |
|-----------|-----------|--------------|----------------|-------------|
| SHA3-256  | 256 bits  | Sponge      | 128 bits      | Medium      |
| SHA-256   | 256 bits  | Merkle-Damgård | 128 bits   | High        |
| BLAKE2s256| 256 bits  | HAIFA       | 128 bits      | Very High   |
| SM3       | 256 bits  | Merkle-Damgård | 128 bits   | High        |

## Use Cases

### Recommended Applications
- **Cryptographic diversity**: Alternative to SHA-2 for defense in depth
- **New protocols**: Modern systems requiring latest NIST standards
- **Regulatory compliance**: Applications requiring FIPS 202 compliance
- **Research applications**: Academic and research cryptography
- **Future-proofing**: Hedge against potential SHA-2 vulnerabilities
- **Blockchain diversity**: Alternative hash functions for new cryptocurrencies

### SHA-3 Advantages
- **Different foundation**: Provides mathematical diversity from SHA-2
- **Length extension immunity**: Inherently secure against length extension
- **Clean design**: No known structural weaknesses
- **Flexible output**: Sponge construction allows variable output lengths

## Security Properties

### Unique Security Features
- **Sponge security**: Different security model from Merkle-Damgård
- **No length extension**: Unlike SHA-1/SHA-2, resistant to length extension attacks
- **Indifferentiability**: Provable security from random oracle
- **Side-channel resistance**: More natural constant-time implementation

### Cryptographic Strength
- **128-bit collision resistance**: Equivalent to SHA-256
- **Pre-image resistance**: Full 256-bit strength
- **Multi-collision resistance**: Better than Merkle-Damgård construction
- **Quantum resistance**: Similar to SHA-256 under quantum attacks

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

2. **SHA3 not available**
   ```
   Error: Unknown message digest sha3-256
   ```
   **Solution**: Ensure OpenSSL 1.1.1+ is installed (SHA-3 added in 1.1.1).

3. **Performance expectations**
   ```
   Note: SHA3-256 slower than SHA-256
   ```
   **Context**: SHA-3 prioritizes security and clean design over speed.

### Performance Considerations
- SHA3-256 is generally slower than SHA-256
- Performance varies significantly between implementations
- Hardware acceleration becoming available on newer processors
- Consider BLAKE2s256 for high-performance applications

## Historical Context

### SHA-3 Competition Background
- **2007**: NIST announces SHA-3 competition following SHA-1 breaks
- **2012**: Keccak selected from 64 initial submissions
- **2015**: SHA-3 standardized as FIPS 202
- **Purpose**: Provide backup to SHA-2, not replacement

### Keccak Design Innovation
- **Sponge construction**: Revolutionary approach to hash function design
- **Team**: Guido Bertoni, Joan Daemen, Michaël Peeters, Gilles Van Assche
- **Influence**: Inspired new generation of cryptographic primitives
- **Recognition**: Represents state-of-the-art in hash function design

## Implementation Notes

### OpenSSL Integration
- Available in default provider (OpenSSL 1.1.1+)
- Standard EVP interface compatibility
- Cross-platform implementation
- Growing hardware acceleration support

### Technical Details
- **Keccak-f[1600]**: Core permutation with 1600-bit state
- **Rate and capacity**: Trade-off between speed and security
- **Padding**: Simple 10*1 padding rule
- **Rounds**: 24 rounds of θ, ρ, π, χ, ι operations

### Sponge Construction Benefits
- **Flexibility**: Can produce arbitrary-length output
- **Security**: No length extension vulnerability
- **Parallelization**: Natural parallel processing capabilities
- **Composability**: Easy to build other primitives on top

### Modern Adoption
- **NIST compliance**: Required for some U.S. government applications
- **Academic use**: Popular in cryptographic research
- **Protocol diversity**: Provides alternative to SHA-2 in new systems
- **Long-term security**: Part of defense-in-depth cryptographic strategy

### Future Outlook
- **Complementary role**: Works alongside SHA-2, not as replacement
- **Hardware support**: Increasing processor support expected
- **Protocol adoption**: Growing use in new cryptographic protocols
- **Standardization**: Basis for additional NIST cryptographic standards