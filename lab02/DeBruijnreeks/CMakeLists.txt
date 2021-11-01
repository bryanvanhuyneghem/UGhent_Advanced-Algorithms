cmake_minimum_required(VERSION 3.10)

project(debruijn)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

add_library(Graaf INTERFACE)
target_include_directories(Graaf INTERFACE include/)

add_library(Euler SHARED src/euler.cpp)
add_library(DeBruijn SHARED src/debruijnreeks.cpp)
target_link_libraries(DeBruijn PUBLIC Euler)

set(SOURCES
	src/main.cpp
)
			
add_executable(debruijn ${SOURCES} ${HEADERS})
target_link_libraries(debruijn PUBLIC Graaf Euler DeBruijn)


enable_testing()
add_subdirectory (test)

