# RSA Public Key Cryptography Example

This example demonstrates RSA public key cryptography including key generation, encryption, and decryption using OpenSSL in C++.

## Overview

RSA is a widely-used public key cryptosystem that enables secure communication and digital signatures. Named after Rivest, Shamir, and Adleman, it's based on the mathematical difficulty of factoring large composite numbers.

## Algorithm Details

### Mathematical Foundation
- **Problem**: Integer factorization of large composite numbers
- **Key generation**: Based on two large prime numbers (p and q)
- **Security**: Relies on difficulty of factoring n = p × q
- **Operations**: Modular exponentiation for encryption/decryption

### Key Parameters
- **Key sizes**: 1024, 2048, 3072, 4096 bits (2048+ recommended)
- **Public key**: (n, e) where e is typically 65537
- **Private key**: (n, d) where d is the modular multiplicative inverse of e
- **Security level**: Approximately key_size/2 bits (e.g., 2048-bit ≈ 112-bit security)

## Files

- `rsa_create_key.cpp` - RSA key pair generation utility
- `rsa_example.cpp` - Main encryption/decryption demonstration
- `private_key.pem` - Generated private key (PEM format)
- `public_key.pem` - Generated public key (PEM format)
- `Makefile` - Build configuration for main example
- `Makefile.key` - Build configuration for key generation
- `out.txt` - Example output from running the program
- `README.md` - This documentation file

## Building and Running

### Prerequisites
- macOS with Homebrew
- OpenSSL 3.x: `brew install openssl`
- C++ compiler with C++11 support

### Step 1: Generate RSA Key Pair
```bash
make -f Makefile.key create
```
This creates:
- `private_key.pem` - 2048-bit RSA private key
- `public_key.pem` - Corresponding public key

### Step 2: Build and Run Example
```bash
make
./rsa_example
```

### Save Output
```bash
./rsa_example > out.txt
```

## Example Output Features

### Key Information Display
- Public key components (n, e)
- Private key components (d, p, q)
- Key size verification
- Modular arithmetic demonstration

### Encryption/Decryption Process
- OAEP padding demonstration
- Hex output formatting
- Security parameter explanation
- Error handling examples

## RSA Operations

### Public Key Encryption
```
Ciphertext = Plaintext^e mod n
```

### Private Key Decryption
```
Plaintext = Ciphertext^d mod n
```

### Digital Signatures
```
Signature = Hash(Message)^d mod n
Verification = Signature^e mod n == Hash(Message)
```

## Security Considerations

### Key Size Recommendations
| Key Size | Security Level | Use Case | Status |
|----------|----------------|----------|---------|
| 1024 bits | ~80 bits | Legacy only | Deprecated |
| 2048 bits | ~112 bits | Current standard | Recommended |
| 3072 bits | ~128 bits | High security | Future-proof |
| 4096 bits | ~150 bits | Maximum security | Performance impact |

### Padding Schemes
- **OAEP**: Recommended for encryption (used in this example)
- **PSS**: Recommended for digital signatures
- **PKCS#1 v1.5**: Legacy padding (vulnerable to attacks)
- **No padding**: Never use (completely insecure)

## Use Cases

### Recommended Applications
- **Key exchange**: Establish shared secrets for symmetric encryption
- **Digital signatures**: Authenticate messages and documents
- **Certificate authorities**: PKI and X.509 certificate systems
- **Secure protocols**: TLS/SSL handshakes and authentication
- **Code signing**: Software authenticity verification

### Performance Considerations
- **Slow encryption**: Use hybrid cryptosystems (RSA + AES)
- **Limited message size**: Can only encrypt data smaller than key size
- **CPU intensive**: Key generation and operations are computationally expensive
- **Memory usage**: Large keys require significant memory

## Troubleshooting

### Common Issues

1. **OpenSSL headers not found**
   ```
   Error: 'openssl/rsa.h' file not found
   ```
   **Solution**: Install OpenSSL development libraries:
   ```bash
   brew install openssl
   ```

2. **Key files missing**
   ```
   Error: Cannot open private_key.pem
   ```
   **Solution**: Generate keys first:
   ```bash
   make -f Makefile.key create
   ```

3. **Padding oracle attacks**
   ```
   Warning: PKCS#1 v1.5 padding is vulnerable
   ```
   **Solution**: Always use OAEP padding for encryption (default in this example).

4. **Message too long**
   ```
   Error: RSA_public_encrypt failed
   ```
   **Solution**: RSA can only encrypt small messages. Use hybrid cryptography for large data.

### Performance Optimization
- Use hardware acceleration when available
- Consider elliptic curve cryptography (ECC) for better performance
- Cache key operations when possible
- Use appropriate key sizes (2048 bits typically sufficient)

## Historical Context

### Development Timeline
- **1977**: RSA algorithm published by Rivest, Shamir, and Adleman
- **1983**: RSA Security founded to commercialize the algorithm
- **1997**: RSA patent expired, algorithm became freely available
- **2000s**: Widely adopted in internet protocols and standards

### Mathematical Foundation
- **Euler's theorem**: Fundamental to RSA correctness
- **Fermat's little theorem**: Special case used in key generation
- **Chinese remainder theorem**: Used for performance optimization
- **Factorization problem**: Basis for RSA security assumptions

## Implementation Notes

### OpenSSL Integration
- Uses EVP high-level interface for portability
- Supports multiple padding schemes
- Hardware acceleration when available
- Cross-platform compatibility

### Security Best Practices
- **Generate keys properly**: Use cryptographically secure random numbers
- **Protect private keys**: Store securely with proper access controls
- **Use correct padding**: OAEP for encryption, PSS for signatures
- **Validate inputs**: Check key sizes and parameter validity
- **Timing attacks**: Use constant-time implementations when possible

### Modern Alternatives
- **Elliptic Curve Cryptography (ECC)**: Smaller keys, better performance
- **Post-quantum cryptography**: Preparation for quantum computing threats
- **Hybrid systems**: Combine RSA with symmetric cryptography
- **Key agreement protocols**: Diffie-Hellman for perfect forward secrecy

### Quantum Computing Impact
- **Shor's algorithm**: Can efficiently factor large integers on quantum computers
- **Timeline**: Large-scale quantum computers may break RSA in 10-30 years
- **Mitigation**: Transition to post-quantum cryptographic algorithms
- **Current status**: RSA remains secure against classical computers

---
