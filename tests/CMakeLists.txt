enable_testing()

include_directories("../include")

add_executable(voyage_test
    voyage_test.cpp
)

target_link_libraries(voyage_test 
    GTest::gtest_main
    voyage
)

include(GoogleTest)
gtest_discover_tests(voyage_test)
