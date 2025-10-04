# Diffie-Hellman Key Exchange Example (C++ & OpenSSL)

This example demonstrates how to generate Diffie-Hellman (DH) parameters, save/load keys, and perform a key exchange using OpenSSL in C++.

---

## 📁 Files

- **dh_create_key.cpp** — Generate DH parameters and keys, save to `dh_private.pem` and `dh_public.pem`.
- **dh_example.cpp** — Load DH parameters, simulate two parties exchanging public keys, and compute the shared secret.
- **Makefile** — Build the key exchange program.
- **Makefile.key** — Build the key generation program.

---

## 🚀 Usage

### 1. Generate DH Parameters and Keys

```sh
make -f Makefile.key
./dh_create_key
```
*This will create `dh_private.pem` and `dh_public.pem` in the current directory.*

### 2. Perform Key Exchange

```sh
make
./dh_example
```

---


## 💡 Example Scenario

1. `dh_create_key.cpp` generates DH parameters and keys, saving them to files.
2. `dh_example.cpp` loads the DH parameters from file, simulates two parties (dh1 and dh2) generating their own key pairs.
3. Each party exchanges their public key and computes the shared secret using the other party's public key.
4. If the protocol is correct, both parties derive the same shared secret, which can be used for secure communication.

---


## 📊 Sequence Diagram

Below is a sequence diagram illustrating the Diffie-Hellman key exchange process in this example:

```
Party1                Party2
  |                     |
  |-- Load DH params -->|   (Read parameters p, g from file)
  |-- Generate keypair -|   (Generate private & public key)
  |<-- Generate keypair-|   (Both parties generate keys)
  |-- Send public key -->|
  |<-- Send public key --|
  |-- Compute shared ----|
  |   secret using      |
  |   other's pubkey    |
  |<-- Compute shared --|
  |   secret using      |
  |   other's pubkey    |
  |                     |
  |-- Compare shared -->|   (If equal: success)
  |                     |
```

> **Notes:**
> - Both parties use the same parameters (p, g).
> - Each party generates its own private key.
> - Only public keys are exchanged, private keys are never sent.
> - The shared secret can only be computed with your own private key and the other party's public key.

---

## 🛡️ Real-World Applications

- Diffie-Hellman is used for secure key exchange in protocols like TLS/SSL, SSH, VPNs, and more.
- The shared secret is never transmitted; it is computed independently by both parties.
- Ensures that even if someone intercepts the public keys, they cannot compute the shared secret without the private keys.

---

## ⚠️ Notes

- Always generate DH parameters before running the key exchange example.
- This example is for educational purposes and does not include all security best practices for production use.
