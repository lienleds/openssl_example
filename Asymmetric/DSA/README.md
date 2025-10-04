# DSA Digital Signature Example (C++ & OpenSSL)

This example demonstrates how to generate DSA keys, sign a message, and verify a digital signature using OpenSSL in C++.

---

## 📁 Files

- **dsa_create_key.cpp** — Generate a DSA key pair (`dsa_private.pem`, `dsa_public.pem`).
- **dsa_example.cpp** — Load the private key, sign a message, and verify the signature.
- **Makefile** — Build the signing/verifying program.
- **Makefile.key** — Build the key generation program.

---

## 🚀 Usage

### 1. Generate DSA Key Pair

```sh
make -f Makefile.key
./dsa_create_key
```
*This will create `dsa_private.pem` and `dsa_public.pem` in the current directory.*

### 2. Sign and Verify a Digital Signature

```sh
make
./dsa_example
```

---

## 💡 Example Scenario

1. The program signs a message (`"Hello, DSA!"`) using the DSA private key.
2. It then attempts to verify the signature with a tampered message (`"Hello, DSA! (tampered)"`).
3. The result will be:

	```
	Signature is invalid!
	```

	because the signature does not match the modified message.

---

## 🛡️ Real-World Applications

- DSA is used to verify the origin and integrity of data (emails, files, transactions, blockchain, etc.).
- If the data is changed, the digital signature will no longer be valid.
- Ensures data is not forged and is signed by the correct person.

---

## ⚠️ Notes

- Always generate the key pair before signing/verifying.
- You can change the message in the code to test different scenarios.
