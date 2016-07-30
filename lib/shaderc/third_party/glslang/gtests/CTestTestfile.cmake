# CMake generated Testfile for 
# Source directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/glslang/gtests
# Build directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/glslang/gtests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(glslang-gtests "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/glslang/gtests/Debug/glslangtests.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(glslang-gtests "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/glslang/gtests/Release/glslangtests.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(glslang-gtests "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/glslang/gtests/MinSizeRel/glslangtests.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(glslang-gtests "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/glslang/gtests/RelWithDebInfo/glslangtests.exe")
else()
  add_test(glslang-gtests NOT_AVAILABLE)
endif()
