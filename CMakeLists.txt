﻿# CMakeList.txt : CMake project for SoftRayTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (SoftRayTracer)

find_program(CLANG_FORMAT_EXE NAMES "clang-format" DOC "Path to clang-format executable")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(MATH_DIR "${SRC_DIR}/math")
set(MATH_FILES
	# Header files
	"${MATH_DIR}/tmath.h"
	#"${MATH_DIR}/interval.h"
)

set(GEOMETRY_DIR "${SRC_DIR}/geometry")
set(GEOMETRY_FILES 
	# Header files
	"${GEOMETRY_DIR}/vector.h"
	"${GEOMETRY_DIR}/ray.h"
	"${GEOMETRY_DIR}/traceable.h"
	"${GEOMETRY_DIR}/sphere.h"
)

set(UTILS_DIR "${SRC_DIR}/utils")
set(UTILS_FILES
	# Header files
	"${UTILS_DIR}/log.h"
	"${UTILS_DIR}/tassert.h"
	"${UTILS_DIR}/utils.h"
	# Source files
)

set(SRC_FILES 
	# Header files
	"${SRC_DIR}/image.h"
	"${SRC_DIR}/color.h"
	"${SRC_DIR}/camera.h"
	"${SRC_DIR}/world.h"
	"${SRC_DIR}/material.h"
	# Source files
	"${SRC_DIR}/image.cpp"
	"${SRC_DIR}/camera.cpp"
)

set(MAIN_FILES
	"${SRC_DIR}/SoftRayTracer.cpp" 
	"${SRC_DIR}/SoftRayTracer.h"
)

set(PROJECT_FILES
	${MATH_FILES}
	${GEOMETRY_FILES}
	${UTILS_FILES}
	${SRC_FILES}
	${MAIN_FILES}
)

# Add source to this project's executable.
add_executable (SoftRayTracer ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC 
	${MATH_DIR}
	${GEOMETRY_DIR}
	${UTILS_DIR}
	${SRC_DIR}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SoftRayTracer PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(vendor)

target_link_libraries(${PROJECT_NAME} PUBLIC
	stb
	spdlog
)

if(CLANG_FORMAT_EXE)
    add_custom_target(
		Code-Format COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${PROJECT_FILES})

	add_dependencies(${PROJECT_NAME} Code-Format)
endif()