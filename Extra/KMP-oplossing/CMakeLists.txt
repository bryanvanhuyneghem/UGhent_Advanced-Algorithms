cmake_minimum_required(VERSION 3.10)

project(kmp)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")


#Setup CSV reader
include(FetchContent)
FetchContent_Declare(csv
  GIT_REPOSITORY 	"https://github.com/vincentlaucsb/csv-parser.git"
  GIT_TAG 		"2.1.3"
  GIT_SHALLOW		true
)

FetchContent_MakeAvailable(csv)

include_directories(${csv_SOURCE_DIR}/single_include)


include_directories(include)

add_library(kmpLib STATIC src/automaten.cpp src/naiefZoeken.cpp include/automaten.h include/naiefZoeken.h)
add_executable(kmp src/main.cpp)
target_link_libraries(kmp kmpLib)

configure_file( realdonaldtrump.csv realdonaldtrump.csv COPYONLY)

enable_testing()
add_subdirectory (test)

