# SHA3-224 Hash Example

This example demonstrates the SHA3-224 cryptographic hash function using OpenSSL in C++.

## Overview

SHA3-224 is part of the SHA-3 (Secure Hash Algorithm 3) family, standardized by NIST in 2015. It's based on the Keccak algorithm that won the SHA-3 competition.

## Algorithm Details

### Basic Parameters
- **Hash size**: 224 bits (28 bytes)
- **Block size**: 1152 bits (144 bytes)
- **Security level**: 112 bits (collision resistance)
- **Algorithm family**: Keccak/SHA-3

### Keccak Innovation
- **Sponge construction**: Fundamentally different from Merkle-Damgård
- **Permutation-based**: Uses Keccak-f[1600] permutation
- **Variable capacity**: Adjustable security/performance trade-off
- **No length extension**: Immune to length extension attacks

## Files

- `sha3_224_example.cpp` - Main hash computation demonstration
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
./sha3_224_example test.txt
```

### Save Output
```bash
./sha3_224_example test.txt > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Security Level | Construction | Performance |
|-----------|-----------|----------------|--------------|-------------|
| SHA3-224  | 224 bits  | 112 bits      | Sponge       | Medium      |
| SHA-224   | 224 bits  | 112 bits      | Merkle-Damgård| High      |
| SHA3-256  | 256 bits  | 128 bits      | Sponge       | Medium      |
| BLAKE2s256| 256 bits  | 128 bits      | HAIFA        | Very High   |

## Use Cases

### Recommended Applications
- **Digital signatures**: Cryptographic signature schemes requiring 112-bit security
- **Certificate authorities**: X.509 certificates with moderate security requirements
- **Integrity checking**: File verification with space-constrained storage
- **Embedded systems**: Applications where 256-bit hashes are too large
- **Legacy compatibility**: Systems requiring SHA-2 style hash lengths

### SHA-3 Advantages
- **Different mathematical foundation**: Provides diversity from SHA-2
- **Length extension immunity**: Inherently resistant to length extension attacks
- **Clean design**: No known cryptographic weaknesses
- **NIST standardized**: Official U.S. government standard

## Security Properties

### Cryptographic Strength
- **112-bit security level**: Suitable for most commercial applications
- **Quantum resistance**: More resistant to quantum attacks than equivalent SHA-2
- **Pre-image resistance**: Computationally infeasible to reverse
- **Collision resistance**: Difficult to find two inputs with same hash

### Sponge Construction Benefits
- **No length extension vulnerability**: Unlike Merkle-Damgård construction
- **Flexible output length**: Can generate arbitrary-length outputs
- **Parallel processing**: Amenable to parallel implementation
- **Side-channel resistance**: More resistant to timing attacks

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
   Error: Unknown message digest sha3-224
   ```
   **Solution**: Ensure OpenSSL 3.x is installed (SHA-3 support added in 1.1.1).

3. **Compilation linking errors**
   ```
   Error: cannot find -lssl -lcrypto
   ```
   **Solution**: Use provided Makefile with correct library paths.

### Performance Considerations
- SHA3-224 is slower than SHA-224 but more secure
- Performance varies significantly between implementations
- Hardware acceleration available on some platforms
- Memory usage is higher than SHA-2 family

## Historical Context

### SHA-3 Competition
- **2007-2012**: NIST conducted public competition for SHA-3
- **2012**: Keccak selected as winner from 64 submissions
- **2015**: SHA-3 standardized as FIPS 202
- **Design goal**: Provide alternative to SHA-2 with different mathematical foundation

### Keccak Design
- Created by Guido Bertoni, Joan Daemen, Michaël Peeters, and Gilles Van Assche
- Based on sponge construction pioneered by same team
- Influenced by AES design principles
- Represents state-of-the-art in hash function design

## Implementation Notes

### OpenSSL Integration
- Available in default provider (OpenSSL 1.1.1+)
- Full EVP interface support
- Compatible with standard hash APIs
- Cross-platform implementation

### Technical Details
- **Rate**: 1152 bits (amount of data processed per round)
- **Capacity**: 448 bits (security parameter)
- **Rounds**: 24 rounds of Keccak-f[1600]
- **State size**: 1600 bits (5×5×64 bit array)

### Performance Optimization
- Implementation can benefit from bit-slicing
- SIMD instructions can accelerate computation
- Hardware implementations possible
- Constant-time implementations available for side-channel resistance
