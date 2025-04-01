# CMakeList.txt : CMake project for SoftRayTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (SoftRayTracer)

find_program(CLANG_FORMAT_EXE NAMES "clang-format" DOC "Path to clang-format executable")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(MATH_FILES 
	"${SRC_DIR}/math/vector.h"
)
set(MAIN_FILES
	"SoftRayTracer.cpp" 
	"SoftRayTracer.h"
)

set(PROJECT_FILES
	${MATH_FILES}
	${MAIN_FILES}
)

# Add source to this project's executable.
add_executable (SoftRayTracer ${PROJECT_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SoftRayTracer PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(vendor)

target_link_libraries(${PROJECT_NAME} PUBLIC
	stb
)

if(CLANG_FORMAT_EXE)
    add_custom_target(
		Code-Format COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${PROJECT_FILES})

	add_dependencies(${PROJECT_NAME} Code-Format)
endif()