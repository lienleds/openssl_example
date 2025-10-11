# SHA-256 Hash Example

This example demonstrates the SHA-256 cryptographic hash function using OpenSSL in C++.

## Overview

SHA-256 (Secure Hash Algorithm 256-bit) is part of the SHA-2 family, standardized by NIST in 2001. It's one of the most widely used cryptographic hash functions and forms the backbone of many security protocols.

## Algorithm Details

### Basic Parameters
- **Hash size**: 256 bits (32 bytes)
- **Block size**: 512 bits (64 bytes)
- **Security level**: 128 bits (collision resistance)
- **Standard**: FIPS 180-4, ISO/IEC 10118-3

### SHA-256 Operations
- **Message padding**: Ensures message length ≡ 448 (mod 512)
- **Message scheduling**: Expands 16 words to 64 words per block
- **Compression function**: 64 rounds of operations
- **Output truncation**: Final 256-bit hash value

## Files

- `sha256.cpp` - Main hash computation demonstration
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
./sha256
```

### Save Output
```bash
./sha256 > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Block Size | Security Level | Performance |
|-----------|-----------|------------|----------------|-------------|
| SHA-256   | 256 bits  | 512 bits   | 128 bits      | High        |
| SHA-224   | 224 bits  | 512 bits   | 112 bits      | High        |
| SHA-512   | 512 bits  | 1024 bits  | 256 bits      | High        |
| SHA3-256  | 256 bits  | 1088 bits  | 128 bits      | Medium      |

## Use Cases

### Recommended Applications
- **Digital signatures**: RSA, ECDSA, and DSA signature schemes
- **Certificate authorities**: X.509 certificates and PKI
- **Blockchain**: Bitcoin and many cryptocurrency systems
- **File integrity**: Checksums and data verification
- **Password hashing**: Combined with salt (though bcrypt/scrypt preferred)
- **HMAC**: Message authentication codes
- **Key derivation**: PBKDF2 and other key stretching functions

### Industry Standards
- **TLS/SSL**: Web security protocols
- **IPSec**: VPN and network security
- **SSH**: Secure shell protocol
- **PGP/GPG**: Email encryption
- **Code signing**: Software authenticity verification

## Security Properties

### Cryptographic Strength
- **Pre-image resistance**: Computationally infeasible to find input for given hash
- **Second pre-image resistance**: Hard to find different input with same hash
- **Collision resistance**: Extremely difficult to find two inputs with same hash
- **Avalanche effect**: Small input changes cause large output changes

### Current Status
- **No known attacks**: Resistant to all practical cryptanalytic attacks
- **NIST approved**: Part of current U.S. government standards
- **Widely analyzed**: Extensive peer review and cryptanalysis
- **Future outlook**: Expected to remain secure for foreseeable future

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

2. **Compilation errors on macOS**
   ```
   Error: cannot find -lssl -lcrypto
   ```
   **Solution**: Use provided Makefile with correct OpenSSL paths.

3. **Performance considerations**
   ```
   Note: SHA-256 performance varies by implementation
   ```
   **Optimization**: Modern CPUs may have SHA instruction extensions.

### Performance Notes
- SHA-256 is optimized for 32-bit and 64-bit processors
- Hardware acceleration available on many modern CPUs
- Consistent performance across different platforms
- Suitable for both high-throughput and embedded applications

## Historical Context

### Development Timeline
- **2001**: SHA-256 standardized as part of SHA-2 family
- **2005**: Weaknesses found in SHA-1, increased SHA-256 adoption
- **2009**: Bitcoin uses SHA-256, bringing widespread attention
- **2012**: NIST begins SHA-3 competition (complement, not replacement)

### Design Philosophy
- **Conservative approach**: Built on proven cryptographic principles
- **Performance optimization**: Balanced security and speed
- **Scalability**: Works well from embedded to server applications
- **Standardization**: Designed for broad adoption and interoperability

## Implementation Notes

### OpenSSL Integration
- Available in default provider
- Standard EVP interface support
- Hardware acceleration when available
- Cross-platform implementation

### Technical Details
- **Initial hash values**: Eight 32-bit constants (fractional parts of square roots)
- **Round constants**: 64 constants (fractional parts of cube roots of first 64 primes)
- **Logical functions**: Ch, Maj, Σ0, Σ1, σ0, σ1
- **Modular arithmetic**: All operations performed modulo 2^32

### Performance Characteristics
- **Software speed**: Fast on modern processors
- **Hardware friendly**: Suitable for ASIC/FPGA implementation
- **Memory usage**: Minimal state requirements
- **Parallel processing**: Each block processed independently

### Modern Context
- **Quantum resistance**: Grover's algorithm reduces effective security to 128 bits
- **Post-quantum transition**: SHA-256 expected to remain part of future systems
- **Current recommendation**: Continues to be recommended by NIST and industry
- **Migration planning**: No immediate need to replace, but monitor developments