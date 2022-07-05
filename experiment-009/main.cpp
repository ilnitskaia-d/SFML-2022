#include <cstdint>
#include <iostream>

int main()
{
    uint32_t flags = 3;
    flags <<= 2;
    std::cout << flags << std::endl;
}