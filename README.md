# OpenSSL Cryptographic Examples Collection

A comprehensive collection of cryptographic algorithm examples implemented in C++ using OpenSSL, covering hash functions, symmetric encryption, asymmetric cryptography, and more.

## 🎯 Overview

This repository provides practical, educational examples of cryptographic algorithms using OpenSSL 3.x. Each example includes complete source code, detailed explanations, build instructions, and comprehensive documentation to help developers understand and implement cryptographic operations correctly.

## 📁 Repository Structure

```
openssl_example/
├── Hash/                          # Cryptographic Hash Functions
│   ├── blake2b512/               # BLAKE2b 512-bit hash
│   ├── blake2s256/               # BLAKE2s 256-bit hash  
│   ├── MD5/                      # MD5 (legacy, educational only)
│   ├── mdc2/                     # MDC-2 hash function
│   ├── ripemd160/               # RIPEMD-160 hash
│   ├── SHA-1/                   # SHA-1 (legacy, educational only)
│   ├── SHA-224/                 # SHA-224 hash
│   ├── SHA-256/                 # SHA-256 hash
│   ├── SHA-384/                 # SHA-384 hash
│   ├── SHA-512/                 # SHA-512 hash
│   ├── sha3-224/                # SHA3-224 hash
│   ├── SHA3-256/                # SHA3-256 hash
│   ├── SHA3-384/                # SHA3-384 hash
│   ├── SHA3-512/                # SHA3-512 hash
│   ├── sm3/                     # SM3 (Chinese national standard)
│   └── whirlpool/               # Whirlpool hash function
├── Symmetric/                    # Symmetric Key Cryptography
│   ├── block_cipers/           # Block Ciphers
│   │   ├── 3DES/               # Triple DES
│   │   ├── AES-CBC/            # AES in CBC mode
│   │   ├── AES-CBC-HMAC/       # AES-CBC with HMAC authentication
│   │   ├── Blowfish/           # Blowfish cipher
│   │   ├── Camellia/           # Camellia cipher
│   │   ├── CAST5/              # CAST5 cipher
│   │   ├── DES/                # DES (legacy, educational only)
│   │   ├── IDEA/               # IDEA cipher
│   │   ├── RC2/                # RC2 cipher
│   │   └── SEED/               # SEED (Korean national standard)
│   ├── stream_ciphers/         # Stream Ciphers
│   │   └── chacha20/           # ChaCha20 stream cipher
│   └── authentication_encryption/ # Authenticated Encryption
│       ├── AES-CCM/            # AES in CCM mode
│       ├── AES-GCM/            # AES in GCM mode
│       └── ChaCha20-Poly1305/  # ChaCha20-Poly1305 AEAD
└── Asymmetric/                   # Public Key Cryptography
    ├── RSA/                     # RSA encryption and signatures
    ├── ECC/                     # Elliptic Curve Cryptography
    ├── DSA/                     # Digital Signature Algorithm
    └── Diffie-Hellman/          # Diffie-Hellman key exchange
```

## 🚀 Quick Start

### Prerequisites

#### macOS (Homebrew)
```bash
# Install OpenSSL
brew install openssl

# Install development tools
xcode-select --install
```

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential libssl-dev
```

#### CentOS/RHEL
```bash
sudo yum groupinstall "Development Tools"
sudo yum install openssl-devel
```

### Running Examples

Each algorithm directory contains:
- **Source code**: Implementation with detailed comments
- **Makefile**: Build configuration optimized for the platform
- **README.md**: Algorithm-specific documentation
- **Key generation**: Utilities for generating cryptographic keys
- **Test data**: Sample inputs and expected outputs

#### General Pattern
```bash
# Navigate to any algorithm directory
cd Hash/SHA-256

# Build the example
make

# Run the example
./sha256

# Save output for analysis
./sha256 > output.txt
```

#### For Symmetric Ciphers
```bash
# Navigate to cipher directory
cd Symmetric/block_cipers/AES-CBC

# Generate keys first
make -f Makefile.key create

# Build and run example
make
./aes_cbc
```

## 🔐 Algorithm Categories

### Hash Functions
Cryptographic hash functions for data integrity, digital signatures, and password verification.

#### Modern Recommended
- **SHA-256/SHA-512**: NIST standard, widely supported
- **SHA3-256/SHA3-512**: Latest NIST standard, sponge construction
- **BLAKE2b/BLAKE2s**: High-performance alternative to SHA-2

#### Specialized/National Standards
- **SM3**: Chinese national cryptographic standard
- **Whirlpool**: ISO/IEC standard based on AES design

#### Educational/Legacy
- **MD5**: Cryptographically broken, educational purposes only
- **SHA-1**: Deprecated, educational purposes only

### Symmetric Encryption

#### Block Ciphers
Fixed-size block encryption algorithms.

**Modern Standards:**
- **AES**: Current global standard (128/192/256-bit keys)
- **Camellia**: Japanese standard, AES alternative
- **SEED**: Korean standard, government applications

**Historical/Educational:**
- **DES/3DES**: Legacy standards, educational value
- **Blowfish**: Variable key length, educational interest
- **IDEA**: PGP cipher, patent expired
- **CAST5**: OpenPGP standard
- **RC2**: Microsoft CryptoAPI legacy

#### Stream Ciphers
Bit-by-bit encryption algorithms.

- **ChaCha20**: Modern high-speed cipher, TLS 1.3 standard

#### Authenticated Encryption
Provides both confidentiality and authenticity.

- **AES-GCM**: High-performance authenticated encryption
- **AES-CCM**: Lower memory usage alternative
- **ChaCha20-Poly1305**: Modern AEAD for mobile/embedded systems

### Asymmetric Cryptography
Public key cryptography for secure communication and digital signatures.

- **RSA**: Widely-used public key system for encryption and signatures
- **ECC (ECDSA)**: Elliptic curve cryptography, smaller keys than RSA
- **DSA**: Digital signatures, government standard
- **Diffie-Hellman**: Key exchange protocol, foundation of many protocols

## 🛡️ Security Recommendations

### For Production Use

#### Hash Functions
1. **SHA-256** or **SHA-512** for general purposes
2. **SHA3-256** for diversity from SHA-2
3. **BLAKE2b** for high-performance applications

#### Symmetric Encryption
1. **AES-256-GCM** for authenticated encryption
2. **ChaCha20-Poly1305** for mobile/embedded systems
3. **AES-CBC + HMAC** for legacy compatibility (with proper implementation)

#### Asymmetric Cryptography
1. **RSA-2048** minimum, **RSA-3072** preferred for new systems
2. **ECDSA P-256** or **P-384** for better performance
3. **Ed25519** for modern applications (when available)

### Deprecated/Avoid
- **MD5**: Cryptographically broken
- **SHA-1**: Collision attacks demonstrated
- **DES**: 56-bit key too small
- **RC4**: Multiple vulnerabilities
- **RSA-1024**: Insufficient key length

## 🔧 Build System

Each example includes optimized Makefiles with:
- **Platform detection**: Automatic OpenSSL path detection for macOS
- **Compiler optimization**: Performance and security flags
- **Dependency management**: Clear library requirements
- **Cross-compilation**: Support for different architectures

### Common Makefile Targets
```bash
make           # Build main example
make clean     # Remove compiled binaries
make -f Makefile.key create  # Generate cryptographic keys
```

## 📚 Educational Features

### Code Quality
- **Clean C++ code**: Modern C++11 standards
- **Detailed comments**: Explaining cryptographic concepts
- **Error handling**: Proper OpenSSL error management
- **Security practices**: Secure key handling and memory management

### Documentation
- **Algorithm explanations**: Mathematical foundations and security properties
- **Historical context**: Development timeline and standardization
- **Use case guidance**: When and how to use each algorithm
- **Security analysis**: Strengths, weaknesses, and recommendations

### Learning Path
1. **Start with hash functions**: Understand cryptographic basics
2. **Move to symmetric encryption**: Learn about keys and modes
3. **Explore asymmetric cryptography**: Public key concepts
4. **Study authenticated encryption**: Modern security requirements

## 🔍 Troubleshooting

### Common Issues

#### OpenSSL Not Found
```bash
Error: 'openssl/evp.h' file not found
```
**Solution**: Install OpenSSL development libraries using platform package manager.

#### Legacy Provider Required
```bash
Error: cipher/digest not available
```
**Solution**: Some older algorithms require loading the legacy provider in OpenSSL 3.x.

#### Compilation Errors
```bash
Error: cannot find -lssl -lcrypto
```
**Solution**: Use provided Makefiles with correct library paths for your platform.

### Platform-Specific Notes

#### macOS
- Makefiles automatically detect Homebrew OpenSSL installation
- May need to set `LIBRARY_PATH` for custom OpenSSL installations
- Apple's LibreSSL doesn't include all algorithms

#### Linux
- Use distribution package manager for OpenSSL installation
- Different distributions may have different package names
- Check for separate development packages (-dev, -devel)

## 🚦 Version Compatibility

### OpenSSL Versions
- **Recommended**: OpenSSL 3.x (latest stable)
- **Supported**: OpenSSL 1.1.1 (with minor modifications)
- **Legacy**: OpenSSL 1.0.x (requires significant changes)

### Algorithm Availability
- **Default provider**: AES, SHA-2, SHA-3, RSA, ECC
- **Legacy provider**: RC2, RC4, DES, MD5, etc.
- **FIPS provider**: FIPS 140-2 validated algorithms

## 📖 References and Standards

### Standards Organizations
- **NIST**: SP 800 series cryptographic standards
- **ISO/IEC**: International cryptographic standards
- **IETF**: Internet cryptographic protocol standards
- **ANSI**: American national standards

### Key Publications
- **FIPS 197**: AES specification
- **FIPS 180-4**: SHA-2 specification  
- **FIPS 202**: SHA-3 specification
- **RFC 8439**: ChaCha20-Poly1305 specification

## 🤝 Contributing

Contributions are welcome! Please:
1. Follow the existing code style and documentation format
2. Include comprehensive test cases and examples
3. Update README files with algorithm details
4. Ensure cross-platform compatibility

## ⚖️ License

This project is intended for educational and research purposes. Individual algorithms may be subject to patents or export restrictions. Always verify legal compliance for your specific use case.

## 🔗 Additional Resources

- [OpenSSL Documentation](https://www.openssl.org/docs/)
- [Crypto++ Library](https://www.cryptopp.com/)
- [Applied Cryptography by Bruce Schneier](https://www.schneier.com/books/applied_cryptography/)
- [Cryptography Engineering by Ferguson, Schneier, and Kohno](https://www.schneier.com/books/cryptography_engineering/)

---

*Note: This collection is for educational purposes. Always use well-tested cryptographic libraries and follow current security best practices for production applications.*