cmake_minimum_required(VERSION 3.10)

project(labo_fietsknooppunten)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
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

#Setup Web Server
# ------------ Download CPM CMake Script ----------------#

## Automatically donwload and use module CPM.cmake
file(DOWNLOAD https://raw.githubusercontent.com/TheLartians/CPM.cmake/v0.26.2/cmake/CPM.cmake
                 "${CMAKE_BINARY_DIR}/CPM.cmake")
include("${CMAKE_BINARY_DIR}/CPM.cmake")

CPMAddPackage(
    NAME  httplib 
    URL  "https://github.com/yhirose/cpp-httplib/archive/v0.6.6.zip"
)
include_directories( ${httplib_SOURCE_DIR} )

include_directories(include)

add_library(fietsnet SHARED src/fietsnet.cpp)
target_link_libraries(fietsnet csv)


add_library(serializer SHARED  src/serializer.cpp)
target_link_libraries(serializer fietsnet)

set(SOURCES	src/webserver.cpp) 

set(HEADERS)
			
add_executable(fietsknooppunten ${SOURCES} ${HEADERS})
target_link_libraries(fietsknooppunten PRIVATE fietsnet serializer PUBLIC httplib)

configure_file(knooppunten.csv knooppunten.csv COPYONLY)
configure_file( trajecten.csv trajecten.csv COPYONLY)
file(COPY www DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")


enable_testing()
add_subdirectory (test)

