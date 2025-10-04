#include <openssl/md5.h>
#include <iostream>
#include <iomanip>
#include <cstring>

int main()
{
    const char* data = "Hello, MD5!";
    unsigned char hash[MD5_DIGEST_LENGTH];

    // Compute MD5 hash
    MD5(reinterpret_cast<const unsigned char*>(data), strlen(data), hash);

    std::cout << "Input: " << data << std::endl;
    std::cout << "MD5_DIGEST_LENGTH: " << MD5_DIGEST_LENGTH << std::endl;
    std::cout << "MD5: ";
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::endl;
    return 0;
}
