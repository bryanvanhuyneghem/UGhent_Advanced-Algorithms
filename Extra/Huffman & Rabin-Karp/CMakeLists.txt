cmake_minimum_required(VERSION 3.10)

project(geval_test_demo_project)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)	

add_executable(huffman src/vraag1.cpp include/huffman.h)

add_library(huffmanlib SHARED src/huffman.cpp include/huffman.h)
target_link_libraries(huffman PUBLIC huffmanlib)

add_executable(rabinKarp src/vraag2.cpp)