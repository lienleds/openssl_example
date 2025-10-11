# SHA-224 Hash Example

This example demonstrates the SHA-224 cryptographic hash function using OpenSSL in C++.

## Overview

SHA-224 is part of the SHA-2 family, providing a truncated version of SHA-256. It offers a balance between security and hash size for applications that need strong security but have storage constraints.

## Algorithm Details

### Basic Parameters
- **Hash size**: 224 bits (28 bytes)
- **Block size**: 512 bits (64 bytes)
- **Security level**: 112 bits (collision resistance)
- **Standard**: FIPS 180-4, ISO/IEC 10118-3

### Relationship to SHA-256
- **Same algorithm**: Uses identical computation as SHA-256
- **Different IV**: Uses different initial hash values
- **Truncated output**: Final hash is truncated to 224 bits
- **Same performance**: Nearly identical speed to SHA-256

## Files

- `sha224.cpp` - Main hash computation demonstration
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
./sha224
```

### Save Output
```bash
./sha224 > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Security Level | Use Case |
|-----------|-----------|----------------|----------|
| SHA-224   | 224 bits  | 112 bits      | Space-constrained, moderate security |
| SHA-256   | 256 bits  | 128 bits      | General purpose, high security |
| SHA-384   | 384 bits  | 192 bits      | High security, larger output |
| SHA-512/224| 224 bits | 112 bits      | Alternative implementation |

## Use Cases

### Recommended Applications
- **Embedded systems**: Where 256-bit hashes are too large
- **Network protocols**: Bandwidth-constrained environments
- **Digital signatures**: DSA with 224-bit q parameter
- **Certificate systems**: Moderate security PKI applications
- **Legacy compatibility**: Systems designed for 224-bit hashes

### Security Level Considerations
- **112-bit security**: Suitable for most commercial applications
- **Collision resistance**: 2^112 operations required for collision
- **Pre-image resistance**: 2^224 operations required for inversion
- **Government use**: Acceptable for non-classified applications

## Security Properties

### Cryptographic Strength
- **Proven security**: Inherits SHA-256 security properties
- **Truncation security**: Truncation doesn't weaken collision resistance
- **Current status**: No known attacks, considered secure
- **Future outlook**: Expected to remain secure for foreseeable future

### Comparison with Alternatives
- **Versus SHA-256**: Slightly less secure but smaller output
- **Versus SHA-512/224**: Different internal structure, similar security
- **Versus BLAKE2s**: BLAKE2s generally faster with similar security

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

2. **Hash size expectations**
   ```
   Note: SHA-224 produces 28-byte output
   ```
   **Context**: Ensure applications expect 224-bit, not 256-bit hashes.

3. **Performance questions**
   ```
   Question: Why not use SHA-256 instead?
   ```
   **Answer**: SHA-224 provides space savings when output size matters.

## Implementation Notes

### OpenSSL Integration
- Available in default provider
- Standard EVP interface support
- Same performance characteristics as SHA-256
- Cross-platform compatibility

### Technical Details
- **Initial values**: Different from SHA-256 initial hash values
- **Computation**: Identical to SHA-256 through all rounds
- **Output truncation**: Last 32 bits discarded from SHA-256 output
- **Security proof**: Truncation security well-established

### When to Choose SHA-224
```cpp
// Choose SHA-224 when:
if (output_size_constrained && security_level_112_adequate) {
    use_sha224();
} else if (need_maximum_security) {
    use_sha256_or_higher();
} else if (performance_critical) {
    consider_blake2s();
}
```

## Historical Context

### Design Rationale
- **NIST requirement**: Needed hash function matching DSA key sizes
- **Standard compliance**: Required for certain FIPS 186 applications
- **Practical consideration**: Balance between security and efficiency
- **Implementation simplicity**: Reuses existing SHA-256 code

### Adoption Timeline
- **2001**: Standardized alongside SHA-256
- **2005**: Adopted in various cryptographic protocols
- **2010s**: Used in specialized applications requiring 224-bit output
- **Present**: Niche but stable usage in specific applications

## Modern Recommendations

### Decision Guidelines
1. **Use SHA-224 if**: Space constraints require smaller hash
2. **Use SHA-256 if**: General-purpose application without size limits  
3. **Use BLAKE2s if**: Performance is critical with size constraints
4. **Use SHA-512/224 if**: Need 64-bit optimized implementation

### Future Considerations
- **Quantum impact**: Grover's algorithm reduces security to ~56 bits
- **Migration path**: Easy upgrade to SHA-256 when needed
- **Standard support**: Continued support expected in cryptographic libraries
- **Application suitability**: Remains appropriate for moderate security needs