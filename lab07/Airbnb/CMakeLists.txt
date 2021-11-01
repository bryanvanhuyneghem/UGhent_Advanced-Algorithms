cmake_minimum_required(VERSION 3.10)

project(btree)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

# Define all libraries and their dependencies
set(HEADERS
	include/bknoop.h
	include/btree.h
  include/schijf.h
  include/airbnb.h
)

set(SOURCES
  src/main.cpp
  src/airbnb.cpp
) 
			
add_executable(btree ${SOURCES})

#copy input file with airbnb-data to build directory
configure_file(AB_NYC_2019.csv AB_NYC_2019.csv COPYONLY)

enable_testing()
add_subdirectory (test)