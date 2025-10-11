# ChaCha20 Stream Cipher Example

This example demonstrates ChaCha20, a modern high-speed stream cipher designed by Daniel J. Bernstein, using OpenSSL in C++.

## Overview

ChaCha20 is a stream cipher that offers excellent performance and security. It's widely used in modern protocols like TLS 1.3, WireGuard VPN, and various cryptographic applications requiring high-speed encryption.

## Algorithm Details

### Basic Parameters
- **Key size**: 256 bits (32 bytes)
- **Nonce size**: 96 bits (12 bytes) or 64 bits (8 bytes)
- **Block counter**: 32-bit or 64-bit counter
- **Output**: Pseudorandom keystream XORed with plaintext

### ChaCha20 Structure
- **Quarter-round function**: Core cryptographic primitive
- **20 rounds**: Provides security margin (ChaCha8, ChaCha12 variants exist)
- **ARX operations**: Addition, Rotation, XOR (simple and fast)
- **Constant-time**: Naturally resistant to timing attacks

## Files

- `chacha20.cpp` - Main ChaCha20 encryption/decryption demonstration
- `chacha20_create_key.cpp` - Key and nonce generation utility
- `chacha20_key.bin` - Generated 256-bit ChaCha20 key
- `chacha20_nonce.bin` - Generated 96-bit nonce
- `Makefile` - Build configuration for main example
- `Makefile.key` - Build configuration for key generation
- `out.txt` - Example output from running the program
- `README.md` - This documentation file

## Building and Running

### Prerequisites
- macOS with Homebrew
- OpenSSL 3.x: `brew install openssl`
- C++ compiler with C++11 support

### Step 1: Generate Key and Nonce
```bash
make -f Makefile.key create
```
This creates:
- `chacha20_key.bin` - 256-bit encryption key
- `chacha20_nonce.bin` - 96-bit nonce (number used once)

### Step 2: Build and Run Example
```bash
make
./chacha20
```

### Save Output
```bash
./chacha20 > out.txt
```

## Stream Cipher Comparison

| Algorithm | Key Size | Nonce Size | Speed | Security | Status |
|-----------|----------|------------|--------|----------|---------|
| ChaCha20  | 256 bits | 96 bits   | Very High | High | Modern |
| Salsa20   | 256 bits | 64 bits   | High     | High | Superseded |
| RC4       | Variable | None      | High     | Broken | Deprecated |
| AES-CTR   | 128-256 bits | 96 bits | High*  | High | Standard |

*AES-CTR speed depends on hardware acceleration availability

## Use Cases

### Recommended Applications
- **High-performance encryption**: Bulk data encryption requiring speed
- **Mobile applications**: Battery-efficient encryption for smartphones
- **VPN protocols**: WireGuard and other modern VPN implementations
- **TLS connections**: TLS 1.3 cipher suites for web security
- **Real-time communications**: Video calls and streaming applications
- **Embedded systems**: Resource-constrained devices

### Performance Benefits
- **Software speed**: Faster than AES without hardware acceleration
- **Constant-time**: Natural resistance to side-channel attacks
- **Simple implementation**: Easy to implement correctly and efficiently
- **No lookup tables**: Reduces cache-timing attack surface

## Security Properties

### Cryptographic Strength
- **256-bit security level**: Equivalent to AES-256
- **Proven security**: Extensive cryptanalysis over many years
- **No known vulnerabilities**: Resistant to all known attacks
- **Simple design**: Easier to analyze and implement securely

### Nonce Requirements
- **Uniqueness**: Never reuse nonce with same key
- **Size**: 96 bits provides ample space (2^32 messages with random nonces)
- **Counter mode**: Can use sequential nonces for some applications
- **Randomness**: Cryptographically secure random generation recommended

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

2. **ChaCha20 not available**
   ```
   Error: Unknown cipher chacha20
   ```
   **Solution**: Ensure OpenSSL 1.1.0+ is installed (ChaCha20 support added).

3. **Nonce reuse**
   ```
   Security Warning: Nonce reused with same key
   ```
   **Solution**: Generate new nonce for each encryption operation.

4. **Key files missing**
   ```
   Error: Cannot open chacha20_key.bin
   ```
   **Solution**: Generate keys first with `make -f Makefile.key create`.

### Performance Optimization
- ChaCha20 is inherently fast and doesn't require special optimization
- Benefits from modern CPU features (SIMD instructions)
- Consistent performance across different platforms
- No key setup cost (unlike block ciphers)

## Historical Context

### Development Timeline
- **2008**: ChaCha family designed by Daniel J. Bernstein
- **2013**: ChaCha20-Poly1305 adopted by Google for TLS
- **2015**: RFC 7539 standardizes ChaCha20-Poly1305
- **2018**: TLS 1.3 includes ChaCha20-Poly1305 cipher suites

### Design Philosophy
- **Performance**: Designed to be fast in software
- **Security**: Conservative approach with large security margins
- **Simplicity**: Easy to implement correctly
- **Portability**: Consistent performance across architectures

## Implementation Notes

### OpenSSL Integration
- Available in default provider (OpenSSL 1.1.0+)
- Standard EVP interface support
- ChaCha20-Poly1305 AEAD mode available
- Cross-platform implementation

### Technical Details
- **State initialization**: 512-bit state from key, nonce, and constants
- **Quarter-round**: (a,b,c,d) → operations on 32-bit words
- **Parallelization**: Can process multiple blocks in parallel
- **Keystream generation**: XOR keystream with plaintext for encryption

### Modern Applications
- **WireGuard VPN**: Uses ChaCha20-Poly1305 for encryption
- **TLS 1.3**: Alternative to AES for devices without AES-NI
- **Signal Protocol**: Secure messaging encryption
- **Tor**: Anonymous communication network
- **SSH**: OpenSSH supports ChaCha20-Poly1305

### Advantages Over AES
- **Software performance**: Faster than AES without hardware acceleration
- **Constant-time**: Natural timing attack resistance
- **Memory access**: No table lookups, cache-friendly
- **Mobile friendly**: Better battery life on ARM processors

3. **Output:**
   - The program prints the key, nonce, ciphertext (in hex), ciphertext length, plaintext length, and the decrypted text.

## Notes
- The key and nonce are loaded from files for better security and modularity.
- Requires OpenSSL development libraries.
- All code is formatted in Allman style for readability.

## References
- [OpenSSL EVP documentation](https://www.openssl.org/docs/manmaster/man3/EVP_EncryptInit.html)
- [Wikipedia: ChaCha20](https://en.wikipedia.org/wiki/Salsa20#ChaCha_variant)
