/*
  Voyage A library for creating and managing hooks for unix systems authored by Gabriel.
  <https://github.com/0x41337/voyage>     <041337@proton.me>

  Voyage is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Voyage is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

/// @brief Represents a hook
struct Hook
{
    void *target;
    unsigned char original_instructions[5];
    bool enabled;
};

/// @brief All API status codes
typedef enum VE_STATUS
{
    VE_UNKNOWN = -1,
    VE_OK = 0,
    VE_ERROR_ALREADY_CREATED,
    VE_ERROR_NOT_CREATED,
    VE_ERROR_ENABLED,
    VE_ERROR_DISABLED,
    VE_ERROR_MEMORY_PROTECT,
    VE_ERROR_ALLOCATE_MEMORY,
    VE_ERROR_MODULE_NOT_FOUND,
    VE_ERROR_SYMBOL_NOT_FOUND,
} VE_STATUS;

// Constants
#define VE_VERSION 0.2;
#define VE_ALL_HOOKS nullptr;

/// @brief Search by symbol address
/// @param img_name Image/module name
/// @param sym_name Symbol name
/// @param dest Destination that will receive the found address
/// @return `VE_STATUS` can be [`VE_ERROR_MODULE_NOT_FOUND`, `VE_ERROR_SYMBOL_NOT_FOUND` and `VE_OK`]
VE_STATUS VE_FindSymbolAddress(const char *img_name, const char *sym_name, void *dest);

/// @brief Create a hook
/// @param target_address Address to the target
/// @param hook_address Address to the hook
/// @param original_function  Pointer to original function
/// @return `VE_STATUS` can be [`VE_ERROR_ALREADY_CREATED`, `VE_ERROR_NOT_CREATED`, `VE_ERROR_MEMORY_PROTECT` and `VE_OK`]
VE_STATUS VE_CreateHook(void *target_address, void *hook_address, Hook *dest);


/// @brief Remove a hook completely
/// @param hook The strutct that represents the hook
/// @return `VE_STATUS` can be [`VE_ERROR_MEMORY_PROTECT` and `VE_OK`]
VE_STATUS VE_RemoveHook(Hook* hook);
