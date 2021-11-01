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

project (kettingwoorden_test)
add_executable(kettingwoorden_test test.cpp)
set_property(TARGET kettingwoorden_test PROPERTY CXX_STANDARD 17)
set_property(TARGET kettingwoorden_test PROPERTY CXX_STANDARD_REQUIRED ON)
include_directories(../src)

target_link_libraries(kettingwoorden_test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(kettingwoorden_test
	EXTRA_ARGS -o report.xml -s -r junit
)
