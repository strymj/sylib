cmake_minimum_required(VERSION 2.8.3)

project(sylib)

add_definitions(-std=c++11)

include_directories(
	include
	)

add_library(${PROJECT_NAME}
	src/math.cpp
	src/io.cpp
	src/wave.cpp
	)

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install (FILES
	include/sylib/io.h
	include/sylib/math.h
	include/sylib/wave.h
	DESTINATION "include/${PROJECT_NAME}/")
