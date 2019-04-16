cmake_minimum_required(VERSION 3.13)
project(Wireworld)

option(BUILD_DEBUG "Build the debug binaries" off)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)
if(BUILD_DEBUG)
	add_compile_options(-g)
endif()

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)

file(GLOB_RECURSE sources "src/*.cpp")

add_executable(Wireworld ${sources})

target_include_directories(Wireworld PUBLIC "include")
target_link_libraries(Wireworld sfml-graphics sfml-window sfml-network sfml-audio sfml-system GL)