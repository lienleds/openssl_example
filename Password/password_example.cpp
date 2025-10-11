/*
 * Secure Password Hashing Example
 * Demonstrates best practices for password storage and verification
 * Uses PBKDF2 with OpenSSL (widely available baseline)
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

class SecurePassword {
private:
    static const int SALT_LENGTH = 32;      // 256-bit salt
    static const int HASH_LENGTH = 32;      // 256-bit output
    static const int MIN_ITERATIONS = 100000; // OWASP 2023 minimum

public:
    struct PasswordHash {
        std::vector<uint8_t> salt;
        std::vector<uint8_t> hash;
        int iterations;
    };

    // Generate cryptographically secure salt
    static std::vector<uint8_t> generateSalt() {
        std::vector<uint8_t> salt(SALT_LENGTH);
        if (RAND_bytes(salt.data(), SALT_LENGTH) != 1) {
            throw std::runtime_error("Failed to generate secure random salt");
        }
        return salt;
    }

    // Hash password using PBKDF2-SHA256
    static PasswordHash hashPassword(const std::string& password, int iterations = MIN_ITERATIONS) {
        PasswordHash result;
        result.salt = generateSalt();
        result.hash.resize(HASH_LENGTH);
        result.iterations = iterations;

        // Use PBKDF2 with SHA-256
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                             result.salt.data(), result.salt.size(),
                             iterations, EVP_sha256(),
                             HASH_LENGTH, result.hash.data()) != 1) {
            throw std::runtime_error("Password hashing failed");
        }

        return result;
    }

    // Verify password against stored hash
    static bool verifyPassword(const std::string& password, const PasswordHash& stored) {
        // Derive hash from input password using same salt and iterations
        std::vector<uint8_t> derived_hash(HASH_LENGTH);
        
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                             stored.salt.data(), stored.salt.size(),
                             stored.iterations, EVP_sha256(),
                             HASH_LENGTH, derived_hash.data()) != 1) {
            return false;
        }

        // Use constant-time comparison to prevent timing attacks
        return CRYPTO_memcmp(derived_hash.data(), stored.hash.data(), HASH_LENGTH) == 0;
    }

    // Helper function to display hash in hex format
    static void printHash(const PasswordHash& hash) {
        std::cout << "Salt (" << hash.salt.size() << " bytes): ";
        for (size_t i = 0; i < std::min(hash.salt.size(), size_t(16)); ++i) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) 
                      << static_cast<int>(hash.salt[i]);
        }
        std::cout << "..." << std::endl;

        std::cout << "Hash (" << hash.hash.size() << " bytes): ";
        for (size_t i = 0; i < std::min(hash.hash.size(), size_t(16)); ++i) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) 
                      << static_cast<int>(hash.hash[i]);
        }
        std::cout << "..." << std::endl;
        
        std::cout << std::dec << "Iterations: " << hash.iterations << std::endl;
    }
};

// Simulate a simple user database
class UserDatabase {
private:
    struct User {
        std::string username;
        SecurePassword::PasswordHash password_hash;
    };
    std::vector<User> users;

public:
    // Register new user with secure password hashing
    bool registerUser(const std::string& username, const std::string& password) {
        // Check if user already exists
        for (const auto& user : users) {
            if (user.username == username) {
                std::cout << "❌ User already exists: " << username << std::endl;
                return false;
            }
        }

        try {
            // Hash the password securely
            auto hash = SecurePassword::hashPassword(password);
            users.push_back({username, hash});
            std::cout << "✅ User registered: " << username << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cout << "❌ Registration failed: " << e.what() << std::endl;
            return false;
        }
    }

    // Authenticate user
    bool login(const std::string& username, const std::string& password) {
        // Find user
        for (const auto& user : users) {
            if (user.username == username) {
                // Verify password using constant-time comparison
                if (SecurePassword::verifyPassword(password, user.password_hash)) {
                    std::cout << "✅ Login successful: " << username << std::endl;
                    return true;
                } else {
                    std::cout << "❌ Invalid password for: " << username << std::endl;
                    return false;
                }
            }
        }
        
        std::cout << "❌ User not found: " << username << std::endl;
        return false;
    }

    // Show stored password info (for educational purposes)
    void showUserInfo(const std::string& username) {
        for (const auto& user : users) {
            if (user.username == username) {
                std::cout << "\n--- User Info: " << username << " ---" << std::endl;
                SecurePassword::printHash(user.password_hash);
                return;
            }
        }
        std::cout << "User not found: " << username << std::endl;
    }
};

int main() {
    std::cout << "=== Secure Password Handling Example ===" << std::endl;
    std::cout << "Using PBKDF2-SHA256 with " << 100000 << " iterations" << std::endl;
    std::cout << "Salt: 256 bits | Hash: 256 bits" << std::endl << std::endl;

    UserDatabase db;

    // Example 1: User Registration
    std::cout << "--- User Registration ---" << std::endl;
    db.registerUser("alice", "SecurePassword123!");
    db.registerUser("bob", "MyStrongPass456@");
    db.registerUser("alice", "DuplicateUser");  // Should fail
    
    // Show stored password information
    db.showUserInfo("alice");

    // Example 2: Login Attempts
    std::cout << "\n--- Login Attempts ---" << std::endl;
    db.login("alice", "SecurePassword123!");    // Correct password
    db.login("alice", "WrongPassword");         // Wrong password
    db.login("bob", "MyStrongPass456@");        // Correct password
    db.login("charlie", "AnyPassword");         // Non-existent user

    // Example 3: Demonstrate Different Costs
    std::cout << "\n--- Performance Comparison ---" << std::endl;
    std::string test_password = "TestPassword123";
    
    auto start = std::chrono::high_resolution_clock::now();
    auto hash_100k = SecurePassword::hashPassword(test_password, 100000);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_100k = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    auto hash_200k = SecurePassword::hashPassword(test_password, 200000);
    end = std::chrono::high_resolution_clock::now();
    auto duration_200k = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "100K iterations: " << duration_100k.count() << "ms" << std::endl;
    std::cout << "200K iterations: " << duration_200k.count() << "ms" << std::endl;
    std::cout << "Note: Aim for ~100ms on your target hardware" << std::endl;

    // Example 4: Security Demonstrations
    std::cout << "\n--- Security Features ---" << std::endl;
    
    // Same password, different salts = different hashes
    auto hash1 = SecurePassword::hashPassword("SamePassword");
    auto hash2 = SecurePassword::hashPassword("SamePassword");
    
    std::cout << "Same password hashed twice:" << std::endl;
    std::cout << "Hash 1 (first 16 bytes): ";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) 
                  << static_cast<int>(hash1.hash[i]);
    }
    std::cout << std::endl;
    
    std::cout << "Hash 2 (first 16 bytes): ";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) 
                  << static_cast<int>(hash2.hash[i]);
    }
    std::cout << std::endl;
    std::cout << "✅ Different hashes due to unique salts" << std::endl;

    std::cout << "\n=== Key Security Principles Demonstrated ===" << std::endl;
    std::cout << "✅ Unique salt per password (prevents rainbow tables)" << std::endl;
    std::cout << "✅ High iteration count (slows down brute force)" << std::endl;
    std::cout << "✅ Constant-time comparison (prevents timing attacks)" << std::endl;
    std::cout << "✅ Cryptographically secure random salt generation" << std::endl;
    std::cout << "✅ No plaintext password storage" << std::endl;
    std::cout << "✅ Configurable cost parameter for future-proofing" << std::endl;

    return 0;
}