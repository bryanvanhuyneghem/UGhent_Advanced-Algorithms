cmake_minimum_required(VERSION 3.10)

project(labo_dynamisch_programmeren)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")


include_directories(include)

add_library(pakjeslib SHARED src/pakjes.cpp)

set(SOURCES
	src/main.cpp
) 

		
add_executable(labo_dynamisch_programmeren ${SOURCES} ${HEADERS})
target_link_libraries(labo_dynamisch_programmeren PRIVATE pakjeslib)

enable_testing()
add_subdirectory (test)

