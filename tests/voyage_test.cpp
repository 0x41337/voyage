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

#include <voyage.h>
#include <gtest/gtest.h>

/* Tests for: VE_FindSymbolAddress */
TEST(voyage_test, FindSymbolAddress_ModuleNotFound)
{
    void (*printf_ptr)(const char *_Format, ...) = nullptr;
    VE_STATUS status = VE_FindSymbolAddress("not_found", "printf", &printf_ptr);
    EXPECT_EQ(status, VE_ERROR_MODULE_NOT_FOUND);
};

TEST(voyage_test, FindSymbolAddress_SymbolNotFound)
{
    void (*printf_ptr)(const char *_Format, ...) = nullptr;
    VE_STATUS status = VE_FindSymbolAddress("", "not_found", &printf_ptr);
    EXPECT_EQ(status, VE_ERROR_SYMBOL_NOT_FOUND);
};

TEST(voyage_test, FindSymbolAddress_Success)
{
    void *(*printf_ptr)(const char *_Format, ...) = nullptr;
    VE_STATUS status = VE_FindSymbolAddress("", "printf", &printf_ptr);
    EXPECT_EQ(status, VE_OK);
    EXPECT_NE(printf_ptr, nullptr);
}

/* Tests for: VE_CreateHook */
int add(int x, int y) { return x + y; }
int add_hook(int x, int y) { return x - y; }
TEST(voyage_test, VE_CreateHook_Success)
{
    Hook hook;
    VE_STATUS status = VE_CreateHook(reinterpret_cast<void *>(&add), reinterpret_cast<void *>(&add_hook), &hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(add(1, 1), 0);
}

TEST(voyage_test, VE_CreateHook_HookAlreadyCreated)
{
    Hook hook;

    VE_CreateHook(reinterpret_cast<void *>(&add), reinterpret_cast<void *>(&add_hook), &hook);
    VE_STATUS status = VE_CreateHook(reinterpret_cast<void *>(&add), reinterpret_cast<void *>(&add_hook), &hook);

    EXPECT_EQ(status, VE_ERROR_ALREADY_CREATED);
}

/* tests for: VE_RemoveHook */
int sub(int x, int y) { return x - y; };
int sub_hook(int x, int y) { return x + y; };
TEST(voyage_test, VE_RemoveHook_Success)
{
    Hook hook;

    VE_STATUS status = VE_CreateHook(reinterpret_cast<void *>(&sub), reinterpret_cast<void *>(&sub_hook), &hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(sub(1, 1), 2);

    status = VE_RemoveHook(&hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(sub(1, 1), 0);
}

/* tests for: VE_EnableHook and VE_DisableHook */
TEST(voyage_test, VE_DisableHook_Success)
{
    Hook hook;

    VE_STATUS status = VE_CreateHook(reinterpret_cast<void *>(&sub), reinterpret_cast<void *>(&sub_hook), &hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(sub(1, 1), 2);

    status = VE_DisableHook(&hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(sub(1, 1), 0);
}

TEST(voyage_test, VE_EnableHook_Success)
{
    Hook hook;

    VE_STATUS status = VE_CreateHook(reinterpret_cast<void *>(&sub), reinterpret_cast<void *>(&sub_hook), &hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(sub(1, 1), 2);

    status = VE_DisableHook(&hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(sub(1, 1), 0);

    status = VE_EnableHook(&hook);
    EXPECT_EQ(status, VE_OK);
    EXPECT_EQ(sub(1, 1), 2);
}