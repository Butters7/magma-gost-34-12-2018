cmake_minimum_required (VERSION 3.5)

project(magma)
     
set(SOURCE_FILES "magma.cpp")
set(HEADER_FILES "magma.h")

add_library(magma SHARED ${HEADER_FILES} ${SOURCE_FILES})
