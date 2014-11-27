cmake_minimum_required(VERSION 2.6)

project(Simplicity)

add_definitions(-std=gnu++11)

set(Simplicity_VERSION_MAJOR 0)
set(Simplicity_VERSION_MINOR 0)
set(Simplicity_VERSION_PATCH 0)
set(Simplicity_VERSION_BUILD 0) # TODO: auto replace this

set(
	Simplicity_VERSION
	"${Simplicity_VERSION_MAJOR}.${Simplicity_VERSION_MINOR}.${Simplicity_VERSION_PATCH}.${Simplicity_VERSION_BUILD}"
)

set(SRC "${PROJECT_SOURCE_DIR}/src")

configure_file(
	"${SRC}/config.hpp.in"
	"${SRC}/config.hpp"
)

include_directories("${PROJECT_BINARY_DIR}")

# Libraries and includes
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(PkgConfig REQUIRED)

find_package(Boost REQUIRED
	COMPONENTS
		log
		log_setup
		program_options
		system
		thread
)

include_directories(${Boost_INCLUDE_DIRS})

pkg_check_modules(XCB xcb REQUIRED)
include_directories(${XCB_INCLUDE_DIRS})

pkg_check_modules(XCB_UTIL xcb-util REQUIRED)
include_directories(${XCB_UTIL_INCLUDE_DIRS})

# End of libraries and includes

add_executable(simplicity "${SRC}/main.cpp" "${SRC}/application.cpp")
target_link_libraries(simplicity ${Boost_LIBRARIES} ${XCB_LIBRARIES} ${XCB_UTIL_LIBRARIES})

