cmake_minimum_required(VERSION 2.6)
project(monitor)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# enable_testing()
# # include testing TP library
add_subdirectory(thirdparty/googletest)
include_directories(${GTEST_SOURCE_DIRS} ${GTEST_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(monitor ${SOURCES})

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)

# test target:
# Add the testing executable
add_executable(utest_linux_parser test/utest_linux_parser.cpp src/linux_parser.cpp)
target_link_libraries(utest_linux_parser
    gtest    
    gtest_main
)

add_test( monitor_test utest_linux_parser )
