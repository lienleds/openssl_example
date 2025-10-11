# SHA-1 Hash Example

This example demonstrates the SHA-1 cryptographic hash function using OpenSSL in C++.

## ⚠️ SECURITY WARNING

**SHA-1 IS CRYPTOGRAPHICALLY DEPRECATED AND SHOULD NOT BE USED FOR NEW SECURITY APPLICATIONS.**

This example is provided for:
- **Educational purposes**: Understanding hash function evolution
- **Legacy system compatibility**: Working with existing SHA-1-based systems  
- **Migration planning**: Understanding systems that need to be upgraded

## Algorithm Details

### Basic Parameters
- **Hash size**: 160 bits (20 bytes)
- **Block size**: 512 bits (64 bytes)
- **Security level**: **DEPRECATED** - collision attacks demonstrated
- **Standard**: FIPS 180-4 (deprecated), RFC 3174

### SHA-1 Operations
- **Message padding**: Ensures message length ≡ 448 (mod 512)
- **Message scheduling**: Expands 16 words to 80 words per block
- **Compression function**: 80 rounds using 4 different functions
- **Output**: 160-bit hash value

## Files

- `sha1.cpp` - Main hash computation demonstration (educational/legacy only)
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

### Step 2: Run Example (Legacy/Educational Only)
```bash
./sha1
```

### Save Output
```bash
./sha1 > out.txt
```

## Security Status

### Vulnerability Timeline
| Year | Development | Impact |
|------|-------------|---------|
| 2005 | Theoretical collision attack (2^69 operations) | Security concerns raised |
| 2015 | Freestart collision attack | Practical weaknesses shown |
| 2017 | **SHAttered attack** - Full collision | Complete cryptographic break |
| 2019 | Chosen-prefix collision attack | Certificate forgery possible |

### Attack Implications
- **Collision attacks**: Can create two different documents with same SHA-1 hash
- **Certificate forgery**: Possible to create rogue SSL certificates
- **Digital signature bypass**: Can forge signatures in some implementations
- **Git vulnerability**: Potential for malicious commit injection

## Migration Recommendations

### Immediate Actions Required
| System Type | Action | Timeline |
|-------------|--------|----------|
| **SSL/TLS Certificates** | Migrate to SHA-256 | **URGENT - Already required** |
| **Code signing** | Use SHA-256 or SHA-512 | **URGENT** |
| **Git repositories** | Enable SHA-256 support | **Recommended** |
| **Digital signatures** | Upgrade to SHA-256 | **CRITICAL** |
| **Password hashing** | Use bcrypt/scrypt/Argon2 | **CRITICAL** |

### Secure Alternatives
```cpp
// REPLACE SHA-1 with these alternatives:

// For general hashing:
use_sha256_instead_of_sha1();

// For high-performance applications:
use_blake2b_for_speed();

// For digital signatures:
use_sha256_with_rsa_or_ecdsa();

// For password hashing:
use_bcrypt_scrypt_or_argon2();
```

## Legacy System Assessment

### Identifying SHA-1 Usage
```bash
# Check SSL certificates
openssl x509 -in certificate.crt -text -noout | grep "Signature Algorithm"

# Check code signing
codesign -d -v /path/to/application

# Check git repository
git log --format="%H %s" | head -5  # Look for 40-character hashes
```

### Migration Strategies
1. **Gradual transition**: Support both algorithms during transition
2. **Dual hashing**: Calculate both SHA-1 (compatibility) and SHA-256 (security)
3. **Protocol upgrade**: Update systems to support newer hash algorithms
4. **Certificate renewal**: Replace all SHA-1 certificates immediately

## Educational Value

### Historical Importance
- **NSA design**: Originally designed by NSA in 1995
- **Widespread adoption**: Became ubiquitous in 2000s internet security
- **Security research**: Collision attacks advanced cryptanalysis field
- **Lessons learned**: Importance of cryptographic agility and migration planning

### Understanding Attacks
- **Differential cryptanalysis**: How mathematical weaknesses are exploited
- **Birthday paradox**: Why collision resistance is limited to n/2 bits
- **Practical impact**: Real-world consequences of cryptographic breaks
- **Research timeline**: How academic research leads to practical attacks

## Troubleshooting

### Common Issues

1. **SHA-1 certificates rejected**
   ```
   Error: Certificate uses deprecated SHA-1 signature
   ```
   **Solution**: Obtain new certificate with SHA-256 or higher.

2. **Browser warnings**
   ```
   Warning: This site uses outdated security
   ```
   **Solution**: Upgrade server certificates to SHA-256.

3. **Git compatibility issues**
   ```
   Error: SHA-1 hash collision detected
   ```
   **Solution**: Migrate repository to SHA-256 object format.

### OpenSSL 3.x Considerations
- SHA-1 still available in default provider
- No deprecated warnings (yet) but strongly discouraged
- May be moved to legacy provider in future versions
- Use EVP interface for forward compatibility

## Real-World Impact

### Major Incidents
- **Google SHAttered (2017)**: Demonstrated practical SHA-1 collision
- **Browser deprecation**: All major browsers reject SHA-1 certificates
- **Certificate authorities**: Stopped issuing SHA-1 certificates in 2016
- **Git vulnerability**: Potential for repository poisoning attacks

### Industry Response
- **Immediate bans**: CAs prohibited from issuing SHA-1 certificates
- **Browser updates**: Automatic warnings and blocks implemented
- **Standard updates**: All security standards updated to require SHA-256+
- **Compliance requirements**: Regulations now mandate stronger algorithms

## Current Recommendations

### For Developers
```cpp
// DO NOT USE for any security purpose
if (absolutely_must_support_legacy_sha1) {
    // Only for compatibility with existing systems
    // Always validate with SHA-256 as well
    compute_sha1_for_compatibility();
    compute_sha256_for_actual_security();
    
    // Log security warning
    log_security_warning("SHA-1 used for legacy compatibility only");
}
```

### Migration Checklist
- [ ] Inventory all SHA-1 usage in your systems
- [ ] Prioritize cryptographic applications (certificates, signatures)
- [ ] Update configuration files and security policies
- [ ] Test compatibility with SHA-256 alternatives
- [ ] Plan gradual rollout with fallback procedures
- [ ] Monitor for SHA-1 usage in logs and alerts

**Critical**: SHA-1 must not be used for any new security applications. Existing SHA-1 usage should be migrated to SHA-256 or stronger algorithms as quickly as possible. This example is provided only for educational purposes and legacy system compatibility analysis.