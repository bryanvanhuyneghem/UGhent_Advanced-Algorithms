cmake_minimum_required(VERSION 3.10)

project(debruijn)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

add_library(Euler SHARED src/euler.cpp include/graaf.hpp)


set(SOURCES
	src/main.cpp
)

set(HEADERS
	"include/graaf.hpp"
)
			
add_executable(ryanair ${SOURCES} ${HEADERS})
target_link_libraries(ryanair PUBLIC Euler)

add_executable(pin src/pin.cpp ${HEADERS})
target_link_libraries(pin PUBLIC Euler)


configure_file(ryanair.txt ryanair.txt COPYONLY)

enable_testing()
add_subdirectory (test)

