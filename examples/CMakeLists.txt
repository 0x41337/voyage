include_directories("../include")

file(GLOB SOURCES "*.cpp")

foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})

    target_link_libraries(${EXECUTABLE_NAME} voyage)
endforeach()