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