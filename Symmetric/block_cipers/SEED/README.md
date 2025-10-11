# SEED Encryption Example

This example demonstrates the SEED block cipher, a Korean cryptographic algorithm standardized as KISA-SEED-128 and later as ISO/IEC 18033-3.

## Overview

SEED (Secure and Efficient Encryption Device) is a 128-bit block cipher developed by the Korea Information Security Agency (KISA) in 1998. It was designed to replace DES in Korean government and financial applications and has achieved international recognition as ISO/IEC 18033-3.

## Algorithm Details

### Basic Parameters
- **Block size**: 128 bits (16 bytes)
- **Key size**: 128 bits (16 bytes) - fixed length
- **Structure**: 16-round Feistel network
- **Key schedule**: Generates 32 subkeys (2 per round)

### Cryptographic Design
- **Rounds**: 16 rounds of Feistel operations
- **S-boxes**: Two 8×8 S-boxes with optimal differential/linear properties
- **Round function**: F-function with G-function and key mixing
- **Key expansion**: Uses rotation and XOR with round constants

### Security Properties
- Resistant to differential cryptanalysis (max probability 2^-52)
- Resistant to linear cryptanalysis (max bias 2^-26)
- No known practical attacks against full 16-round SEED
- Suitable for long-term security applications

## Files

- `seed_example.cpp` - Main encryption/decryption demonstration
- `seed_create_key.cpp` - Key and IV generation utility  
- `Makefile` - Build script for main example
- `Makefile.key` - Build script for key generation
- `README.md` - This documentation file

## Building and Running

### Step 1: Generate Keys
```bash
make -f Makefile.key create
```

This creates:
- `seed_key.bin` - 128-bit SEED key
- `seed_iv.bin` - 128-bit initialization vector

### Step 2: Build and Run Example
```bash
make
./seed_example
```

### Save Output
```bash
./seed_example > out.txt
```

## Example Output Features

### Block Analysis
- Detailed breakdown of text into 16-byte blocks
- Visual representation of block boundaries
- Analysis of padding requirements

### PKCS#7 Padding Demonstration
- Shows exact bytes needing padding in the last block
- Explains padding value calculation and application
- Hex visualization of padding bytes

### CBC Mode Explanation
- Demonstrates cipher block chaining
- Shows IV usage and block interdependency
- Educational visualization of encryption flow

## Korean Cryptographic Heritage

### Development History
- **1998**: Developed by KISA (Korea Information Security Agency)
- **1999**: Adopted as Korean national standard KS X 1213
- **2005**: Became ISO/IEC 18033-3 international standard
- **Purpose**: Replace DES in Korean government and financial systems

### International Recognition
- First Korean-designed block cipher to achieve international standardization
- Included in TLS cipher suites (RFC 4162)
- Used in Korean e-government and financial applications
- Example of successful national cryptographic standard development

### Technical Innovation
- Demonstrates Korea's expertise in cryptographic algorithm design
- Balances security, efficiency, and implementation flexibility
- Reflects commitment to cryptographic sovereignty

## Algorithm Comparison

| Algorithm | Block Size | Key Size | Rounds | Structure | Origin |
|-----------|------------|----------|---------|-----------|---------|
| SEED      | 128 bits   | 128 bits | 16      | Feistel   | Korea (1998) |
| AES       | 128 bits   | 128/192/256 bits | 10/12/14 | SPN | USA (1998) |
| Camellia  | 128 bits   | 128/192/256 bits | 18/24 | Feistel | Japan (2000) |
| Blowfish  | 64 bits    | 32-448 bits | 16 | Feistel | USA (1993) |

## Security Applications

### Government Usage
- Korean government secure communications
- Financial transaction protection
- Digital signature applications
- Secure document storage

### Commercial Applications
- Banking and payment systems
- Secure network protocols (TLS/SSL)
- File encryption utilities
- Embedded security systems

## Technical Notes

### OpenSSL Requirements
- Requires legacy provider in OpenSSL 3.x
- Uses `EVP_seed_cbc()` for CBC mode operations
- Compatible with standard EVP interface

### Implementation Features
- Hardware-friendly design for efficient implementation
- Software-optimized round function operations
- Balanced approach to security and performance
- Suitable for both embedded and server applications

### Key Schedule Details
The SEED key schedule operates as follows:
1. 128-bit master key is expanded into 32 16-bit subkeys
2. Key expansion uses rotation operations and round constants
3. Two subkeys are used per round (Ki and Ki+1)
4. Round constants prevent related-key attacks

### Round Function (F-function)
Each round processes data through:
1. Key mixing with round subkeys
2. G-function operations using S-boxes
3. Linear transformation and bit rotations
4. XOR with round-specific values

## Troubleshooting

### Common Issues

1. **Legacy provider not loaded**
   ```
   Error: Failed to load legacy provider!
   ```
   Solution: Ensure OpenSSL 3.x is properly installed with legacy provider support.

2. **Key files missing**
   ```
   Error: Cannot open seed_key.bin or seed_iv.bin!
   ```
   Solution: Run `make -f Makefile.key create` to generate keys first.

3. **Compilation errors**
   ```
   Error: cannot find -lssl -lcrypto
   ```
   Solution: Install OpenSSL development packages:
   - Ubuntu/Debian: `sudo apt-get install libssl-dev`
   - macOS: `brew install openssl`
   - CentOS/RHEL: `sudo yum install openssl-devel`

### Performance Notes
- SEED is optimized for both software and hardware implementations
- 128-bit blocks provide good throughput for modern systems
- 16 rounds offer strong security with reasonable performance
- Fixed key length simplifies key management

## Educational Value

This example demonstrates:
- **Block cipher fundamentals**: Fixed-size block processing
- **Padding schemes**: PKCS#7 padding implementation
- **Chain modes**: CBC mode operation and IV usage
- **Korean cryptography**: National cryptographic standard development
- **International standards**: ISO/IEC standardization process
- **Security analysis**: Resistance to known cryptanalytic attacks

## Historical Context

SEED represents an important milestone in cryptographic history as one of the first successful national block cipher standards to achieve international recognition. Its development demonstrates how countries can create robust cryptographic standards that meet both domestic security needs and international interoperability requirements.

The algorithm's inclusion in international standards like TLS cipher suites validates its security and implementation quality, making it a valuable case study in cryptographic algorithm design and standardization processes.