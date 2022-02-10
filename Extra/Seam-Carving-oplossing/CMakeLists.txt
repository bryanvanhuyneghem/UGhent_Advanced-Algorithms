cmake_minimum_required(VERSION 3.10)

project(labo_seamcarving)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -fsanitize=address,undefined -fno-omit-frame-pointer")

# OpenCV contains a memory leak. Ignore it!
configure_file(lsan_suppressions.txt lsan_suppressions.txt COPYONLY)

# Find OpenCV on the system (if this fails: run `apt install libopencv-dev`)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(include)

add_library(seamcarving SHARED src/seamcarving.cpp)
target_link_libraries(seamcarving ${OpenCV_LIBS})

set(SOURCES
	src/main.cpp
) 

set(HEADERS
)
			
add_executable(sc ${SOURCES} ${HEADERS})
target_link_libraries(sc seamcarving ${OpenCV_LIBS})


configure_file(kasteel.jpg kasteel.jpg COPYONLY)

enable_testing()
add_subdirectory (test)

