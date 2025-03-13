cmake_minimum_required (VERSION 3.8)

project(magma-test)

set(SOURCE_FILES "magma-test-linux.cpp")

add_executable (magma-test ${SOURCE_FILES})
 
include_directories("../magma")
target_link_libraries(magma-test magma)

