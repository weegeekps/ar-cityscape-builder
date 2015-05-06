# CMake file for the AR Cityscape Builder project.
cmake_minimum_required(VERSION 2.6)

project(cityscape_builder)

# Find necessary packages
FIND_PACKAGE(OpenGL)
FIND_PACKAGE(OpenSceneGraph)
FIND_PACKAGE(osg)
FIND_PACKAGE(osgDB)
FIND_PACKAGE(osgGA)
FIND_PACKAGE(osgViewer)
FIND_PACKAGE(osgUtil)
FIND_PACKAGE(OpenThreads)
FIND_PACKAGE(OpenCV REQUIRED)

# Includes
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

# Source Files
file(GLOB cityscape_builder_src)

#add_definitions(-DDEBUG_BOXES)

# Executable
add_executable(cityscape_builder ${cityscape_builder_src}
main.cpp
ARTagNode.h
ARTagNode.cpp
CalibrationParameters.h
CalibrationParameters.cpp
GeometryTypes.h
GeometryTypes.cpp
GLSL_ShaderLoader.h
GLSL_ShaderLoader.cpp
Marker.h
Marker.cpp
MarkerDetector.h
MarkerDetector.cpp
SkyscraperAssetLoader.h
SkyscraperAssetLoader.cpp
VideoRenderer.h
VideoRenderer.cpp
VideoTexCallback.h
VideoTexCallback.cpp)

# Link paths
link_directories(${OPENSCENEGRAPH_LIBRARY_DIR})
link_directories(${OpenCV_LIB_DIR})

IF(NOT CMAKE_CFG_INTDIR)
    SET(CMAKE_CFG_INTDIR "Release")
ENDIF(NOT CMAKE_CFG_INTDIR)

IF(CMAKE_CFG_INTDIR MATCHES "Debug")
	link_directories(${OpenCV_LIB_DIR_DBG})
ELSE(CMAKE_CFG_INTDIR MATCHES "Debug")
	link_directories(${OpenCV_LIB_DIR_OPT})
ENDIF(CMAKE_CFG_INTDIR MATCHES "Debug")


# Add libraries
if(WIN32 AND NOT APPLE)
	set(OSG_LIBS
		optimized ${OSG_LIBRARY}
		optimized ${OSGGA_LIBRARY}
		optimized ${OSGDB_LIBRARY}
		optimized ${OSGVIEWER_LIBRARY}
		optimized ${OSGUTIL_LIBRARY}
		optimized ${OPENTHREADS_LIBRARY}

		debug ${OSG_LIBRARY_DEBUG}
		debug ${OSGGA_LIBRARY_DEBUG}
		debug ${OSGDB_LIBRARY_DEBUG}
		debug ${OSGVIEWER_LIBRARY_DEBUG}
		debug ${OSGUTIL_LIBRARY_DEBUG}
		debug ${OPENTHREADS_LIBRARY_DEBUG}
	)

    target_link_libraries(cityscape_builder ${OPENGL_LIBRARIES} ${OSG_LIBS} ${OpenCV_LIBS} )
else()
	set(OSG_LIBS
		${OSG_LIBRARY}
		${OSGGA_LIBRARY}
		${OSGDB_LIBRARY}
		${OSGVIEWER_LIBRARY}
		${OSGUTIL_LIBRARY}
		${OPENTHREADS_LIBRARY}
	)

    target_link_libraries(cityscape_builder ${OPENGL_LIBRARIES} ${OSG_LIBS} ${OpenCV_LIBS} )
endif()