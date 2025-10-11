# ECC (Elliptic Curve Cryptography) Example

This example demonstrates Elliptic Curve Digital Signature Algorithm (ECDSA) using OpenSSL in C++, including key generation, message signing, and signature verification.

## Overview

Elliptic Curve Cryptography (ECC) provides the same cryptographic strength as RSA with significantly smaller key sizes, making it ideal for resource-constrained environments and modern applications requiring high performance.

## Algorithm Details

### Mathematical Foundation
- **Problem**: Elliptic Curve Discrete Logarithm Problem (ECDLP)
- **Curve equation**: y² = x³ + ax + b (mod p) for prime curves
- **Point operations**: Point addition and scalar multiplication on elliptic curves
- **Security**: Based on difficulty of finding k given k×G = P

### Key Parameters
- **Curve types**: secp256r1 (P-256), secp384r1 (P-384), secp521r1 (P-521)
- **Key sizes**: 256-bit, 384-bit, 521-bit (much smaller than equivalent RSA)
- **Security levels**: 128-bit, 192-bit, 256-bit respectively
- **Performance**: Significantly faster than RSA for equivalent security

## Files

- `ecc_create_key.cpp` - ECC key pair generation utility
- `ecc_example.cpp` - Digital signature demonstration with ECDSA
- `ec_private.pem` - Generated private key (PEM format)
- `ec_public.pem` - Generated public key (PEM format)
- `Makefile` - Build configuration for main example
- `Makefile.key` - Build configuration for key generation
- `out.txt` - Example output from running the program
- `README.md` - This documentation file

## Building and Running

### Prerequisites
- macOS with Homebrew
- OpenSSL 3.x: `brew install openssl`
- C++ compiler with C++11 support

### Step 1: Generate ECC Key Pair
```bash
make -f Makefile.key create
```
This creates:
- `ec_private.pem` - secp256r1 (P-256) private key
- `ec_public.pem` - Corresponding public key

### Step 2: Build and Run Example
```bash
make
./ecc_example
```

### Save Output
```bash
./ecc_example > out.txt
```

## Example Output Features

### Key Information Display
- Elliptic curve parameters
- Public key point coordinates (x, y)
- Private key scalar value
- Curve verification

### Digital Signature Process
- Message hashing (SHA-256)
- ECDSA signature generation
- Signature verification (valid and invalid cases)
- DER encoding demonstration

## ECDSA Operations

### Key Generation
1. Select elliptic curve parameters
2. Generate random private key d
3. Calculate public key Q = d × G (where G is base point)

### Signature Generation
1. Hash message: h = SHA-256(message)
2. Generate random k
3. Calculate r = (k × G).x mod n
4. Calculate s = k⁻¹(h + rd) mod n
5. Signature is (r, s)

### Signature Verification
1. Hash message: h = SHA-256(message)
2. Calculate u₁ = h × s⁻¹ mod n
3. Calculate u₂ = r × s⁻¹ mod n
4. Verify (u₁ × G + u₂ × Q).x ≡ r mod n

## Security Comparison

### ECC vs RSA Key Sizes
| Security Level | ECC Key Size | RSA Key Size | Performance Ratio |
|----------------|--------------|--------------|-------------------|
| 80 bits        | 160 bits     | 1024 bits    | ~10:1            |
| 112 bits       | 224 bits     | 2048 bits    | ~6:1             |
| 128 bits       | 256 bits     | 3072 bits    | ~6:1             |
| 192 bits       | 384 bits     | 7680 bits    | ~10:1            |
| 256 bits       | 521 bits     | 15360 bits   | ~15:1            |

### ECC vs Other Digital Signature Algorithms
| Algorithm | Key Size | Signature Size | Speed | Security |
|-----------|----------|----------------|--------|----------|
| ECDSA     | Small    | Small          | Fast   | High     |
| RSA       | Large    | Large          | Slow   | High     |
| DSA       | Large    | Medium         | Medium | Good     |
| EdDSA     | Small    | Small          | Very Fast | High  |

## Use Cases

### Recommended Applications
- **Mobile applications**: Efficient cryptography for smartphones and tablets
- **IoT devices**: Low-power, resource-constrained environments
- **Blockchain**: Bitcoin, Ethereum, and other cryptocurrencies
- **TLS/SSL**: Modern web security protocols
- **Smart cards**: Limited processing power and memory
- **Embedded systems**: Automotive, industrial control systems

### Performance Benefits
- **Battery life**: Lower power consumption in mobile devices
- **Network efficiency**: Smaller certificates and signatures
- **Processing speed**: Faster operations than equivalent RSA
- **Memory usage**: Reduced storage requirements

## Troubleshooting

### Common Issues

1. **OpenSSL headers not found**
   ```
   Error: 'openssl/ec.h' file not found
   ```
   **Solution**: Install OpenSSL development libraries:
   ```bash
   brew install openssl
   ```

2. **Key files missing**
   ```
   Error: Cannot open ec_private.pem
   ```
   **Solution**: Generate keys first:
   ```bash
   make -f Makefile.key create
   ```

3. **Curve not supported**
   ```
   Error: Unknown curve name
   ```
   **Solution**: Use standard curves like secp256r1, secp384r1, or secp521r1.

4. **Invalid signature verification**
   ```
   Error: Signature verification failed
   ```
   **Solution**: Ensure message hasn't been modified and keys match.

### Performance Notes
- ECC is 5-10x faster than RSA for equivalent security
- Signature generation is faster than RSA signing
- Signature verification is much faster than RSA verification
- Key generation is significantly faster than RSA

## Historical Context

### Development Timeline
- **1985**: Elliptic curve cryptography independently proposed by Neal Koblitz and Victor Miller
- **1990s**: Mathematical foundations developed and security analyzed
- **2000s**: Standardization in NIST, ANSI, IEEE, and ISO standards
- **2010s**: Widespread adoption in modern cryptographic protocols

### Standardization
- **NIST**: Recommended elliptic curves (P-256, P-384, P-521)
- **SECG**: Additional curves and implementation guidelines
- **ANSI X9.62**: ECDSA standard for digital signatures
- **IEEE 1363**: Comprehensive elliptic curve standards

## Implementation Notes

### OpenSSL Integration
- Standard EVP interface for high-level operations
- Multiple curve support (prime fields, binary fields)
- Hardware acceleration when available
- Constant-time implementations for side-channel resistance

### Elliptic Curve Selection
- **secp256r1 (P-256)**: Most widely used, good balance of security/performance
- **secp384r1 (P-384)**: Higher security level, moderate performance
- **secp521r1 (P-521)**: Maximum security, slower performance
- **Curve25519**: Modern curve with excellent security properties

### Security Best Practices
- **Use standard curves**: Avoid custom or experimental curves
- **Proper randomness**: Ensure secure random number generation for k
- **Validate points**: Always validate public key points are on curve
- **Side-channel protection**: Use constant-time implementations
- **Key management**: Protect private keys with appropriate access controls

### Modern Developments
- **EdDSA**: Edwards curve digital signatures (Ed25519, Ed448)
- **X25519**: Curve25519 for key agreement
- **Post-quantum**: Preparing for quantum-resistant alternatives
- **Hardware support**: Increasing CPU support for ECC operations

```sh
make
./ecc_example
```

---

## 💡 Example Scenario

1. The program signs a message (`"Hello, ECC!"`) using the ECC private key.
2. It verifies the signature with the original message (should be valid).
3. It then attempts to verify the signature with a tampered message (`"Hello, ECC! (tampered)"`).
4. The result will be:

   ```
   Signature is valid!
   [Invalid case] Signature is invalid! (expected)
   ```

   because the signature does not match the modified message.

---

## 🛡️ Real-World Applications

- ECC is used for digital signatures, secure communications, and blockchain.
- If the data is changed, the digital signature will no longer be valid.
- Ensures data is not forged and is signed by the correct person.

---

## ⚠️ Notes

- Always generate the key pair before signing/verifying.
- You can change the message in the code to test different scenarios.
