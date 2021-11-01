cmake_minimum_required(VERSION 3.10)

project(labo_splayboom)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

#copy input file for 'voetbal_resultaten.csv' to build directory
configure_file(voetbal_resultaten.csv voetbal_resultaten.csv  COPYONLY)

include_directories(include)

add_library(landenLib SHARED src/leeslanden.cpp)

set(SOURCES
	src/splayboom.cpp
) 
			
add_executable(labo_splayboom ${SOURCES} ${HEADERS})
target_link_libraries(labo_splayboom PUBLIC landenLib)

enable_testing()
add_subdirectory (test)

