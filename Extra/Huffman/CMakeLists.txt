cmake_minimum_required(VERSION 3.10)

project(labo_autocomplete)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")


include_directories(include)

add_library(bitstream SHARED include/bitstream.h src/bitstream.cpp)

add_executable(huffman src/main.cpp src/huffman.cpp)
target_link_libraries(huffman bitstream)


configure_file( hamlet.txt hamlet.txt COPYONLY)

enable_testing()
add_subdirectory (test)