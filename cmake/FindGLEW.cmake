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

#############################################
# Try to find ASSMIP and set the following: #
#                                           #
# GLEW_FOUND                                #
# GLEW_INCLUDE_DIRS                         #
# GLEW_LIBRARIES                            #
#############################################

SET( GLEW_SEARCH_PATHS
	${GLEW_ROOT_DIR}					# GLEW!
	./lib/glew
	$ENV{PROGRAMFILES}/GLEW				# WINDOWS
	"$ENV{PROGRAMFILES(X86)}/GLEW"		# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
	/sw									# Fink
	/opt/local							# DarwinPorts
	/opt/csw							# Blastwave
)

FIND_PATH( GLEW_INCLUDE_DIRS
	NAMES
		GL/glew.h
	PATHS
		${GLEW_SEARCH_PATHS}
	PATH_SUFFIXES
		include
	DOC
		"The directory where GL/glew.h resides"
)

FIND_LIBRARY( GLEW_LIBRARIES
	NAMES
		glew GLEW libGLEW.a glew32 glew32s
	PATHS
		${GLEW_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/Release/Win32
		lib/Release/x64
	DOC
		"The GLEW library"
)

# Check if we found it!
IF ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
	SET( GLEW_FOUND TRUE )
	MESSAGE( STATUS "Looking for GLEW - found" )
ELSE ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
	SET( GLEW_FOUND FALSE )
	MESSAGE( STATUS "Looking for GLEW - not found" )
ENDIF ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
