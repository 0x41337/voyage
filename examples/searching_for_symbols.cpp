#include <voyage.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    void *printf_ptr = nullptr;
    
    if (VE_FindSymbolAddress(nullptr, "printf", &printf_ptr) == VE_OK)
    {
        std::cout << "Printf() address: " << printf_ptr << '\n';
    }

    return 0;
}