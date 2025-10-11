# AES-GCM (Galois/Counter Mode) Example

## Algorithm Overview

AES-GCM (Advanced Encryption Standard in Galois/Counter Mode) is an Authenticated Encryption with Associated Data (AEAD) cipher mode that provides both confidentiality and authenticity in a single operation. It's widely used in modern cryptographic protocols and is considered the gold standard for AEAD encryption.

### Key Characteristics
- **Algorithm Type**: Authenticated Encryption with Associated Data (AEAD)
- **Key Size**: 128, 192, or 256 bits
- **Block Size**: 128 bits
- **IV/Nonce Size**: 96 bits (recommended) or variable
- **Tag Size**: 128 bits (default), configurable 96-128 bits
- **Security Level**: ★★★★★ (Maximum security when used correctly)

## Security Properties

### Strengths
- **Authenticated Encryption**: Provides both confidentiality and authenticity
- **Efficiency**: Hardware acceleration available on modern processors
- **Parallelizable**: Encryption and authentication can be parallelized
- **Associated Data**: Can authenticate additional unencrypted data
- **Proven Security**: Extensive cryptanalytic review and formal proofs

### Security Requirements
- **Nonce Uniqueness**: Each encryption must use a unique nonce
- **Key Management**: Proper random key generation required
- **Tag Verification**: Authentication tag must always be verified

## Use Cases

### Recommended Applications
- **TLS 1.2/1.3**: Primary cipher suite for secure communications
- **IPsec**: VPN and secure network communications
- **Cloud Storage**: Encrypting data at rest with integrity
- **Secure Messaging**: Modern messaging protocol encryption
- **Database Encryption**: Column-level and transparent data encryption

### Protocol Integration
- **HTTP/2**: Secure web communications
- **QUIC**: Modern transport protocol encryption
- **JOSE/JWE**: JSON Web Encryption standard
- **SSH**: Secure shell communications
- **File Systems**: Encrypted file system implementations

## Security Analysis

### Attack Resistance
- **Chosen Plaintext**: Secure against adaptive chosen plaintext attacks
- **Chosen Ciphertext**: Provides strong authentication against tampering
- **Birthday Attacks**: 64-bit collision resistance in authentication
- **Side Channel**: Hardware implementations resist timing attacks

### Critical Requirements
1. **Never reuse nonce with same key**: Catastrophic security failure
2. **Always verify authentication tag**: Decrypt only after verification
3. **Secure random number generation**: For keys and nonces
4. **Proper key lifecycle management**: Key rotation and secure storage

## Code Example

This implementation demonstrates AES-GCM encryption and decryption:

```cpp
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

// AEAD encryption with authentication
int aes_gcm_encrypt(const unsigned char *plaintext, int plaintext_len,
                   const unsigned char *aad, int aad_len,
                   const unsigned char *key,
                   const unsigned char *iv, int iv_len,
                   unsigned char *ciphertext,
                   unsigned char *tag)
```

## Files Description

- `aes_gcm.cpp` - Main AES-GCM encryption/decryption example
- `Makefile` - Build configuration
- `out.txt` - Example program output

## Build and Run

```bash
# Build the example
make

# Run AES-GCM demonstration
./aes_gcm

# View example output
cat out.txt
```

## Performance Considerations

### Hardware Acceleration
- **AES-NI**: Intel/AMD processors with dedicated AES instructions
- **PMULL**: ARM processors with polynomial multiplication
- **Throughput**: Multi-gigabit speeds on modern hardware
- **Latency**: Low latency for small messages

### Optimization Tips
- Use hardware-accelerated implementations when available
- Batch operations for better throughput
- Consider CTR-DRBG for nonce generation
- Implement proper key caching strategies

## Implementation Details

### Nonce Management
```cpp
// Generate cryptographically secure random nonce
unsigned char nonce[12];  // 96-bit nonce
RAND_bytes(nonce, sizeof(nonce));
```

### Associated Data Usage
- Headers that need authentication but not encryption
- Protocol metadata and routing information
- Session identifiers and timestamps
- Any data requiring integrity protection

## Common Pitfalls

### Critical Errors to Avoid
1. **Nonce Reuse**: Devastating cryptographic failure
2. **Missing Tag Verification**: Allows tampering attacks
3. **Weak Random Generation**: Predictable nonces/keys
4. **Improper Key Storage**: Keys in plaintext memory
5. **Side Channel Leaks**: Timing-based information disclosure

### Best Practices
- Always use cryptographically secure random number generators
- Implement constant-time comparison for authentication tags
- Clear sensitive data from memory after use
- Use proper key derivation functions (HKDF, PBKDF2)
- Implement proper error handling without information leakage

## Troubleshooting

### Common Issues
- **Authentication failure**: Check tag verification implementation
- **Nonce collision**: Ensure unique nonce for each encryption
- **Performance issues**: Verify hardware acceleration is enabled
- **Memory leaks**: Proper cleanup of EVP contexts

### Debugging Tips
```bash
# Check OpenSSL version and features
openssl version -a

# Verify AES-NI support
grep -i aes /proc/cpuinfo

# Test with known vectors
./aes_gcm test-vectors
```

## Standards and Compliance

### Specifications
- **NIST SP 800-38D**: GCM specification
- **RFC 5116**: AEAD cipher interface
- **FIPS 140-2**: Validated implementations available
- **Common Criteria**: EAL4+ certified implementations

### Industry Standards
- **TLS 1.2/1.3**: Mandatory cipher suite
- **IEEE 802.11**: WPA3 wireless security
- **NIST**: Recommended for government use
- **FIDO2/WebAuthn**: Secure authentication protocols

## Related Algorithms

### AEAD Alternatives
- **ChaCha20-Poly1305**: Software-optimized AEAD
- **AES-CCM**: Counter with CBC-MAC mode
- **AES-OCB**: High-performance AEAD mode
- **AES-SIV**: Synthetic IV mode

### Performance Comparison
- **AES-GCM**: Best hardware performance
- **ChaCha20-Poly1305**: Best software performance
- **AES-CCM**: Lower memory requirements
- **AES-SIV**: Misuse resistance

## References

- NIST SP 800-38D: Recommendation for Block Cipher Modes
- RFC 5116: An Interface and Algorithms for AEAD
- McGrew, D., Viega, J.: "The Galois/Counter Mode of Operation (GCM)"
- Iwata, T., et al.: "Breaking and Repairing GCM Security Proofs"

AES-GCM represents the current state-of-the-art in authenticated encryption, providing both security and performance for modern applications.