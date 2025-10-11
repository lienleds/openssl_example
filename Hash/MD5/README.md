# MD5 Hash Example

This example demonstrates the MD5 cryptographic hash function using OpenSSL in C++.

## ⚠️ SECURITY WARNING

**MD5 IS CRYPTOGRAPHICALLY BROKEN AND SHOULD NOT BE USED FOR SECURITY PURPOSES.**

This example is provided for:
- **Educational purposes**: Understanding hash function concepts
- **Legacy system compatibility**: Working with existing MD5-based systems
- **Non-security applications**: Checksums where cryptographic security is not required

## Algorithm Details

### Basic Parameters
- **Hash size**: 128 bits (16 bytes)
- **Block size**: 512 bits (64 bytes)
- **Security level**: **BROKEN** - practical collision attacks exist
- **Standard**: RFC 1321 (1992)

### MD5 Operations
- **Message padding**: Ensures message length ≡ 448 (mod 512)
- **Message scheduling**: Processes 16 32-bit words per block
- **Compression function**: 64 rounds using 4 auxiliary functions
- **Output**: 128-bit hash value

## Files

- `md5.cpp` - Main hash computation demonstration (educational only)
- `note.txt` - Security warnings and migration guidance
- `Makefile` - Build configuration with macOS OpenSSL support
- `README.md` - This documentation file

## Building and Running

### Prerequisites
- macOS with Homebrew
- OpenSSL 3.x: `brew install openssl`
- C++ compiler with C++11 support
- **Legacy provider**: Required for MD5 in OpenSSL 3.x

### Step 1: Build
```bash
make
```

### Step 2: Run Example (Educational Only)
```bash
./md5
```

## Security Status

### Known Vulnerabilities
| Attack Type | Status | Impact |
|-------------|--------|---------|
| Collision attacks | **BROKEN** | Can create two different inputs with same hash |
| Chosen-prefix attacks | **BROKEN** | Can create collisions with chosen prefixes |
| Pre-image attacks | Weakened | Faster than brute force but not practical |
| Length extension | Vulnerable | Can extend messages without knowing content |

### Timeline of Breaks
- **1996**: First theoretical weaknesses discovered
- **2004**: Practical collision attack demonstrated (1 hour on cluster)
- **2005**: Collisions generated on single laptop
- **2008**: Chosen-prefix collision attacks
- **2009**: Rogue CA certificate created using MD5 collision

## Migration Recommendations

### Secure Alternatives
| Use Case | Recommended Algorithm | Reason |
|----------|----------------------|---------|
| General hashing | SHA-256 | Industry standard, secure |
| High performance | BLAKE2b | Faster than SHA-256, secure |
| Password hashing | bcrypt, scrypt, Argon2 | Designed for password security |
| HMAC | SHA-256 | Secure message authentication |
| Digital signatures | SHA-256 or SHA-512 | Required for signature security |

### Legacy System Handling
```cpp
// DO NOT USE for new applications
// Only for compatibility with existing systems
if (legacy_system_requires_md5) {
    // Use MD5 only for non-security checksums
    // Always validate with secure hash as well
    compute_md5_for_compatibility();
    compute_sha256_for_security();
}
```

## Educational Value

### Learning Objectives
- **Hash function concepts**: Basic cryptographic hash principles
- **Algorithm structure**: Merkle-Damgård construction
- **Security evolution**: How cryptographic standards evolve
- **Attack methodology**: Understanding collision attacks

### Historical Significance
- **Early Internet**: Widely used in 1990s and early 2000s
- **Cryptographic lessons**: Demonstrates importance of security margins
- **Standard evolution**: Led to development of SHA-2 family
- **Research impact**: Collision attacks advanced cryptanalysis field

## Troubleshooting

### Common Issues

1. **MD5 not available in OpenSSL 3.x**
   ```
   Error: Unknown message digest md5
   ```
   **Solution**: Load legacy provider:
   ```cpp
   OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
   ```

2. **Security warnings**
   ```
   Warning: MD5 is cryptographically broken
   ```
   **Response**: This is correct - only use for educational purposes.

3. **Compilation issues**
   ```
   Error: 'openssl/md5.h' not found
   ```
   **Solution**: Use EVP interface instead of deprecated MD5-specific functions.

### Modern OpenSSL Usage
```cpp
// Correct approach for educational/legacy use
EVP_MD_CTX *ctx = EVP_MD_CTX_new();
const EVP_MD *md = EVP_get_digestbyname("md5");
// Always check if md is NULL before using
```

## Real-World Impact

### Notable Incidents
- **2008 CA attack**: Rogue SSL certificate created using MD5 collision
- **Flame malware**: Used MD5 collision to forge Microsoft certificates  
- **Password databases**: Many breached databases used MD5 without salt
- **Legacy protocols**: Many older systems still vulnerable

### Current Status
- **Deprecated**: All major organizations recommend against MD5
- **Compliance**: Prohibited in government and financial applications
- **Browser warnings**: Modern browsers warn about MD5 certificates
- **Legacy burden**: Still found in older systems requiring updates

## Implementation Notes

### OpenSSL 3.x Considerations
- **Legacy provider required**: MD5 moved to legacy provider
- **Deprecation warnings**: Compiler may issue warnings
- **API changes**: Some MD5-specific functions deprecated
- **Migration tools**: OpenSSL provides tools for algorithm migration

### Safe Usage Patterns
```cpp
// ONLY acceptable for non-security checksums
void compute_file_checksum_md5(const char* filename) {
    // Add warning comment
    // This is NOT for security - checksums only
    // Consider SHA-256 for any security-related use
}
```

### Educational Context
- **Understand**: Why MD5 was designed and initially adopted
- **Learn**: How collision attacks work in practice
- **Appreciate**: Importance of cryptographic agility
- **Apply**: Lessons learned to evaluating current algorithms

**Remember**: This example demonstrates a broken algorithm. Never use MD5 for passwords, digital signatures, certificates, or any security-critical application. Always use SHA-256 or stronger alternatives for security purposes.