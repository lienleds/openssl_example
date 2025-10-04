---

## 🔍 ECC vs DSA

| Feature         | ECC (ECDSA)                                   | DSA (Digital Signature Algorithm)         |
|-----------------|-----------------------------------------------|-------------------------------------------|
| Security        | High, modern, strong with short keys           | Good, but needs longer keys for same level|
| Key Size        | Short (e.g. 256-bit ≈ DSA 3072-bit)            | Long (2048/3072-bit for strong security)  |
| Performance     | Fast sign & verify, efficient for all devices  | Fast sign, slower verify                  |
| Resource Usage  | Low (good for mobile, IoT, embedded)           | Higher (needs more memory & CPU)          |
| Usage           | Modern apps, blockchain, TLS/SSL, SSH, etc.    | Legacy systems, older standards           |
| Recommendation  | Preferred for new systems                      | Not recommended for new systems           |

**Summary:** ECC/ECDSA is more secure, efficient, and future-proof than DSA. Use ECC/ECDSA for new digital signature applications.
# ECC Digital Signature Example (C++ & OpenSSL)

This example demonstrates how to generate ECC (Elliptic Curve Cryptography) keys, sign a message, and verify a digital signature using OpenSSL in C++.

---

## 📁 Files

- **ecc_create_key.cpp** — Generate an ECC key pair (`ec_private.pem`, `ec_public.pem`).
- **ecc_example.cpp** — Load the private key, sign a message, and verify the signature (including a valid and an invalid case).
- **Makefile** — Build the signing/verifying program.
- **Makefile.key** — Build the key generation program.

---

## 🚀 Usage

### 1. Generate ECC Key Pair

```sh
make -f Makefile.key
./ecc_create_key
```
*This will create `ec_private.pem` and `ec_public.pem` in the current directory.*

### 2. Sign and Verify a Digital Signature

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
