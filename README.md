# The voyage
[![CMake on a single platform](https://github.com/0x41337/voyage/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/0x41337/voyage/actions/workflows/cmake-single-platform.yml)
![](https://img.shields.io/badge/License-GPL_3.0-blue)
![](https://img.shields.io/badge/Version-0.2-yellow)

Voyage is a library for creating/managing hooks for unix systems.<br>
Voyage is inspired by the [Dobby](https://github.com/jmpews/Dobby), [Minhook](https://github.com/TsudaKageyu/minhook) and [Libmem](https://github.com/rdbo/libmem) libraries, which are great libraries. (You should look)<br> 
If you know how to use some of the libraries mentioned, you will certainly feel comfortable using Voyage.

## Dependencies

-   `googletest` Framework for writing tests.

## How to build

Make sure you have all dependencies that contain _\*_ in their name.
You can build the library using cmake:

```sh
$ cmake -S . -B build
```

And

```sh
$ cmake --build build
```

If everything goes well you should have the shared library.

## Integration

Voyage is a C++ project so if you are creating a project with C/C++ together with CMake you can build Voyage alongside your project:

-   Add Voyage as a vendorized dependency using git modules:

```sh
$ git submodule add repository/voyage.git vendor/voyage
```
> Note: You should change `repository` to the original repository. I just used this name to shorten the command and make it easier to read.

-   Then add it to your CMake file:

```cmake
add_subdirectory(vendor/voyage)
```

-   And lastly you can link your binary/library with Voyage:

```cmake
target_link_libraries(your_project voyage)
```

## The tests
Tests are written using the `googletest` testing framework and are located in the `tests` folder.

After compiling the project, you can use the command below to run the tests:
```sh
$ ctest --test-dir build/tests
```

## Development status
Voyage is still in the development phase in version 0.2. Below is a list of what has been implemented and what has not yet been implemented:

**Voyage core**
- [x] Trampoline
- [x] Memory protection
- [ ] Support for multiple architectures (Current focus)

**Voyage api**
- [x] `VE_FindSymbolAddress`
- [x] `VE_CreateHook` 
- [ ] `VE_RemoveHook` (Current focus)
- [ ] `VE_EnableHook`
- [ ] `VE_Disablehook`

**Voyage repository**
- [ ] Documentation
- [ ] Examples

## Documentation
All library documentation is available as markdown files in the `docs` folder

## Examples
The examples are in the `examples` folder

## License and Terms
The Voyage code is under the `GPL-3.0` license. Third-party libraries used in the construction of the project may be under other licenses and terms, check the copy of the license and see the license and terms of the libraries used before using.
