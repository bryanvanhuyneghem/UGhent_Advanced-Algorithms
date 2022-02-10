cmake_minimum_required(VERSION 3.10)

project(labo_patricia)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")


include_directories(include)

set(SOURCES
	src/main.cpp
) 

set(HEADERS
)
			
add_executable(Patricia ${SOURCES} ${HEADERS})

configure_file(bible.txt bible.txt COPYONLY)

enable_testing()
add_subdirectory (test)

