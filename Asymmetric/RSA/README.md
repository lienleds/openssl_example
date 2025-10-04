# 🚀 RSA Example with OpenSSL (C++)

This example demonstrates how to generate RSA key pairs and perform RSA encryption/decryption using OpenSSL in C++.

---

## 📂 Files

| File                | Description                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| `rsa_create_key.cpp`| Generates a 2048-bit RSA key pair and saves them to `private_key.pem` and `public_key.pem`. |
| `rsa_example.cpp`   | Loads the private key and demonstrates RSA encryption/decryption.            |
| `Makefile`          | Builds both programs (default target: `rsa_example`).                        |
| `Makefile.key`      | Builds only the key generation program (`rsa_create_key`).                   |

---

## 🛠️ How to Build and Run

### 1️⃣ Generate RSA Key Pair

```sh
make -f Makefile.key
./rsa_create_key
```
> This will create `private_key.pem` and `public_key.pem` in the current directory.

---

### 2️⃣ Build and Run RSA Encryption/Decryption Example

```sh
make
./rsa_example
```

---

## 📦 Requirements

- OpenSSL development libraries (`libssl-dev` or `openssl-devel`)
- `g++` compiler

---

## ⚡ Notes

- **Always generate the key pair before running the encryption/decryption example.**
- The example uses **OAEP padding** for enhanced security.

---
