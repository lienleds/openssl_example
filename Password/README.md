# Password Security Example

## Overview

This example demonstrates secure password handling best practices using OpenSSL's PBKDF2 implementation. It shows how to properly hash, store, and verify passwords in a way that's resistant to common attacks.

### Key Features
- **PBKDF2-SHA256**: Industry-standard password hashing
- **Unique salts**: Prevents rainbow table attacks
- **Configurable iterations**: Future-proof security scaling
- **Constant-time comparison**: Prevents timing attacks
- **Secure memory handling**: Proper cleanup of sensitive data

## Security Properties

### Algorithm Details
- **Hash Function**: PBKDF2 with SHA-256
- **Salt Size**: 256 bits (32 bytes)
- **Hash Output**: 256 bits (32 bytes)
- **Default Iterations**: 100,000 (OWASP 2023 minimum)
- **Time Target**: ~100ms on modern hardware

### Attack Resistance
- **Rainbow Tables**: Unique salts make precomputed attacks infeasible
- **Brute Force**: High iteration count slows down password cracking
- **Timing Attacks**: Constant-time comparison prevents information leakage
- **Dictionary Attacks**: Computational cost makes large-scale attacks expensive

## Code Structure

### SecurePassword Class
```cpp
class SecurePassword {
    static PasswordHash hashPassword(const std::string& password, int iterations);
    static bool verifyPassword(const std::string& password, const PasswordHash& stored);
    static std::vector<uint8_t> generateSalt();
};
```

### UserDatabase Class
Simulates a user authentication system demonstrating:
- User registration with secure password hashing
- Login verification with constant-time comparison
- Proper error handling without information leakage

## Build and Run

```bash
# Build the example
make

# Run the demonstration
make run

# Clean build files
make clean
```

## Example Output

The program demonstrates several security scenarios:

1. **User Registration**: Shows password hashing with unique salts
2. **Login Authentication**: Demonstrates correct and incorrect password handling
3. **Performance Testing**: Compares different iteration counts
4. **Security Features**: Shows salt uniqueness and hash differences

### Sample Session
```
=== Secure Password Handling Example ===
Using PBKDF2-SHA256 with 100000 iterations

--- User Registration ---
✅ User registered: alice
✅ User registered: bob
❌ User already exists: alice

--- User Info: alice ---
Salt (32 bytes): a1b2c3d4e5f6789a...
Hash (32 bytes): 9f8e7d6c5b4a3210...
Iterations: 100000

--- Login Attempts ---
✅ Login successful: alice
❌ Invalid password for: alice
✅ Login successful: bob
❌ User not found: charlie
```

## Security Best Practices Demonstrated

### 1. **Never Store Plaintext Passwords**
```cpp
// ❌ WRONG
string stored_password = "user123";

// ✅ CORRECT
PasswordHash hash = SecurePassword::hashPassword("user123");
```

### 2. **Use Cryptographically Secure Random Salts**
```cpp
std::vector<uint8_t> salt(SALT_LENGTH);
RAND_bytes(salt.data(), SALT_LENGTH);  // OpenSSL secure RNG
```

### 3. **Constant-Time Comparison**
```cpp
// Prevents timing attacks
return CRYPTO_memcmp(derived_hash.data(), stored.hash.data(), HASH_LENGTH) == 0;
```

### 4. **Configurable Cost Parameters**
```cpp
// Allow iteration count tuning for future hardware
static const int MIN_ITERATIONS = 100000;
auto hash = hashPassword(password, custom_iterations);
```

## Real-World Considerations

### **Production Deployment**
- **Monitor hash timing**: Adjust iterations to maintain ~100ms target
- **Implement rate limiting**: Prevent brute force attempts
- **Use secure memory**: Consider mlock() for sensitive data
- **Plan algorithm migration**: Design for future algorithm upgrades

### **Performance Tuning**
```cpp
// Measure on your target hardware
auto start = std::chrono::high_resolution_clock::now();
auto hash = SecurePassword::hashPassword(password, iterations);
auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::high_resolution_clock::now() - start);
```

### **Alternative Algorithms**
While this example uses PBKDF2 (widely available), consider:
- **Argon2id**: Winner of Password Hashing Competition (preferred for new systems)
- **bcrypt**: Time-tested alternative with wide library support
- **scrypt**: Memory-hard function for additional GPU resistance

## Security Warnings

### **❌ Common Mistakes to Avoid**
1. Using fast hash functions (SHA-256, MD5) directly
2. Reusing salts across different passwords
3. Insufficient iteration counts (< 100,000 for PBKDF2)
4. Storing passwords in reversible format
5. Client-side only password hashing

### **🔍 Additional Security Measures**
- Implement account lockout after failed attempts
- Use HTTPS for all authentication traffic
- Consider multi-factor authentication (MFA)
- Regular security audits and penetration testing
- Monitor for credential stuffing attacks

## Testing and Validation

### **Security Testing**
```bash
# Test with common passwords
./password_example

# Performance testing on your hardware
time ./password_example

# Memory leak checking (if valgrind available)
valgrind --leak-check=full ./password_example
```

### **Integration Testing**
- Test password verification with various inputs
- Verify unique salt generation
- Confirm constant-time behavior
- Validate error handling paths

## References

- **OWASP Password Storage Cheat Sheet**: Current best practices
- **RFC 2898**: PKCS #5 PBKDF2 specification
- **NIST SP 800-63B**: Digital Identity Guidelines
- **Password Hashing Competition**: Modern algorithm comparisons

## Files Description

- `password_example.cpp`: Complete demonstration of secure password handling
- `Makefile`: Build configuration with OpenSSL linking
- `README.md`: This documentation file

This example provides a solid foundation for implementing secure password storage in real applications while demonstrating the key security principles that protect user credentials.