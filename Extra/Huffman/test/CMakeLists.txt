cmake_minimum_required (VERSION 3.14)

#Setup doctest
include(FetchContent)
FetchContent_Declare(doctest
  GIT_REPOSITORY 	"https://github.com/onqtam/doctest"
  GIT_TAG 		"v2.4.9"
  GIT_SHALLOW		true
)

FetchContent_MakeAvailable(doctest)

LIST(APPEND CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/contrib")
set(AdditionalCatchParameters )

project (huffman_test)
add_executable(huffman_test test.cpp ../src/huffman.cpp)

target_link_libraries(huffman_test doctest bitstream)

include(CTest)
include (${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(huffman_test
 	EXTRA_ARGS -o report.xml -s -r junit
)