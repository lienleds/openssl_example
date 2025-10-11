# RC4 Stream Cipher Example

## Algorithm Overview

RC4 (Rivest Cipher 4) is a symmetric stream cipher designed by Ron Rivest in 1987. It was widely used in protocols like WEP, WPA (TKIP), and TLS, but has since been deprecated due to serious cryptographic vulnerabilities. This example is provided for educational purposes only.

### Key Characteristics
- **Algorithm Type**: Stream cipher
- **Key Size**: Variable (40-2048 bits, commonly 128 bits)
- **Block Size**: 1 byte (8 bits)
- **Design**: Variable-length key stream generation
- **Security Status**: **CRYPTOGRAPHICALLY BROKEN - DO NOT USE**

## Security Properties

### Strengths (Historical)
- Extremely fast in software
- Simple implementation
- Variable key length support
- Low memory requirements

### Critical Weaknesses
- **Biased keystream**: Statistical biases in the output
- **Related-key attacks**: Vulnerable when using related keys
- **Weak key scheduling**: Some keys produce predictable patterns
- **FMS attack**: Fluhrer, Mantin, and Shamir attack on WEP
- **Invariance weakness**: Certain byte patterns reveal key information
- **BEAST and other attacks**: Exploitable in various protocols

## Use Cases

### Educational Use Only
- Understanding stream cipher principles
- Cryptanalysis studies and research
- Historical cryptography education
- Demonstrating broken cipher vulnerabilities

### **STRONGLY DEPRECATED**
- ❌ Any production cryptographic use
- ❌ Network protocol encryption
- ❌ File encryption
- ❌ Password protection
- ❌ Any security-critical application

## Migration Recommendations

### Modern Alternatives
- **ChaCha20**: Modern stream cipher with proven security
- **AES-GCM**: AEAD mode providing encryption and authentication
- **AES-CTR**: Counter mode for stream-like encryption
- **ChaCha20-Poly1305**: AEAD combining ChaCha20 with Poly1305 MAC

## Code Example

This implementation demonstrates RC4 for educational purposes:

```cpp
#include <openssl/evp.h>
#include <openssl/rc4.h>

// Key generation and stream cipher operations
```

## Files Description

- `rc4_create_key.cpp` - Key generation utility
- `rc4_example.cpp` - Main RC4 encryption/decryption example
- `Makefile` - Build configuration
- `rc4_key.bin` - Generated key file

## Build and Run

```bash
# Build the examples
make

# Generate a key
./rc4_create_key

# Run the example
./rc4_example
```

## Security Analysis

### Attack Vectors
1. **Statistical Analysis**: Keystream biases enable plaintext recovery
2. **Key Recovery**: FMS and related attacks can extract keys
3. **Collision Attacks**: Repeated keystream segments
4. **Implementation Flaws**: Timing attacks and side channels

### Cryptanalysis History
- **1994**: First statistical biases discovered
- **2001**: FMS attack breaks WEP
- **2004**: Invariance weakness identified
- **2013**: RFC 7465 prohibits RC4 in TLS
- **2015**: Formal deprecation across protocols

## Troubleshooting

### Common Issues
- **Deprecated warnings**: Expected - RC4 is intentionally deprecated
- **Compilation errors**: May require legacy OpenSSL flags
- **Weak key detection**: Some keys may be rejected by modern implementations

### Build Problems
```bash
# If RC4 is disabled in your OpenSSL build
export OPENSSL_CONF=""
# Or use legacy provider
```

## Educational Notes

### Learning Objectives
- Understand stream cipher operation
- Learn about cryptographic failures
- Study historical attack evolution
- Analyze vulnerability discovery process

### Related Algorithms
- **Salsa20/ChaCha20**: Modern stream ciphers
- **AES-CTR**: Block cipher in counter mode
- **Linear/Differential Cryptanalysis**: Attack techniques

## References

- RFC 7465: Prohibiting RC4 Cipher Suites
- Fluhrer, S., Mantin, I., Shamir, A.: "Weaknesses in the Key Scheduling Algorithm of RC4"
- AlFardan, N., et al.: "On the Security of RC4 in TLS"
- NIST SP 800-131A: Cryptographic Algorithm Transitions and Guidelines

## Warning

⚠️ **CRITICAL SECURITY WARNING**: RC4 is cryptographically broken and must not be used for any security-critical applications. This implementation is provided solely for educational and historical study purposes.