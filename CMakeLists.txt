cmake_minimum_required (VERSION 2.6)
project (SPIRV_Viewer C CXX)

set(PROJECT_LABEL "SPIRV_Viewer")

find_package(OpenGL REQUIRED)

set (COMMON_OUTPUT_DIR "./bin")
set (DEBUG_OUTPUT_DIR "./bin/Debug/")
set (RELEASE_OUTPUT_DIR "./bin/Release/")

set (INCLUDE_DIR "./include")
set (COMMON_INCLUDE_DIR "./lib/include")
set (IMGUI_INCLUDE_DIR "./lib/include/imgui")
set (SHADERC_INCLUDE_DIR "./lib/shaderc/libshaderc/include")
set (GLFW_INCLUDE_DIR "./lib/include/glfw")

set (SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/")
set (LIB_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/src/")

set (IMGUI_SOURCES "${IMGUI_INCLUDE_DIR}/imgui.cpp" "${SOURCES_DIR}/imgui_draw.cpp" "${SOURCES_DIR}/imgui_demo.cpp" "${SOURCES_DIR}/imgui_impl_glfw_gl3")

if(WIN32)
set(NFD_SOURCES "${LIB_SOURCES_DIR}nfd_common.c" "${LIB_SOURCES_DIR}/nfd_win.cpp")
elseif(UNIX)
#set(NFD_SOURCES "${NFD_SOURCES}" "${LIB_SOURCES_DIR}/") //add linux nfd later
endif()

set (SPIRV_SOURCES "${LIB_SOURCES_DIR}/spirv_cpp" "${LIB_SOURCES_DIR}/spirv_cross" "${LIB_SOURCES_DIR}/spirv_glsl" "${LIB_SOURCES_DIR}/spirv_msl")
set (GLFW_SOURCES "./lib/include/GL/gl3w.c")

set ( SOURCES "./source/main.cpp" "./source/tool_framework.cpp" "./source/tool_SPIRVviewer")

include_directories("${INCLUDE_DIR}")
include_directories("${COMMON_INCLUDE_DIR}")
include_directories("${IMGUI_INCLUDE_DIR}")
include_directories("${SHADERC_INCLUDE_DIR}")
include_directories("${COMMON_INCLUDE_DIR}/cross")
include_directories("${COMMON_INCLUDE_DIR}/GL")
include_directories("${GLFW_INCLUDE_DIR}")

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/find")

set (HEADERS "${INCLUDE_DIR}/tool_framework.hpp" "${INCLUDE_DIR}/resource.h" "${INCLUDE_DIR}/tool_SPIRVviewer.hpp" "${INCLUDE_DIR}/imgui_impl_glfw_gl3")

set (LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory("${LIB_DIR}/shaderc" EXCLUDE_FROM_ALL)
link_directories(${LIB_DIR})

add_executable(SPIRV_Viewer ${SOURCES} ${IMGUI_SOURCES} ${NFD_SOURCES} ${SPIRV_SOURCES} ${GLFW_SOURCES} ${HEADERS})

set (LIBS shaderc jsoncppd glfw3)
target_link_libraries(SPIRV_Viewer ${LIBS} ${OPENGL_LIBRARIES})
set_property(TARGET SPIRV_Viewer PROPERTY OUTPUT_NAME "SPIRV_Viewer")
