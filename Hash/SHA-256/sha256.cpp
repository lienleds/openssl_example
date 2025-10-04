#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <cstring>

int main()
{
    const char* data = "Hello, SHA-256!";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Compute SHA-256 hash
    SHA256(reinterpret_cast<const unsigned char*>(data), strlen(data), hash);

    std::cout << "Input: " << data << std::endl;
    std::cout << "SHA256_DIGEST_LENGTH: " << SHA256_DIGEST_LENGTH << std::endl;
    std::cout << "SHA-256: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::endl;
    return 0;
}
