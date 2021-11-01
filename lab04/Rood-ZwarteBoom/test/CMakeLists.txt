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
#add_subdirectory(catch EXCLUDE_FROM_ALL)

include_directories(../src)

project (labo_roodzwarteboom_test)

#copy input file for 'Ovidius' to build directory
configure_file(../Ovidius Ovidius COPYONLY)

add_executable(roodzwarteboom_test test.cpp ${HEADERS})
target_link_libraries(roodzwarteboom_test PRIVATE Catch2::Catch2)



include(CTest)
include(Catch)
catch_discover_tests(roodzwarteboom_test
	EXTRA_ARGS -o report.xml -s -r junit
)
