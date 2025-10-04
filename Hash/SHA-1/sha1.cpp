#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <cstring>

int main()
{
    const char* data = "Hello, SHA-1!";
    unsigned char hash[SHA_DIGEST_LENGTH];

    // Compute SHA-1 hash
    SHA1(reinterpret_cast<const unsigned char*>(data), strlen(data), hash);

    std::cout << "Input: " << data << std::endl;
    std::cout << "SHA_DIGEST_LENGTH: " << SHA_DIGEST_LENGTH << std::endl;
    std::cout << "SHA-1: ";
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) 
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}
