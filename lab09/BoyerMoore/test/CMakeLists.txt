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

project (boyer_moore_test)

set(TEST_SOURCES
      test.cpp
      #haal de volgende regel uit commentaar om de benchmarks aan te zetten
      benchmark.cpp
      )

add_executable(boyer_moore_test ${TEST_SOURCES})

target_link_libraries(boyer_moore_test Catch2::Catch2 bmLib)

file(COPY files DESTINATION .)


include(CTest)
include(Catch)
catch_discover_tests(boyer_moore_test
	EXTRA_ARGS -o report.xml -s -r junit
)
