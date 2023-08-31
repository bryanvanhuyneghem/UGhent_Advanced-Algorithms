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

project (autocomplete_test)
add_executable(autocomplete_test test.cpp ../src/ternaire-zoekboom.cpp)

target_link_libraries(autocomplete_test doctest )

configure_file(../woordenlijst.txt woordenlijst.txt COPYONLY)

include(CTest)
include (${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(autocomplete_test
 	EXTRA_ARGS -o report.xml -s -r junit
)