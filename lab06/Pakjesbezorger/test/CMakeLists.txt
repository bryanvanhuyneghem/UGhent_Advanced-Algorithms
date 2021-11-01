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

include_directories(include)

project (labo_dynamisch_programmeren_test)
add_executable(labo_dynamisch_programmeren_test test.cpp)


target_link_libraries(labo_dynamisch_programmeren_test Catch2::Catch2 pakjeslib)

include(CTest)
include(Catch)
catch_discover_tests(labo_dynamisch_programmeren_test
	EXTRA_ARGS -o report.xml -s -r junit
)
