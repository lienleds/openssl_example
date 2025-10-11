# SHA-384 Hash Example

This example demonstrates the SHA-384 cryptographic hash function using OpenSSL in C++.

## Overview

SHA-384 is part of the SHA-2 family, providing a truncated version of SHA-512. It offers high security with a smaller output size than SHA-512, making it suitable for applications requiring strong security with moderate storage requirements.

## Algorithm Details

### Basic Parameters
- **Hash size**: 384 bits (48 bytes)
- **Block size**: 1024 bits (128 bytes)
- **Security level**: 192 bits (collision resistance)
- **Standard**: FIPS 180-4, ISO/IEC 10118-3

### Relationship to SHA-512
- **Same algorithm**: Uses identical computation as SHA-512
- **Different IV**: Uses different initial hash values
- **Truncated output**: Final hash is truncated to 384 bits
- **Same performance**: Nearly identical speed to SHA-512

## Files

- `sha384.cpp` - Main hash computation demonstration
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
./sha384
```

### Save Output
```bash
./sha384 > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Security Level | Performance (64-bit) | Use Case |
|-----------|-----------|----------------|---------------------|----------|
| SHA-384   | 384 bits  | 192 bits      | Excellent           | High security, moderate size |
| SHA-512   | 512 bits  | 256 bits      | Excellent           | Maximum security |
| SHA-256   | 256 bits  | 128 bits      | Good                | General purpose |
| SHA3-384  | 384 bits  | 192 bits      | Medium              | Alternative to SHA-384 |

## Use Cases

### Recommended Applications
- **High-security systems**: Government and financial applications
- **Long-term security**: Archival systems with extended lifetime
- **Space-constrained high-security**: When SHA-512 is too large
- **Elliptic curve cryptography**: Matching ECC P-384 security level
- **Digital signatures**: High-security signature schemes
- **Certificate authorities**: High-assurance PKI systems

### Security Level Applications
- **192-bit security**: Suitable for top secret information (depending on policy)
- **Future-proofing**: Provides security margin for long-term applications
- **Quantum resistance**: Better post-quantum security than smaller hashes
- **Regulatory compliance**: Meets high-security government requirements

## Security Properties

### Enhanced Security Features
- **High collision resistance**: 192-bit security level
- **Extended pre-image resistance**: 384-bit strength against inversion
- **Quantum resilience**: 96-bit effective security under quantum attack
- **Future-proof design**: Large security margin for extended use

### Cryptographic Guarantees
- **Proven security**: Inherits SHA-512 security analysis
- **Truncation safety**: Truncation doesn't compromise security properties
- **No known weaknesses**: Resistant to all known cryptanalytic attacks
- **Conservative design**: Large security margins built in

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

2. **Performance on 32-bit systems**
   ```
   Warning: SHA-384 may be slow on 32-bit processors
   ```
   **Solution**: Consider SHA-256 for 32-bit or embedded systems.

3. **Output size handling**
   ```
   Note: SHA-384 produces 48-byte output
   ```
   **Consideration**: Ensure applications handle 384-bit hash correctly.

### Performance Optimization
- SHA-384 performs excellently on 64-bit systems
- Hardware SHA extensions provide significant acceleration
- Memory usage is moderate (larger than SHA-256, smaller than SHA-512)
- Consider BLAKE2b for higher performance with similar security

## Historical Context

### Design Background
- **Complementary security**: Provides intermediate security level in SHA-2 family
- **NIST strategy**: Part of comprehensive hash function suite
- **Government adoption**: Used in high-security government applications
- **Industry uptake**: Gradual adoption in high-assurance systems

### Standardization Timeline
- **2001**: Standardized as part of SHA-2 family
- **2005**: Increased adoption following SHA-1 concerns
- **2010s**: Deployment in high-security applications
- **Present**: Stable choice for high-security, size-conscious applications

## Implementation Notes

### OpenSSL Integration
- Available in default provider
- Full EVP interface support
- Hardware acceleration when available
- Consistent API with other SHA-2 variants

### Technical Specifications
- **Initial hash values**: Different 64-bit constants from SHA-512
- **Computation**: Identical to SHA-512 through all 80 rounds
- **Output handling**: Truncates SHA-512 output to first 384 bits
- **Security analysis**: Extensive cryptanalytic review completed

### Architecture Considerations
- **64-bit systems**: Excellent choice for high-security applications
- **32-bit systems**: May prefer SHA-256 for better performance
- **Embedded high-security**: Evaluate against resource constraints
- **Server applications**: Good balance of security and performance

## Modern Recommendations

### Selection Criteria
```cpp
// Choose SHA-384 when:
if (need_high_security && output_size_matters) {
    use_sha384();  // 192-bit security, 48-byte output
} else if (need_maximum_security) {
    use_sha512();  // 256-bit security, 64-byte output
} else if (general_purpose_adequate) {
    use_sha256();  // 128-bit security, 32-byte output
}
```

### Application Guidelines
- **Financial systems**: Excellent for payment processing and banking
- **Government systems**: Suitable for classified information (policy dependent)
- **Long-term storage**: Good choice for archival systems
- **High-value assets**: Appropriate for protecting valuable digital assets

### Future Considerations
- **Post-quantum security**: 96-bit effective security under quantum attack
- **Migration flexibility**: Easy upgrade path to SHA-512 if needed
- **Standard longevity**: Expected to remain supported long-term
- **Hardware support**: Growing processor support for SHA-384 acceleration

### Quantum Computing Impact
- **Current assessment**: Grover's algorithm reduces effective security
- **Timeline considerations**: Quantum threat timeline affects choice
- **Migration planning**: Consider post-quantum alternatives for very long-term use
- **Risk assessment**: Balance current security needs with future quantum threat