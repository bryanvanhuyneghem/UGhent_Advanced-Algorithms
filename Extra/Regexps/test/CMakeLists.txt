cmake_minimum_required (VERSION 3.14)

#Setup doctest
include(FetchContent)
FetchContent_Declare(doctest
  GIT_REPOSITORY 	"https://github.com/onqtam/doctest"
  GIT_TAG 		"v2.4.9"
  GIT_SHALLOW		true
)

FetchContent_MakeAvailable(doctest)

LIST(APPEND CMAKE_MODULE_PATH "${catch_SOURCE_DIR}/contrib")
set(AdditionalCatchParameters )

project (automaten_test)
add_executable(automaten_test test.cpp)

target_link_libraries(automaten_test doctest RegexpLib)

include(CTest)
include (${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(automaten_test
 	EXTRA_ARGS -o report.xml -s -r junit
)
