cmake_minimum_required(VERSION 3.10)

project(sodor)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

#Fetch nlohmann/json repository
include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1
  GIT_SHALLOW		true)


FetchContent_MakeAvailable(json)

# Define all libraries and their dependencies
set(HEADERS
	include/graaf.h
    include/stroomnet.h
)

# Executable for 'bipartite graaf'
add_executable(bipartite src/bipartite.cpp ${HEADERS})

#copy input file for 'bipartite' to build directory
configure_file(bipartitegraaf bipartitegraaf COPYONLY)

add_library(NetworkReader SHARED src/network-reader.cpp)
target_link_libraries(NetworkReader PUBLIC nlohmann_json::nlohmann_json)

add_library(SodorLib SHARED src/sodor.cpp ${HEADERS})
target_link_libraries(SodorLib PUBLIC NetworkReader)

#Executable for 'sodor'
set(SOURCES
	src/sodor-main.cpp
) 
			
add_executable(sodor ${SOURCES})
target_link_libraries(sodor PRIVATE SodorLib)

#copy input file for 'sodor' to build directory
configure_file(sodor-trainnetwork.json sodor-trainnetwork.json COPYONLY)

enable_testing()
add_subdirectory (test)

