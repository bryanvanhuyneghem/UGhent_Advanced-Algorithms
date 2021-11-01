cmake_minimum_required(VERSION 3.10)

project(labo_template)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

add_executable(labo_roodzwarteboom src/main.cpp ${HEADERS})

#copy input file for 'Ovidius' to build directory
configure_file(Ovidius Ovidius COPYONLY)

enable_testing()
add_subdirectory (test)

