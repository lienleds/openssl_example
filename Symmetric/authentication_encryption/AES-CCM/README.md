# AES-CCM (Counter with CBC-MAC) Example

## Algorithm Overview

AES-CCM (Advanced Encryption Standard in Counter with CBC-MAC mode) is an Authenticated Encryption with Associated Data (AEAD) cipher mode that combines CTR mode encryption with CBC-MAC authentication. It's designed for constrained environments where memory usage is critical.

### Key Characteristics
- **Algorithm Type**: Authenticated Encryption with Associated Data (AEAD)
- **Key Size**: 128, 192, or 256 bits
- **Block Size**: 128 bits
- **Nonce Size**: 7-13 bytes (variable, affects counter size)
- **Tag Size**: 4, 6, 8, 10, 12, 14, or 16 bytes (configurable)
- **Security Level**: ★★★★☆ (High security with proper configuration)

## Security Properties

### Strengths
- **Authenticated Encryption**: Provides confidentiality and authenticity
- **Memory Efficient**: Lower memory requirements than GCM
- **Deterministic**: No randomness required after key/nonce generation
- **Provable Security**: Formal security proofs available
- **Flexible Parameters**: Configurable nonce and tag lengths

### Constraints
- **Two-Pass Algorithm**: Requires two passes over the data
- **Length Prefix**: Message length must be known in advance
- **Sequential Processing**: Cannot be parallelized like GCM
- **Performance**: Generally slower than GCM on modern hardware

## Use Cases

### Optimal Applications
- **IoT Devices**: Constrained memory environments
- **Embedded Systems**: Real-time systems with limited resources
- **IEEE 802.15.4**: Wireless sensor networks (ZigBee)
- **Bluetooth LE**: Low energy wireless communications
- **Smart Cards**: Secure element implementations

### Protocol Integration
- **WPA3**: WiFi security for resource-constrained devices
- **Thread**: IPv6 mesh networking protocol
- **Matter**: Smart home connectivity standard
- **DTLS**: Datagram TLS for UDP-based protocols
- **CoAP**: Constrained Application Protocol security

## Security Analysis

### Attack Resistance
- **Chosen Plaintext**: Secure with unique nonces
- **Chosen Ciphertext**: Strong authentication prevents tampering
- **Forgery Attacks**: Authentication tag provides integrity
- **Birthday Attacks**: Tag length determines collision resistance

### Critical Requirements
1. **Unique Nonces**: Never reuse nonce with same key
2. **Known Message Length**: Length must be available before processing
3. **Tag Verification**: Always verify authentication before decryption
4. **Parameter Selection**: Proper nonce/tag length for security level

## Implementation Details

### Parameter Selection
```cpp
// Nonce length affects counter space
// Longer nonce = shorter counter = smaller max message size
uint8_t nonce_len = 12;  // Common choice: 96-bit nonce
uint8_t tag_len = 16;    // Maximum security: 128-bit tag

// Maximum message size = 2^(8*(15-nonce_len)) bytes
// nonce_len=12 allows ~16MB messages
// nonce_len=7 allows ~256GB messages
```

### Memory Optimization
- Single block buffer for CBC-MAC computation
- Streaming interface for large messages
- In-place encryption when possible
- Minimal state maintenance

## Code Example

This implementation demonstrates AES-CCM encryption and decryption:

```cpp
#include <openssl/evp.h>
#include <openssl/aes.h>

// Two-pass AEAD encryption
int aes_ccm_encrypt(const unsigned char *plaintext, int plaintext_len,
                   const unsigned char *aad, int aad_len,
                   const unsigned char *key,
                   const unsigned char *nonce, int nonce_len,
                   unsigned char *ciphertext,
                   unsigned char *tag, int tag_len)
```

## Files Description

- `aes_ccm_example.cpp` - Main AES-CCM encryption/decryption example
- `Makefile` - Build configuration

## Build and Run

```bash
# Build the example
make

# Run AES-CCM demonstration
./aes_ccm_example
```

## Performance Considerations

### Memory Usage
- **Minimal RAM**: Single AES block buffer required
- **Stack Friendly**: Low stack usage for embedded systems
- **No Large Tables**: Unlike GCM's multiplication tables
- **Streaming**: Can process arbitrarily large messages

### Processing Overhead
- **Two Passes**: Authentication then encryption passes
- **Sequential**: No parallelization opportunities
- **Block Aligned**: Optimal with block-sized operations
- **Hardware**: AES-NI acceleration for AES operations only

## Configuration Guidelines

### Nonce Length Selection
```cpp
// Security vs Message Size Trade-off
//
// Nonce=7:  Max Message=256GB,  Counter=64-bit
// Nonce=8:  Max Message=16GB,   Counter=56-bit  
// Nonce=12: Max Message=16MB,   Counter=24-bit (common)
// Nonce=13: Max Message=1MB,    Counter=16-bit
```

### Tag Length Selection
- **16 bytes**: Maximum security (128-bit)
- **12 bytes**: Good balance (96-bit)
- **8 bytes**: Constrained environments (64-bit)
- **4 bytes**: Minimal security (32-bit) - avoid if possible

## Common Implementation Patterns

### Embedded Systems
```cpp
// Typical IoT configuration
#define CCM_NONCE_LEN 12    // 96-bit nonce
#define CCM_TAG_LEN 8       // 64-bit authentication
#define CCM_KEY_LEN 16      // AES-128

// Memory-efficient processing
uint8_t buffer[16];  // Single AES block
```

### Network Protocols
```cpp
// DTLS-style configuration
#define CCM_NONCE_LEN 12    // Compatible with TLS nonce
#define CCM_TAG_LEN 16      // Full security
#define CCM_KEY_LEN 32      // AES-256
```

## Error Handling

### Common Failure Modes
1. **Length Mismatch**: Declared vs actual message length
2. **Parameter Validation**: Invalid nonce/tag lengths
3. **Authentication Failure**: Corrupted or tampered data
4. **Memory Constraints**: Insufficient buffer space

### Robust Implementation
```cpp
// Always check return values
if (EVP_EncryptInit_ex(ctx, EVP_aes_128_ccm(), NULL, NULL, NULL) != 1) {
    // Handle initialization error
}

// Validate parameters before processing
if (nonce_len < 7 || nonce_len > 13) {
    return -1; // Invalid nonce length
}
```

## Troubleshooting

### Common Issues
- **Two-pass requirement**: Ensure length is set before data
- **Nonce management**: Avoid nonce reuse
- **Tag verification**: Check authentication before use
- **Parameter limits**: Respect nonce/tag length constraints

### Debug Techniques
```bash
# Verify OpenSSL CCM support
openssl enc -aes-128-ccm -help

# Test with known vectors
# Use NIST test vectors for validation
```

## Standards and Specifications

### References
- **RFC 3610**: Counter with CBC-MAC (CCM)
- **NIST SP 800-38C**: CCM Mode specification
- **IEEE 802.11i**: WiFi security standard
- **RFC 5116**: AEAD interface specification

### Test Vectors
- NIST CAVP test vectors available
- RFC 3610 includes test cases
- IEEE 802.15.4 provides examples
- OpenSSL test suite validation

## Comparison with Other AEAD Modes

| Feature | AES-CCM | AES-GCM | ChaCha20-Poly1305 |
|---------|---------|---------|-------------------|
| Memory Usage | Low | Medium | Low |
| Performance | Medium | High | High |
| Parallelizable | No | Yes | Partially |
| Hardware Accel | AES only | Full | Software opt |
| Flexibility | High | Medium | Low |

## Related Algorithms

### AEAD Alternatives
- **AES-GCM**: Higher performance, more memory
- **ChaCha20-Poly1305**: Software-optimized alternative
- **AES-OCB**: Patent-encumbered high-performance mode
- **AES-EAX**: Two-pass mode similar to CCM

### Legacy Modes
- **AES-CBC + HMAC**: Encrypt-then-MAC construction
- **AES-CTR + HMAC**: Counter mode with authentication
- **AES-CBC-MAC**: Authentication only (no encryption)

## References

- RFC 3610: Counter with CBC-MAC (CCM)
- NIST SP 800-38C: Recommendation for CCM Mode
- Whiting, D., et al.: "Counter with CBC-MAC (CCM)"
- Jonsson, J.: "On the Security of CTR + CBC-MAC"

AES-CCM provides authenticated encryption optimized for memory-constrained environments while maintaining strong security properties.