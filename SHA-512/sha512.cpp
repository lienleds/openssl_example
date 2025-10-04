#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <cstring>

int main()
{
    const char* data = "Hello, SHA-512!";
    unsigned char hash[SHA512_DIGEST_LENGTH];

    // Compute SHA-512 hash
    SHA512(reinterpret_cast<const unsigned char*>(data), strlen(data), hash);

    std::cout << "Input: " << data << std::endl;
    std::cout << "SHA512_DIGEST_LENGTH: " << SHA512_DIGEST_LENGTH << std::endl;
    std::cout << "SHA-512: ";
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::endl;
    return 0;
}
