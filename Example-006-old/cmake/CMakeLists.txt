########################################################################################################################################################
# David Canino (canino.david@gmail.com)
#
# Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
#
# Last update: January 2018
#                                                                    
# CMakeLists.txt - the settings for constructing the makefile of interest for the 'Example-006 (Old Mode)'
########################################################################################################################################################
cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
project(Example-006-old LANGUAGES CXX)
message("")
message(STATUS "We assume that the 'GLU' and the 'OpenGL' packages are stored in the same package (like in the recent distributions).")
set(CMAKE_WARN_DEPRECATED,FALSE)
set(CMAKE_ERROR_DEPRECATED,FALSE)
if(APPLE OR CMAKE_HOST_APPLE)

	# We are using a Macintosh Apple (MacOSX) platform. First, we look for the 'OpenGL' package.
	set(CMAKE_CXX_FLAGS "-Wno-deprecated")
	message("")
	find_package(OpenGL REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR} /.)
	message(STATUS "The library file(s) for the OpenGL package: " ${OPENGL_LIBRARIES} .)
	message("")

	# Now, we look for the 'GLUT' package.
	find_package(GLUT REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR} /.)
	message(STATUS "The library file(s) for the 'GLUT' package: " ${GLUT_LIBRARIES} .)
	message("")

	# Finally, we look for the 'GLEW' package.	
	find_package(GLEW REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR} /.)
	message(STATUS "The library file(s) for the 'GLEW' package: " ${GLEW_LIBRARIES} .)

elseif(UNIX OR CMAKE_HOST_UNIX)

	# We are using a Unix-like platform, e.g., any GNU/Linux distribution. First, we look for the 'OpenGL' package.
	set(CMAKE_CXX_FLAGS "-Wno-deprecated")
	message("")
	find_package(OpenGL REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR} /.)
	message(STATUS "The library file(s) for the OpenGL package: " ${OPENGL_LIBRARIES} .)
	message("")

	# Now, we look for the 'GLUT' package.
	find_package(GLUT REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR} /.)
	message(STATUS "The library file(s) for the 'GLUT' package: " ${GLUT_LIBRARIES} .)
	message("")

	# Finally, we look for the 'GLEW' package.	
	find_package(GLEW REQUIRED)
	message(STATUS "The path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR} /.)
	message(STATUS "The library file(s) for the 'GLEW' package: " ${GLEW_LIBRARIES} .)

elseif(WIN32 OR CMAKE_HOST_WIN32)

	# We are using any Microsoft Windows platform. In this case, we must look for the standard OpenGL, GLUT, and GLEW packages.
	# If we cannot be found in the system, then we exploit their custom 32-bit versions in the ‘depends’ folder, except for the OpenGL package!
	# First, we look for the 'OpenGL' package. 
	message("")
	find_package(OpenGL)
	if(OPENGL_INCLUDE_DIR)
		
		# Here, it is possible to find the 'include' path for the 'OpenGL' package (standard version).
		message(STATUS "The (standard) path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR} /.)

	else()
		
		# Here, it is not possible to find the 'include' path for the 'OpenGL' package, and we use its custom version in the ‘depends’ folder.
		set(OPENGL_INCLUDE_DIR "../../depends/include")
		message(STATUS "The (custom) path of the 'include' folder for the 'OpenGL' package: " ${OPENGL_INCLUDE_DIR} /.)

	endif()
	if(OPENGL_LIBRARIES)
		
		# Here, it is possible to find the 'lib' path for the 'OpenGL' package (standard version).
		message(STATUS "The (standard) library file(s) for the OpenGL package: " ${OPENGL_LIBRARIES} .)

	else()
		
		# Here, it is not possible to find the 'lib' path for the 'OpenGL' package, and it must be added to the system necessarily.
		# NOTE: this situation is not common in most platforms.
		message(FATAL_ERROR "Please, add the 'OpenGL' library to your system!")

	endif()
	
	# Now, we look for the 'GLUT' package.
	message("")	
	find_package(GLUT)
	if(GLUT_INCLUDE_DIR)
		
		# Here, it is possible to find the 'include' path for the 'GLUT' package (standard version).
		message(STATUS "The (standard) path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR} /.)

	else()
		
		# Here, it is not possible to find the 'include' path for the 'GLUT' package, and we use its custom version in the ‘depends’ folder.
		set(GLUT_INCLUDE_DIR "../../depends/include")
		message(STATUS "The (custom) path of the 'include' folder for the 'GLUT' package: " ${GLUT_INCLUDE_DIR} /.)

	endif()
	if(GLUT_LIBRARIES)
		
		# Here, it is possible to find the 'lib' path for the 'GLUT' package (standard version).
		message(STATUS "The (standard) library file(s) for the 'GLUT' package: " ${GLUT_LIBRARIES} .)

	else()
		
		# Here, it is not possible to find the 'lib' path for the 'GLUT' package, and we use its custom version in the ‘depends’ folder.
		set(GLUT_LIBRARIES "../../../depends/lib/freeglut")
		message(STATUS "The (custom) library file(s) for the 'GLUT' package: " ${GLUT_LIBRARIES} .)

	endif()

	# Now, we look for the ‘GLEW’ package.
	message("")	
	find_package(GLEW)
	if(GLEW_INCLUDE_DIR)
		
		# Here, it is possible to find the 'include' path for the 'GLEW' package (standard version).
		message(STATUS "The (standard) path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR} /.)

	else()
		
		# Here, it is not possible to find the 'include' path for the 'GLEW' package, and we use its custom version in the ‘depends’ folder.
		set(GLEW_INCLUDE_DIR "../../depends/include")
		message(STATUS "The (custom) path of the 'include' folder for the 'GLEW' package: " ${GLEW_INCLUDE_DIR} .)

	endif()
	if(GLEW_LIBRARIES)
		
		# Here, it is possible to find the 'lib' path for the 'GLEW' package (standard version).
		message(STATUS "The (standard) library file(s) for the 'GLEW' package: " ${GLEW_LIBRARIES} .)
	
	else()
		
		# Here, it is not possible to find the 'lib' path for the 'GLEW' package, and we use its custom version in the ‘depends’ folder.
		set(GLEW_LIBRARIES "../../../depends/lib/glew32")
		message(STATUS "The (custom) library file(s) for the ‘GLEW’ package: " ${GLEW_LIBRARIES} .)
	endif()

else()
	
	# We are using a not supported platform (FATAL ERROR)!
	message(FATAL_ERROR "The current platform is not supported!")

endif()

# If we arrive here, the we can finalize the building process.
# At this point:
#
# 	- the OPENGL_INCLUDE_DIR variable contains the path of the header files, related to the OpenGL package library;
#	- the OPENGL_LIBRARIES variable contains the library file(s) for the OpenGL package library;
#	- the GLUT_INCLUDE_DIR variable contains the path of the header files, related to the GLUT package library;
#	- the GLUT_LIBRARIES variable contains the library file(s) for the GLUT package library;
#	- the GLEW_INCLUDE_DIR variable contains the path of the header files, related to the GLEW package library;
#	- the GLEW_LIBRARIES variable contains the library file(s) for the GLEW package library.
#
# For the sake of the simplicity, we define the following variables:
#
# 	- INCLUDES = OPENGL_INCLUDE_DIR GLUT_INCLUDE_DIR GLEW_INCLUDE_DIR
#	- LIBS = OPENGL_LIBRARIES GLUT_LIBRARIES GLEW_LIBRARIES
message("")
set(INCLUDES ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
set(LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
add_executable(Example-006-old ../src/main.cpp)
include_directories(${INCLUDES})
target_link_libraries(Example-006-old ${LIBS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/.)
