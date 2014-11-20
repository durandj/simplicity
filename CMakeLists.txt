cmake_minimum_required(VERSION 2.6)

project(Simplicity)

set(Simplicity_VERSION_MAJOR 0)
set(Simplicity_VERSION_MINOR 0)
set(Simplicity_VERSION_PATCH 0)
set(Simplicity_VERSION_BUILD 0) # TODO: auto replace this

set(SRC "${PROJECT_SOURCE_DIR}/src")

configure_file(
	"${SRC}/config.h.in"
	"${SRC}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(simplicity "${SRC}/main.cpp")

