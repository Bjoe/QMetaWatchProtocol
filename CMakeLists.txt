cmake_minimum_required(VERSION 2.8.11)

project(QMetaWatchManagerProtocol)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" CACHE PATH "cmake modul path") 
include(BuildUtil)

# The version number.
set (Project_VERSION_MAJOR 0)
set (Project_VERSION_MINOR 1)
set (Project_VERSION_PATCH 0)
set (PROJECT_VERSION ${Project_VERSION_MAJOR}.${Project_VERSION_MINOR}.${Project_VERSION_PATCH})

# activate C++ 11
if(${BLACKBERRY})
  add_definitions(-Wc,-std=c++0x)
else(${BLACKBERRY})
  add_definitions(-std=c++11)
endif(${BLACKBERRY})


# http://www.cmake.org/Wiki/CMake/Tutorials/How_to_create_a_ProjectConfig.cmake_file
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/QMWProtocol)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# QML debuggen
#add_definitions(-DQT_QML_DEBUG)
# and set environment
# QML_COMPILER_DUMP=1
# QML_DISABLE_OPTIMIZER=1
# argument:
# $ executable -qmljsdebugger=port:3768,block

#SET(ENV{PKG_CONFIG_PATH} "foo/bar/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
# find_package(PkgConfig)
# pkg_check_modules(FOO foo)
# include_directories(${FOO_INCLUDE_DIRS})
# link_directories(${FOO_LIBRARY_DIRS})
# target_link_libraries(${FOO_LDFLAGS})
if(${BLACKBERRY})
  set(Qt4 TRUE)
endif(${BLACKBERRY})

if(${Qt4})
  if(${BLACKBERRY})
    set(QT_QMAKE_EXECUTABLE ${BLACKBERRY_TOOLCHAIN_ROOT}/usr/bin/qmake)
    find_package(BBSystem REQUIRED)
  else({${BLACKBERRY})
    find_package(Qt4 4.8 REQUIRED QtCore)
  endif(${BLACKBERRY})
  include(${QT_USE_FILE})
else(${Qt4})
  # cmake example from http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html
  # Find the QtWidgets library
  find_package(Qt5Core REQUIRED)
endif(${Qt4})

find_package(Boost 1.5 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

if(${DOC})
    find_doxygen()
endif(${DOC})

add_subdirectory(src)

if(${TEST})
    # The following are required to uses CTest, Dart and the Cdash dashboard
    enable_testing(true)
    include(CTest)
    add_subdirectory(tests)
endif(${TEST})

# Add all targets to the build-tree export set
export(TARGETS qmwprotocol
  FILE "${PROJECT_BINARY_DIR}/QMWProtocolTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE QMWProtocol)



##################################################################
# Create the xxxxxxConfig.cmake and xxxxxxConfigVersion.cmake files

#-----------------------------------------------------------------
# ... for the build tree
set(CONF_INCLUDE_DIRS 
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_BINARY_DIR}"
)
configure_file(
  "QMWProtocolConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/QMWProtocolConfig.cmake" @ONLY
)

#-----------------------------------------------------------------
# ... for the install tree
file(RELATIVE_PATH 
  REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
  "${INSTALL_INCLUDE_DIR}"
)
set(CONF_INCLUDE_DIRS 
  "\${QMWPROTOCOL_CMAKE_DIR}/${REL_INCLUDE_DIR}"
)
configure_file(
  "QMWProtocolConfig.cmake.in"
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/QMWProtocolConfig.cmake" @ONLY
)

#-----------------------------------------------------------------
# ... for both
configure_file(
  "QMWProtocolConfigVersion.cmake.in"
  "${PROJECT_BINARY_DIR}/QMWProtocolConfigVersion.cmake" @ONLY
)
 

##################################################################
# Install the xxxxxxConfig.cmake and xxxxxxConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/QMWProtocolConfig.cmake"
  "${PROJECT_BINARY_DIR}/QMWProtocolConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
install(EXPORT QMWProtocolTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
