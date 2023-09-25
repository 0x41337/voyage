#include <voyage.h>
#include <iostream>

// Simple function that adds x and y
int add(int x, int y) 
{ 
    return x + y;
}

// Function that will replace add() that subtracts x and y
int add_hook(int x, int y)
{ 
    return x - y;
}

int main(int argc, char const *argv[])
{
    // Create a struct to store the hook
    Hook hook;
    
    // Create the hook for the add() function and its hook must be add_hook() the hook must be stored in hook
    VE_STATUS status = VE_CreateHook(reinterpret_cast<void*>(&add), reinterpret_cast<void*>(&add_hook), &hook);
    
    // Check if the hook was created successfully and call the add() function
    if (status == VE_OK)
    {   
        std::cout << "The add(1, 1) result is: " << add(1, 1) << '\n'; // 0
    } 

    return 0;
}
