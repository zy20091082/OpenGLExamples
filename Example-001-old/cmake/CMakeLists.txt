########################################################################################################################################################
# David Canino (canino.david@gmail.com)
#
# Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
#
# Last update: December 2016
#                                                                    
# This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
#                                                                           
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for
# more details.
#
# CMakeLists.txt - the settings for constructing the makefile of interest for the 'Example-001 (Old Mode)'
########################################################################################################################################################

cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
project(Example-001-old LANGUAGES CXX)
message("")
message(STATUS "We assume that the GLU and the OpenGL package are stored in the same package (like in the recent distributions)")
if(APPLE OR CMAKE_HOST_APPLE)

	# We are using a Macintosh Apple (MacOSX) platform. First, we look for the 'OpenGL' package
	message("")
	find_package(OpenGL REQUIRED)
	message(STATUS "The path of the 'include' folder for the OpenGL package: " ${OPENGL_INCLUDE_DIR})
	message(STATUS "The library file(s) for the OpenGL package: " ${OPENGL_LIBRARIES})
	message("")

	# Now, we look for the 'GLUT' package.
	find_package(GLUT REQUIRED)
	message(STATUS "The path of the 'include' folder for the GLUT package: " ${GLUT_INCLUDE_DIR})
	message(STATUS "The library file(s) for the GLUT package: " ${GLUT_LIBRARIES})
	message("")

	# Now, we look for the 'GLEW' package.	
	find_package(GLEW REQUIRED)
	message(STATUS "The path of the 'include' folder for the GLUT package: " ${GLEW_INCLUDE_DIR})
	message(STATUS "The library file(s) for the GLEW package: " ${GLEW_LIBRARIES})
	message("")

	# If we arrive here, we compose the final constants.
	set(INCLUDES ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
	set(LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
	add_executable(Example-001-old ../src/main.cpp)

elseif(UNIX OR CMAKE_HOST_UNIX)

	# We are using a Unix-like platform, maybe the GNU/Linux. First, we look for the 'OpenGL' package
	message("")
	find_package(OpenGL REQUIRED)
	message(STATUS "The path of the 'include' folder for the OpenGL package: " ${OPENGL_INCLUDE_DIR})
	message(STATUS "The libraries for the OpenGL package: " ${OPENGL_LIBRARIES})
	message("")

	# Now, we look for the 'GLUT' package.
	find_package(GLUT REQUIRED)
	message(STATUS "The path of the 'include' folder for the GLUT package: " ${GLUT_INCLUDE_DIR})
	message(STATUS "The libraries for the GLUT package: " ${GLUT_LIBRARIES})
	message("")

	# Now, we look for the 'GLEW' package.	
	find_package(GLEW REQUIRED)
	message(STATUS "The path of the 'include' folder for the GLUT package: " ${GLEW_INCLUDE_DIR})
	message(STATUS "The libraries for the GLEW package: " ${GLEW_LIBRARIES})
	message("")

	# If we arrive here, we compose the final constants.
	set(INCLUDES ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
	set(LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
	add_executable(Example-001-old ../src/main.cpp)

elseif(WIN32 OR CMAKE_HOST_WIN32)

	message(STATUS "We are using Windows")
else ()
	message(FATAL_ERROR "The current platform is not supported")
endif()

# Now, we can finalize the building process.
include_directories(${INCLUDES})
target_link_libraries(Example-001-old ${LIBS})
