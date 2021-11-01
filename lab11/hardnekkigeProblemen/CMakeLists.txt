cmake_minimum_required(VERSION 3.10)

project(labo_simulated_annealing)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(include)

# Definitie van XML-library
add_library(pugixml STATIC deps/pugi/pugixml.hpp deps/pugi/pugixml.cpp)
include_directories(deps/pugi)


# Definitie van Probalisitic Probing bibliotheek
add_library(probProbLib STATIC include/probprob.h include/kerstman_prob.h src/kerstman_prob.cpp)

# Voorbeeld van probalistic probing 
add_executable(probprob_voorbeeld src/probprob_voorbeeld.cpp)
target_link_libraries(probprob_voorbeeld probProbLib)

# Definitie van Simmulated Annealing bibiliotheek
add_library(saLib STATIC src/kerstman_sa.cpp)

add_library(kerstmanLib STATIC include/kerstman.h src/kerstman.cpp)

target_link_libraries(kerstmanLib pugixml)
configure_file(kerstnet.xml kerstnet.xml COPYONLY)

add_executable(labo_simulated_annealing src/main.cpp)
target_link_libraries(labo_simulated_annealing kerstmanLib saLib probProbLib)

enable_testing()
add_subdirectory (test)

