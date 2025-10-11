# SHA-512 Hash Example

This example demonstrates the SHA-512 cryptographic hash function using OpenSSL in C++.

## Overview

SHA-512 (Secure Hash Algorithm 512-bit) is part of the SHA-2 family, providing a higher security level than SHA-256. It's designed for applications requiring maximum cryptographic strength.

## Algorithm Details

### Basic Parameters
- **Hash size**: 512 bits (64 bytes)
- **Block size**: 1024 bits (128 bytes)
- **Security level**: 256 bits (collision resistance)
- **Standard**: FIPS 180-4, ISO/IEC 10118-3

### SHA-512 Operations
- **64-bit operations**: Uses 64-bit words (vs 32-bit in SHA-256)
- **Message scheduling**: Expands 16 words to 80 words per block
- **Compression function**: 80 rounds of operations
- **Higher precision**: Increased internal state size

## Files

- `sha512.cpp` - Main hash computation demonstration
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
./sha512
```

### Save Output
```bash
./sha512 > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Block Size | Security Level | 64-bit Performance |
|-----------|-----------|------------|----------------|--------------------|
| SHA-512   | 512 bits  | 1024 bits  | 256 bits      | Excellent          |
| SHA-384   | 384 bits  | 1024 bits  | 192 bits      | Excellent          |
| SHA-256   | 256 bits  | 512 bits   | 128 bits      | Good               |
| BLAKE2b512| 512 bits  | 1024 bits  | 256 bits      | Superior           |

## Use Cases

### Recommended Applications
- **High-security applications**: Government and military systems
- **Long-term security**: Archival systems and future-proofing
- **Large file integrity**: Checksums for big data applications
- **Cryptographic protocols**: Where maximum hash strength is required
- **64-bit systems**: Optimized performance on 64-bit architectures
- **Key derivation**: High-entropy key generation from passwords

### Performance Advantages on 64-bit Systems
- **Native operations**: Uses native 64-bit CPU instructions
- **Better throughput**: Often faster than SHA-256 on 64-bit processors
- **Parallel processing**: Can process larger blocks more efficiently
- **Modern hardware**: Takes advantage of current processor architectures

## Security Properties

### Enhanced Security Features
- **Higher collision resistance**: 256-bit security level vs 128-bit for SHA-256
- **Larger internal state**: 512-bit state provides more security margin
- **Extended rounds**: 80 rounds vs 64 rounds in SHA-256
- **Future-proof**: Better quantum resistance (128-bit effective vs 64-bit)

### Cryptographic Guarantees
- **Pre-image resistance**: 2^512 operations required
- **Second pre-image resistance**: 2^512 operations required
- **Collision resistance**: 2^256 operations required (birthday paradox)
- **Avalanche effect**: Single bit change affects ~50% of output bits

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

2. **Performance expectations**
   ```
   Note: SHA-512 may be slower on 32-bit systems
   ```
   **Recommendation**: Use SHA-256 on 32-bit or constrained systems.

3. **Memory usage**
   ```
   Warning: Larger hash size requires more storage
   ```
   **Consideration**: Balance security needs with storage requirements.

### Performance Optimization
- SHA-512 performs best on 64-bit systems
- Hardware SHA extensions provide significant acceleration
- Consider BLAKE2b for higher performance with equivalent security
- Vectorization can improve throughput on supported processors

## Historical Context

### Development Rationale
- **Extended security**: Response to theoretical advances in cryptanalysis
- **64-bit optimization**: Designed for modern processor architectures
- **Future-proofing**: Anticipation of stronger attack methods
- **Complementary design**: Part of comprehensive SHA-2 family

### Adoption Timeline
- **2001**: Standardized alongside SHA-256
- **2005**: Increased adoption as SHA-1 weaknesses emerged
- **2010s**: Widespread deployment in high-security applications
- **Present**: Standard choice for maximum security applications

## Implementation Notes

### OpenSSL Integration
- Available in default provider
- Full EVP interface support
- Hardware acceleration when available
- Consistent API with other SHA-2 variants

### Technical Specifications
- **Initial hash values**: Eight 64-bit constants
- **Round constants**: 80 constants derived from cube roots of primes
- **Word size**: 64-bit words throughout computation
- **Padding**: Similar to SHA-256 but with 128-bit length field

### Architecture Considerations
- **64-bit systems**: Excellent performance, recommended choice
- **32-bit systems**: May be slower than SHA-256, consider alternatives
- **Embedded systems**: Evaluate memory and performance requirements
- **Server applications**: Ideal for high-throughput, high-security needs

### Security Recommendations
- **Choose SHA-512**: For new applications requiring maximum security
- **Long-term storage**: Preferred for data with extended lifetime
- **Regulatory compliance**: Often required for high-security environments
- **Migration path**: Good choice when upgrading from SHA-256