cmake_minimum_required(VERSION 3.10)

project(LZW)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

set(LZW_HEADERS
	include/lzw.h
	include/bitstream.h
)

set(LZW_SOURCES
	src/lzw.cpp
	src/bitstream.cpp
)

add_library(lzwLib SHARED ${LZW_SOURCES} ${LZW_HEADERS})

set(SOURCES
	src/main.cpp
) 
			
add_executable(lzw_compressie ${SOURCES} ${HEADERS})
target_link_libraries(lzw_compressie PUBLIC lzwLib)

enable_testing()
add_subdirectory (test)

