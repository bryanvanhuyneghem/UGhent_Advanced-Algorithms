cmake_minimum_required (VERSION 3.14)

project (debruijn_test)

#Setup doctest
include(FetchContent)
FetchContent_Declare(doctest
  GIT_REPOSITORY 	"https://github.com/onqtam/doctest"
  GIT_TAG 		"v2.4.9"
  GIT_SHALLOW		true
)

FetchContent_MakeAvailable(doctest)


set(SOURCES
	  test.cpp
)

add_executable(debruijn_test ${SOURCES} ${HEADERS})
target_link_libraries(debruijn_test PUBLIC Graaf Euler DeBruijn doctest)


include(CTest)
include (${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(debruijn_test
 	EXTRA_ARGS -o report.xml -s -r junit
)


