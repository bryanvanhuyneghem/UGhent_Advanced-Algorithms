cmake_minimum_required(VERSION 3.10)

project(boyer_moore)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Deze flags zetten de address sanitizer aan
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-omit-frame-pointer")

# Optimaliseer voor een korte compile-tijd ipv een korte uitvoerings-tijd
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# Gebruike deze flags om te compileren met aggressieve optimalisaties door de compiler:
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3 -march=native" )

include_directories(include)

add_library(bmLib src/bm_verkeerdekarakter.cpp src/bm_horspool.cpp src/bm_sunday.cpp)

set(SOURCES
	src/benchmark.cpp
) 
			
add_executable(boyer_moore_benchmark ${SOURCES} ${HEADERS})
target_link_libraries(boyer_moore_benchmark bmLib)

file(COPY files DESTINATION .)

enable_testing()
add_subdirectory (test)

