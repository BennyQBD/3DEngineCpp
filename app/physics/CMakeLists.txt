# Copyright (C) 2014 Barry Deeney
# Copyright (C) 2014 Benny Bobaganoosh
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# We need features that are 2.6 >= dependent
cmake_minimum_required(VERSION 2.6)

# Name the project
project(Physics)

# Add the -c and -Wall flags
add_definitions(-c -Wall)

# If no build target, build debug
if (CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE "Debug")
endif (CMAKE_BUILD_TYPE STREQUAL "")

# If building for release add optimize flag
if (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions( -O2 )
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# Lets LOAD app our headers!
file(GLOB APP_HDRS ${PROJECT_SOURCE_DIR}/src/*.h)

# Load app our sources!
file(GLOB APP_SRCS
	${PROJECT_SOURCE_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/src/*.c
)

# Define the library
add_executable(Physics ${APP_HDRS} ${APP_SRCS})

# Define the include DIRs
include_directories(
	${PROJECT_SOURCE_DIR}/src
	${Engine_SOURCE_DIR}/src
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries(
	Physics
	Engine
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	${ASSIMP_LIBRARIES}
)
