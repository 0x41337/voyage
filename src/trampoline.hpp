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
#include <unistd.h>
#include <memory.h>
#include <inttypes.h>
#include <sys/mman.h>

#include <voyage.h>

/// @brief Removes target address memory protection
/// @param target_address  Address to the target
/// @return VE_STATUS can be [VE_ERROR_MEMORY_PROTECT and VE_OK]
VE_STATUS Remove_memory_protection(void *target_address)
{
    if (mprotect(reinterpret_cast<void *>((uintptr_t)target_address & ~(sysconf(_SC_PAGE_SIZE) - 1)), sysconf(_SC_PAGE_SIZE), PROT_READ | PROT_WRITE | PROT_EXEC) == -1)
        return VE_ERROR_MEMORY_PROTECT;

    return VE_OK;
}

/// @brief Restores target address memory protection
/// @param target_address Address to the target
/// @return VE_STATUS can be [VE_ERROR_MEMORY_PROTECT and VE_OK]
VE_STATUS Restore_memory_protection(void *target_address)
{
    if (mprotect(reinterpret_cast<void *>((uintptr_t)target_address & ~(sysconf(_SC_PAGE_SIZE) - 1)), sysconf(_SC_PAGE_SIZE), PROT_READ | PROT_EXEC) == -1)
        return VE_ERROR_MEMORY_PROTECT;

    return VE_OK;
}

/// @brief Saves the original instructions that are at the target address
/// @param target_address Address to the target
/// @param dest Pointer to hook
void Save_original_instructions(void *target_address, Hook *dest)
{
    memcpy(dest->original_instructions, target_address, sizeof(dest->original_instructions));
}

/// @brief Restores instructions that were saved with Save_original_instructions
/// @param hook The hook
void Restore_original_instructions(Hook hook)
{
    memcpy(hook.target, hook.original_instructions, sizeof(hook.original_instructions));
}


/// @brief Injects the `jmp` instruction at the `target address` to the `hook address`
/// @param target_address Address to the target
/// @param hook_address Address to the hook
void Apply_detour(void *target_address, void *hook_address)
{
    // 32 bits
    if (sizeof(void *) == 4)
    {
        // Set the jump instruction and its size
        const int jmp_size = 5;
        unsigned char jmp[jmp_size] = {0xE9, 0x00, 0x00, 0x00, 0x00};

        // Calculate offset
        intptr_t offset = ((intptr_t)hook_address - (intptr_t)target_address - jmp_size);

        // Copy instruction from jmp hook_address to target address
        memcpy(&jmp[1], &offset, sizeof(offset));
        memcpy(target_address, jmp, sizeof(jmp));
    }

    // Set the jump instruction and its size
    const int jmp_size = 8;
    unsigned char jmp[jmp_size] = {0xE9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Calculate offset
    intptr_t offset = ((intptr_t)hook_address - (intptr_t)target_address - jmp_size);

    // Copy instruction from jmp hook_address to target address
    memcpy(&jmp[1], &offset, sizeof(offset));
    memcpy(target_address, jmp, sizeof(jmp));
}
