#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <cstring>

int main()
{
    const char* data = "Hello, SHA-224!";
    unsigned char hash[SHA224_DIGEST_LENGTH];

    // Compute SHA-224 hash
    SHA224(reinterpret_cast<const unsigned char*>(data), strlen(data), hash);

    std::cout << "Input: " << data << std::endl;
    std::cout << "SHA224_DIGEST_LENGTH: " << SHA224_DIGEST_LENGTH << std::endl;
    std::cout << "SHA-224: ";
    for (int i = 0; i < SHA224_DIGEST_LENGTH; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::endl;
    return 0;
}
