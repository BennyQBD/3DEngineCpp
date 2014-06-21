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
# ASSIMP_FOUND                              #
# ASSIMP_INCLUDE_DIRS                       #
# ASSIMP_LIBRARIES                          #
#############################################

SET( ASSIMP_SEARCH_PATHS
	${ASSIMP_ROOT_DIR}					# ASSIMP!
	./lib/Assimp
	$ENV{PROGRAMFILES}/ASSIMP			# WINDOWS
	"$ENV{PROGRAMFILES(X86)}/ASSIMP"	# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
	/sw									# Fink
	/opt/local							# DarwinPorts
	/opt/csw							# Blastwave
)

FIND_PATH( ASSIMP_INCLUDE_DIRS
	NAMES
		assimp/mesh.h
	PATHS
		${ASSIMP_SEARCH_PATHS}
	PATH_SUFFIXES
		include
	DOC
		"The directory where assimp/mesh.h resides"
)

FIND_LIBRARY( ASSIMP_LIBRARIES
	NAMES
		assimp ASSIMP
	PATHS
		${ASSIMP_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC
		"The ASSIMP library"
)

# Check if we found it!
IF ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )
	SET( ASSIMP_FOUND TRUE )
	MESSAGE(STATUS "Looking for ASSIMP - found")
ELSE ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )
	SET( ASSIMP_FOUND FALSE )
	MESSAGE(STATUS "Looking for ASSIMP - not found")
ENDIF ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )
