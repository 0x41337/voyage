# 😁 Quick start

Now that you understand how hooks work, let's see a little about the API and how it works.

Creating a simple hook

{% code lineNumbers="true" %}
```cpp
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
```
{% endcode %}

In this example we create a hook in the sum function called "Add()", it receives two integers and returns their sum. In our Hook we receive the integers and do subtraction. When Add() is called our hook function is called instead doing a subtraction instead of addition.

So, if I want to disable this hook? to disable this hook we can use " VE\_Disablehook"

{% code lineNumbers="true" %}
```cpp
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
    
    // Disable the function hook by restoring its behavior
    status = VE_Disablehook(&hook);
    
    // Verify that the hook was successfully disabled
    if (status == VE_OK)
    {
        std::cout << "The add(1, 1) result is: " << add(1, 1) << '\n'; // 2
    }

    return 0;
}
```
{% endcode %}

As you can see the hook was disabled with **VE\_Disablehook** you can pass the hook which is a structure that represents the hook so the hook can be disabled and the function is restored.

Nice. With this, you can do some things, but what about enabling the hook again? We can use **VE\_EnableHook** to enable the hook again.

{% code lineNumbers="true" %}
```cpp
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
    
    // Disable the function hook by restoring its behavior
    status = VE_Disablehook(&hook);
    
    // Verify that the hook was successfully disabled
    if (status == VE_OK)
    {
        std::cout << "The add(1, 1) result is: " << add(1, 1) << '\n'; // 2
    }
    
    // Re-enable the hook
    status = VE_EnableHook(&hook);
    
    // Verify that the hook was successfully enabled
    if (status == VE_OK)
    {   
        std::cout << "The add(1, 1) result is: " << add(1, 1) << '\n'; // 0
    } 

    return 0;
}
```
{% endcode %}

With this you can create hooks, enable and disable them. It is important to note that the **VE\_CreateHook** function already creates an enabled hook. So you don't need to use **VE\_EnableHook** for it to work.

Now to finish, let's see how to delete the hooks using **VE\_RemoveHook**.

{% code lineNumbers="true" %}
```cpp
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
    
    // Disable the function hook by restoring its behavior
    status = VE_Disablehook(&hook);
    
    // Verify that the hook was successfully disabled
    if (status == VE_OK)
    {
        std::cout << "The add(1, 1) result is: " << add(1, 1) << '\n'; // 2
    }
    
    // Re-enable the hook
    status = VE_EnableHook(&hook);
    
    // Verify that the hook was successfully enabled
    if (status == VE_OK)
    {   
        std::cout << "The add(1, 1) result is: " << add(1, 1) << '\n'; // 0
    }
    
    // Remove the hook
    status = VE_RemoveHook(&hook);
    
    // Verify that the hook was successfully removed
    if (status == VE_OK)
    {
        std::cout << "The add(1, 1) result is: " << add(1, 1) << '\n'; // 2
    }
    
    return 0;
}
```
{% endcode %}
