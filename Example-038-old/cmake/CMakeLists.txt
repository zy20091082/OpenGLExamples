########################################################################################################################################################
# David Canino (canino.david@gmail.com)
#
# Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
#
# Last update: January 2017
#                                                                    
# This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
#                                                                           
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for
# more details.
#
# CMakeLists.txt - the settings for constructing the makefile of interest for the 'Example-038 (Old Mode)'
########################################################################################################################################################

cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
project(Example-038-old LANGUAGES CXX)
message("")
message(STATUS "We assume that the 'GLU' and the 'OpenGL' packages are stored in the same package (like in the recent distributions)")
if(APPLE OR CMAKE_HOST_APPLE)

	# We are using a Macintosh Apple (MacOSX) platform. First, we look for the 'OpenGL' package
	message("")
	find_package(OpenGL REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR})
	message(STATUS "The library file(s) for the OpenGL package: " ${OPENGL_LIBRARIES})
	message("")

	# Now, we look for the 'GLUT' package.
	find_package(GLUT REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR})
	message(STATUS "The library file(s) for the 'GLUT' package: " ${GLUT_LIBRARIES})
	message("")

	# Now, we look for the 'GLEW' package.	
	find_package(GLEW REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR})
	message(STATUS "The library file(s) for the 'GLEW' package: " ${GLEW_LIBRARIES})

elseif(UNIX OR CMAKE_HOST_UNIX)

	# We are using a Unix-like platform, maybe the GNU/Linux. First, we look for the 'OpenGL' package
	message("")
	find_package(OpenGL REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR})
	message(STATUS "The libraries for the 'OpenGL' package: " ${OPENGL_LIBRARIES})
	message("")

	# Now, we look for the 'GLUT' package.
	find_package(GLUT REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR})
	message(STATUS "The libraries for the 'GLUT' package: " ${GLUT_LIBRARIES})
	message("")

	# Now, we look for the 'GLEW' package.	
	find_package(GLEW REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR})
	message(STATUS "The libraries for the 'GLEW' package: " ${GLEW_LIBRARIES})

elseif(WIN32 OR CMAKE_HOST_WIN32)

	# We are using a Microsoft Windows platform. First, we look for the 'OpenGL' package.
	message("")
	find_package(OpenGL)
	if(OPENGL_INCLUDE_DIR)
		
		# It is possible to find the 'include' path for the 'OpenGL' package.
		message(STATUS "The (standard) path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR})
	else()
		
		# It is not possible to find the 'include' path for the 'OpenGL' package.
		set(OPENGL_INCLUDE_DIR "../../depends/include/")
		message(STATUS "The (custom) path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR})
	endif()
	if(OPENGL_LIBRARIES)
		
		# It is possible to find the 'lib' path for the 'OpenGL' package.
		message(STATUS "The (standard) libraries for the 'OpenGL' package: " ${OPENGL_LIBRARIES})
	else()
		
		# It is not possible to find the 'lib' path for the 'OpenGL' package.
		message(FATAL_ERROR "Please, add the 'OpenGL' library to your system")
	endif()

	# Now, we look for the 'GLUT' package.
	message("")	
	find_package(GLUT)
	if(GLUT_INCLUDE_DIR)
		
		# It is possible to find the 'include' path for the 'GLUT' package.
		message(STATUS "The (standard) path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR})
	else()
		
		# It is not possible to find the 'include' path for the 'GLUT' package.
		set(GLUT_INCLUDE_DIR "../../depends/include/")
		message(STATUS "The (custom) path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR})
	endif()
	if(GLUT_LIBRARIES)
		
		# It is possible to find the 'lib' path for the 'GLUT' package.
		message(STATUS "The (standard) libraries for the 'GLUT' package: " ${GLUT_LIBRARIES})
	else()
		
		# It is not possible to find the 'lib' path for the 'GLUT' package.
		set(GLUT_LIBRARIES "../../../depends/lib/freeglut")
		message(STATUS "The (custom) libraries for the 'GLUT' package: " ${GLUT_LIBRARIES})
	endif()

	# Now, we look for the 'Glew' package.
	message("")	
	find_package(GLEW)
	if(GLEW_INCLUDE_DIR)
		
		# It is possible to find the 'include' path for the 'GLEW' package.
		message(STATUS "The (standard) path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR})
	else()
		
		# It is not possible to find the 'include' path for the 'GLEW' package.
		set(GLEW_INCLUDE_DIR "../../depends/include/")
		message(STATUS "The (custom) path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR})
	endif()
	if(GLEW_LIBRARY!=GLEW_LIBRARY-NOTFOUND)
		
		# It is possible to find the 'lib' path for the 'GLEW' package.
		message(STATUS "The (standard) libraries for the 'GLEW' package: " ${GLEW_LIBRARY})
	else()
		
		# It is not possible to find the 'lib' path for the 'GLEW' package.
		set(GLEW_LIBRARY "../../../depends/lib/glew32")
		set(GLEW_LIBRARIES ${GLEW_LIBRARY})
		message(STATUS "The (custom) library for the 'GLEW' package: " ${GLEW_LIBRARY})
	endif()
else ()
	message(FATAL_ERROR "The current platform is not supported")
endif()

# If we arrive here, we compose the final constants, and finalize the building process.
message("")
set(INCLUDES ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
set(LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
add_executable(Example-038-old ../src/main.cpp)
include_directories(${INCLUDES})
target_link_libraries(Example-038-old ${LIBS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
