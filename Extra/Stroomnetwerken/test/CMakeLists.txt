cmake_minimum_required (VERSION 3.14)

project (stroomnet_test_project)

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


add_executable(stroomnet_test test.cpp)
target_link_libraries(stroomnet_test PUBLIC Catch2::Catch2 galadiner_lib)


include(CTest)
include(Catch)
catch_discover_tests(stroomnet_test
	EXTRA_ARGS -o report.xml -s -r junit
)
