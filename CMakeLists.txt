cmake_minimum_required(VERSION 3.2)


# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS_DEBUG_INIT -Wall)

project(NewtonFractal VERSION 1.1 LANGUAGES C CXX)

#for out of source build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

file(GLOB INCLUDES 
	includes/*.h 
	includes/*.hpp
	${CMAKE_SOURCE_DIR}/Dependencies/includes/*
)
file(GLOB SRC src/*.cpp src/*.c)

include_directories(
	${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/Dependencies/includes
	
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/)


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("Build type: ${CMAKE_BUILD_TYPE}")
	link_directories(${CMAKE_SOURCE_DIR}/Dependencies/lib)

	add_executable(NewtonFractal src/main.cpp ${SRC} ${INCLUDES})
	target_link_libraries(NewtonFractal glfw3.lib opengl32)



elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	add_executable(NewtonFractal src/main.cpp ${SRC} ${INCLUDES})
	target_link_libraries(NewtonFractal glfw GL dl)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")