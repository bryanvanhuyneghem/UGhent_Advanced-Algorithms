cmake_minimum_required(VERSION 3.10)

project(DEFLATE)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # -fsanitize=address,undefined -fno-omit-frame-pointer")

add_library(sais INTERFACE)
target_include_directories(sais INTERFACE deps/sais/include)

include_directories(include)

set(LZ77_HEADERS
	include/lz77.h
	include/suffix_array.h
	include/bitstream.h
)

set(LZ77_SOURCES
	src/lz77.cpp
	src/suffix_array.cpp
	src/bitstream.cpp
)

add_library(lz77Lib SHARED ${LZ77_SOURCES} ${LZ77_HEADERS})
target_link_libraries(lz77Lib sais)

set(SOURCES
	src/main.cpp
) 
			
add_executable(deflate ${SOURCES} ${HEADERS})
target_link_libraries(deflate PUBLIC lz77Lib)

enable_testing()
add_subdirectory (test)

