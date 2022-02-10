cmake_minimum_required(VERSION 3.10)

project(stroomnet_project)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)


set(SOURCES
	src/main.cpp
)

set(HEADERS
	"include/stroomnet.h"
	"include/graaf.hpp"
	"include/galadiner.h"
)

add_library(galadiner_lib src/galadiner.cpp include/stroomnet.h include/graaf.hpp)


add_executable(galadiner ${SOURCES} ${HEADERS})
target_link_libraries(galadiner PUBLIC galadiner_lib)

enable_testing()
add_subdirectory (test)

