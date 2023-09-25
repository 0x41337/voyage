include_directories("../include")

add_executable(simple_hook
    simple_hook.cpp
)

target_link_libraries(simple_hook
    voyage
)