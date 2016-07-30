# Install script for directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SPIRV_Viewer")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/spirv-tools" TYPE FILE FILES "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/include/spirv-tools/libspirv.h")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/external/cmake_install.cmake")
  include("C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/source/cmake_install.cmake")
  include("C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/tools/cmake_install.cmake")
  include("C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/test/cmake_install.cmake")

endif()

