cmake_minimum_required(VERSION 3.4)

project(
  "ViennaTestProject"
  VERSION 0.0.1)

add_definitions(-DVIENNARAY_VERSION=${PROJECT_VERSION})

include(GNUInstallDirs)

# c++17 for inline constexpr variables
SET(CMAKE_CXX_STANDARD "17")

# set default build type
SET(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# tell VS to export all symbols to its dll files
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE CACHE BOOL "Export all symbols")
endif()


# # Check for VTK
# ###################
# find_package(VTK QUIET)
# if (VTK_FOUND)
#   message (STATUS "VTK_VERSION: ${VTK_VERSION}")
#   include(${VTK_USE_FILE})
# endif()

# Specify general include directory
################
include_directories( ${CMAKE_SOURCE_DIR}/src/ )

# Specify that the output executable is placed in the root build directory
################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Specify that the libraries are placed in the root build directory
################
set(LIBRARY_OUTPUT_PATH    ${CMAKE_SOURCE_DIR}/lib/${PROJECT_NAME})
link_directories(${LIBRARY_OUTPUT_PATH})

# Find prerequisites
####################
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(pybind11/include/pybind11)
include_directories( ${CMAKE_SOURCE_DIR}/src/ )


add_subdirectory(pybind11)


# Building Module 
######################
set(SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pybind11/pyModuleA.cpp
  )

pybind11_add_module(ModuleA ${SRC})

# Building Module with VTK dependency
######################
if (VTK_FOUND)
  message (STATUS "VTK_VERSION: ${VTK_VERSION}")
  include(${VTK_USE_FILE})

  set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pybind11/pyVTKModule.cpp
    )

  pybind11_add_module(VTKModule ${SRC})
  target_link_libraries(VTKModule PRIVATE ${VTK_LIBRARIES})

endif() # vtk dependencies


#Building Docs
##############
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  # note the option ALL which allows to build the docs together with the application
  add_custom_target( doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
