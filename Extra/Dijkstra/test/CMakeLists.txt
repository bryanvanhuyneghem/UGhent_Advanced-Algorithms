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

project (fietsknooppunten_test)
add_executable(fietsknooppunten_test test.cpp)

target_link_libraries(fietsknooppunten_test PRIVATE doctest fietsnet)


configure_file(../knooppunten.csv knooppunten.csv COPYONLY)
configure_file(../trajecten.csv trajecten.csv COPYONLY)


include(CTest)
include (${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(fietsknooppunten_test
 	EXTRA_ARGS -o report.xml -s -r junit
)
