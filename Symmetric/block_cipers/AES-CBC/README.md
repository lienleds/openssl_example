# AES-CBC Block Cipher Example

This example demonstrates AES (Advanced Encryption Standard) in CBC (Cipher Block Chaining) mode using OpenSSL in C++.

## Overview

AES is the most widely used symmetric encryption algorithm, standardized by NIST in 2001. It replaced DES and 3DES as the standard for government and commercial applications worldwide.

## Algorithm Details

### Basic Parameters
- **Block size**: 128 bits (16 bytes) - fixed for all AES variants
- **Key sizes**: 128, 192, or 256 bits (AES-128, AES-192, AES-256)
- **Rounds**: 10 (AES-128), 12 (AES-192), 14 (AES-256)
- **Structure**: Substitution-Permutation Network (SPN)

### AES Operations
- **SubBytes**: Byte substitution using S-box
- **ShiftRows**: Cyclical shift of row bytes
- **MixColumns**: Linear transformation of columns
- **AddRoundKey**: XOR with round key

### CBC Mode Features
- **Chaining**: Each plaintext block is XORed with previous ciphertext block
- **IV requirement**: Initialization Vector needed for first block
- **Sequential processing**: Cannot parallelize encryption (but can parallelize decryption)
- **Error propagation**: Single bit error affects current and next block

## Files

- `aes_cbc.cpp` - Main AES-CBC encryption/decryption demonstration
- `aes_create_key.cpp` - Key and IV generation utility
- `aes_key.bin` - Generated AES key (128, 192, or 256 bits)
- `aes_iv.bin` - Generated initialization vector (128 bits)
- `Makefile` - Build configuration for main example
- `Makefile.key` - Build configuration for key generation
- `out.txt` - Example output from running the program
- `README.md` - This documentation file

## Building and Running

### Prerequisites
- macOS with Homebrew
- OpenSSL 3.x: `brew install openssl`
- C++ compiler with C++11 support

### Step 1: Generate AES Key and IV
```bash
make -f Makefile.key create
```
This creates:
- `aes_key.bin` - AES encryption key
- `aes_iv.bin` - CBC mode initialization vector

### Step 2: Build and Run Example
```bash
make
./aes_cbc
```

### Save Output
```bash
./aes_cbc > out.txt
```

## Example Output Features

### Key and IV Display
- Hexadecimal key representation
- IV values and usage explanation
- Key size verification

### Encryption Process
- Plaintext block breakdown
- CBC chaining visualization
- Ciphertext generation
- PKCS#7 padding demonstration

### Decryption Verification
- Ciphertext processing
- Padding removal
- Original plaintext recovery

## AES Security Levels

### Key Size Comparison
| AES Variant | Key Size | Rounds | Security Level | Quantum Security |
|-------------|----------|--------|----------------|------------------|
| AES-128     | 128 bits | 10     | 128 bits      | ~64 bits         |
| AES-192     | 192 bits | 12     | 192 bits      | ~96 bits         |
| AES-256     | 256 bits | 14     | 256 bits      | ~128 bits        |

### Mode Comparison
| Mode | Parallelization | Random Access | IV/Nonce | Padding |
|------|----------------|---------------|----------|---------|
| CBC  | Decrypt only   | No            | IV       | Required |
| CTR  | Both           | Yes           | Nonce    | No       |
| GCM  | Both           | Yes           | Nonce    | No       |
| ECB  | Both           | Yes           | None     | Required |

## Use Cases

### Recommended Applications
- **File encryption**: Secure storage of sensitive documents
- **Database encryption**: Protecting stored data
- **VPN protocols**: Secure network tunneling
- **Legacy system compatibility**: CBC widely supported
- **Regulatory compliance**: FIPS 140-2 approved algorithm

### CBC Mode Advantages
- **Wide support**: Available in all cryptographic libraries
- **Proven security**: Decades of analysis and real-world use
- **Deterministic**: Same plaintext produces different ciphertext with different IV
- **Error recovery**: Single block errors don't cascade indefinitely

### CBC Mode Limitations
- **Sequential encryption**: Cannot parallelize encryption process
- **Padding oracle attacks**: Vulnerable if padding validation errors leak information
- **IV requirements**: Must use unique, unpredictable IVs
- **Performance**: Slower than parallelizable modes like CTR

## Security Considerations

### Initialization Vector (IV) Requirements
- **Uniqueness**: Never reuse IV with same key
- **Unpredictability**: IV should be cryptographically random
- **Size**: Must be exactly one block size (128 bits for AES)
- **Transmission**: IV can be sent in plaintext with ciphertext

### Padding Oracle Attacks
- **Vulnerability**: Occurs when padding validation errors are distinguishable
- **Mitigation**: Use authenticated encryption (AES-GCM) or constant-time padding validation
- **Detection**: Monitor for timing differences in decryption failures
- **Prevention**: Implement proper error handling

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

2. **Key files missing**
   ```
   Error: Cannot open aes_key.bin
   ```
   **Solution**: Generate keys first:
   ```bash
   make -f Makefile.key create
   ```

3. **Padding errors**
   ```
   Error: bad decrypt
   ```
   **Solution**: Verify ciphertext hasn't been corrupted and correct key/IV are used.

4. **IV reuse**
   ```
   Warning: Same IV used multiple times
   ```
   **Solution**: Generate new IV for each encryption operation.

### Performance Optimization
- AES-NI instructions provide hardware acceleration on modern CPUs
- Use AES-GCM for better performance and built-in authentication
- Consider key caching for multiple operations with same key
- Profile different AES modes for specific use cases

## Historical Context

### Development Timeline
- **1997**: AES competition announced by NIST
- **2000**: Rijndael selected as AES winner
- **2001**: AES standardized as FIPS 197
- **2005**: AES-256 approved for TOP SECRET information by NSA

### Design Philosophy
- **Simplicity**: Clean, understandable algorithm structure
- **Efficiency**: Fast implementation in both software and hardware
- **Security**: Resistant to all known cryptanalytic attacks
- **Flexibility**: Supports multiple key sizes

## Implementation Notes

### OpenSSL Integration
- Available in default provider
- Full EVP interface support
- Hardware acceleration when available
- Multiple mode support (CBC, CTR, GCM, etc.)

### Performance Characteristics
- **Hardware acceleration**: Up to 10x speedup with AES-NI
- **Software implementation**: Still very fast on modern CPUs
- **Memory usage**: Minimal state required
- **Scalability**: Suitable from embedded systems to data centers

### Best Practices
- **Use AES-256**: Provides best security margin
- **Prefer authenticated modes**: GCM or CCM over CBC when possible
- **Secure key management**: Protect keys with appropriate access controls
- **IV generation**: Use cryptographically secure random number generator
- **Constant-time implementation**: Prevent side-channel attacks
