cmake_minimum_required (VERSION 3.14)

project (debruijn_test)

#Setup Catch2
include(FetchContent)
FetchContent_Declare(catch
  GIT_REPOSITORY 	"https://github.com/catchorg/catch2.git"
  GIT_TAG 		"v2.13.0"
  GIT_SHALLOW		true
)

FetchContent_MakeAvailable(catch)

LIST(APPEND CMAKE_MODULE_PATH "${catch_SOURCE_DIR}/contrib")
set(AdditionalCatchParameters )
#add_subdirectory(catch EXCLUDE_FROM_ALL)


set(SOURCES
	  test.cpp
)

add_executable(debruijn_test ${SOURCES} ${HEADERS})
target_link_libraries(debruijn_test PUBLIC Graaf Euler DeBruijn Catch2::Catch2)


include(CTest)
include(Catch)
catch_discover_tests(debruijn_test
	EXTRA_ARGS -o report.xml -s -r junit
)
