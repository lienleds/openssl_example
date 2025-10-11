# BLAKE2s256 Hash Example

This example demonstrates the BLAKE2s256 cryptographic hash function using OpenSSL in C++.

## Overview

BLAKE2s256 is a high-performance cryptographic hash function from the BLAKE2 family, optimized for 8- to 32-bit platforms and embedded systems.

## Algorithm Details

### Basic Parameters
- **Hash size**: 256 bits (32 bytes)
- **Block size**: 512 bits (64 bytes)
- **Algorithm family**: BLAKE2s (optimized for 32-bit platforms)
- **Security level**: 128 bits (collision resistance)

### Key Features
- **Performance**: Optimized for smaller word sizes and embedded systems
- **Security**: Provides strong cryptographic security guarantees
- **Efficiency**: Lower memory usage than BLAKE2b
- **Portability**: Better performance on 32-bit and ARM processors

## Files

- `blake2s256_example.cpp` - Main hash computation demonstration
- `test.txt` - Sample input file for hashing
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

### Step 2: Run Example
```bash
./blake2s256_example test.txt
```

### Save Output
```bash
./blake2s256_example test.txt > out.txt
```

## Algorithm Comparison

| Algorithm | Hash Size | Block Size | Target Platform | Performance |
|-----------|-----------|------------|-----------------|-------------|
| BLAKE2s256| 256 bits  | 512 bits   | 32-bit/ARM     | Very High   |
| BLAKE2b512| 512 bits  | 1024 bits  | 64-bit         | Very High   |
| SHA-256   | 256 bits  | 512 bits   | General        | High        |
| SHA3-256  | 256 bits  | 1088 bits  | General        | Medium      |

## Use Cases

### Recommended Applications
- **Embedded systems**: Optimized for resource-constrained environments
- **Mobile applications**: Efficient hashing for ARM processors
- **IoT devices**: Low memory and power consumption
- **32-bit systems**: Better performance than 64-bit optimized algorithms
- **Real-time systems**: Predictable performance characteristics

### Platform Optimization
- Designed for 32-bit word operations
- Efficient on ARM Cortex processors
- Reduced memory footprint
- Cache-friendly for smaller systems

## Security Properties

### Cryptographic Strength
- **128-bit security level**: Equivalent to AES-128
- **Pre-image resistance**: Computationally infeasible to reverse
- **Collision resistance**: Extremely difficult to find hash collisions
- **Second pre-image resistance**: Hard to find alternative inputs

### Modern Security
- No known cryptographic vulnerabilities
- Resistant to length extension attacks
- Suitable for security-critical applications
- Extensive cryptanalysis performed

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

2. **Compilation errors on macOS**
   ```
   Error: cannot find -lssl -lcrypto
   ```
   **Solution**: Use provided Makefile with correct OpenSSL paths.

3. **Legacy provider errors**
   ```
   Error: BLAKE2s not available
   ```
   **Solution**: BLAKE2s is in default provider, ensure OpenSSL 3.x is installed.

### Performance Characteristics
- Faster than SHA-256 on 32-bit platforms
- Lower memory usage than BLAKE2b
- Suitable for battery-powered devices
- Consistent performance across different architectures

## Historical Context

### Design Philosophy
- **2012**: BLAKE2s developed alongside BLAKE2b
- **Target**: Fill gap between high-performance and embedded systems
- **Optimization**: Specifically designed for 32-bit and smaller platforms
- **Adoption**: Popular in embedded and mobile cryptography

### Technical Innovation
- Adapted ChaCha cipher round function for 32-bit efficiency
- Optimized constants and operations for smaller word sizes
- Maintained security properties of larger BLAKE2b variant
- Demonstrated that high security doesn't require large operations

## Implementation Notes

### OpenSSL Integration
- Available in default provider (OpenSSL 3.x)
- Standard EVP interface compatibility
- No special configuration required
- Cross-platform support

### Performance Tuning
- Vectorization support on supported platforms
- Compiler optimization friendly
- Minimal branching for consistent timing
- Suitable for side-channel resistant implementations
