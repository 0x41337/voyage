# ⬇ Installation

In this topic we will understand how to install the library and how to use it in our projects.

Note: The example here will use CMake if you use another type of construction system such as Meson or Bazel the integration parameters will change.

First let's clone the repository and build Voyage as part of our project.

```
$ git submodule init
$ git submodule add https://github.com/0x41337/voyage.git vendor/voyage
```

This will add the library as a vendorized dependency to our project. Now we can write our CMake file:

```cmake
cmake_minimum_required(VERSION 3.15)
project(my_project CXX)

add_subdirectory(vendor/voyage)
target_link_libraries(${PROJECT_NAME} voyage)
```

What we just did was include the library as part of the project and link it to our project Now the `<voyage.h>` headers are available and can be used.
