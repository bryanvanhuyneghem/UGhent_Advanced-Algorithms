cmake_minimum_required(VERSION 3.10)

project(automaten)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

add_library(RegexpLib STATIC include/regexp.h src/regexp.cpp include/automaten.h src/automaten.cpp)
		
add_executable(regexp_voorbeeld src/regexp_voorbeeld.cpp)
target_link_libraries(regexp_voorbeeld RegexpLib)

enable_testing()
add_subdirectory (test)

