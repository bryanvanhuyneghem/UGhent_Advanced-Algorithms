cmake_minimum_required (VERSION 3.14)

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

project (Patricia_test)
add_executable(Patricia_test test.cpp)

target_link_libraries(Patricia_test Catch2::Catch2)



include(CTest)
include(Catch)
catch_discover_tests(Patricia_test
	EXTRA_ARGS -o report.xml -s -r junit
)
