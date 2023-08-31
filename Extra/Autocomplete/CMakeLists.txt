cmake_minimum_required(VERSION 3.10)

project(labo_autocomplete)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)	

configure_file(woordenlijst.txt woordenlijst.txt COPYONLY)

add_executable(autocomplete src/main.cpp src/ternaire-zoekboom.cpp)


enable_testing()
add_subdirectory (test)