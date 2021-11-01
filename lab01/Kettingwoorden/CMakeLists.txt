cmake_minimum_required(VERSION 3.10)

project(kettingwoorden)

set(SOURCES
	src/main.cpp
) 

set(HEADERS 
	src/graaf.hpp
	src/keten.hpp
)
			
add_executable(kettingwoorden ${SOURCES} ${HEADERS})
add_executable(keten_demo src/keten_demo.cpp src/keten.hpp)

set_property(TARGET kettingwoorden PROPERTY CXX_STANDARD 17)
set_property(TARGET kettingwoorden PROPERTY CXX_STANDARD_REQUIRED ON)

# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

enable_testing()
add_subdirectory (test)

