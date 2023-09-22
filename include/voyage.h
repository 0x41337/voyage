/*
  Voyage A library for creating and managing hooks for unix systems authored by Gabriel.
  <https://github.com/0x41337/Voyage>     <041337@proton.me>

  Voyage is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either VEersion 3 of the License, or
  (at your option) any later VEersion.

  Voyage is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without eVEen the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should haVEe receiVEed a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <stdint.h>

// All API status codes
typedef enum VE_STATUS
{
    VE_UNKNOWN = -1,
    VE_OK = 0,
    VE_ERROR_ALREADY_CREATED,
    VE_ERROR_NOT_CREATED,
    VE_ERROR_ENABLED,
    VE_ERROR_DISABLED,
    VE_ERROR_NOT_EXECUTABLE,
    VE_ERROR_UNSUPPORTED_FUNCTION,
    VE_ERROR_MEMORY_ALLOC,
    VE_ERROR_MEMORY_PROTECT,
    VE_ERROR_MODULE_NOT_FOUND,
    VE_ERROR_SYMBOL_NOT_FOUND,
    VE_ERROR_FUNCTION_NOT_FOUND
} VE_STATUS;

// Types definitions
typedef uintptr_t addr_t;
typedef uint32_t addr32_t;
typedef uint64_t addr64_t;

typedef void *dummy_func_t;

// Constants
#define VE_VERSION  0.1;
#define VE_ALL_HOOKS nullptr;

/// @brief Search by symbol address
/// @param img_name Image/module name
/// @param sym_name Symbol name
/// @param dest Destination that will receive the found address
/// @return `VE_STATUS` can be [`VE_ERROR_MODULE_NOT_FOUND`, `VE_ERROR_SYMBOL_NOT_FOUND` and `VE_OK`]
VE_STATUS VE_FindSymbolAddress(const char* img_name, const char* sym_name, void* dest);


/// @brief Create a hook 
/// @param address The address of function
/// @param hook_function The detour function 
/// @param original_function  Pointer to original function
/// @return `VE_STATUS` can be [`VE_ERROR_ALREADY_CREATED`, `VE_ERROR_NOT_CREATED` and `VE_OK`]
VE_STATUS VE_CreateHook(void* address, dummy_func_t hook_func, dummy_func_t *original_function);
