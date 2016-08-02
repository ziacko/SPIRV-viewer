# CMake generated Testfile for 
# Source directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc
# Build directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(glslc_file "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/Debug/glslc_file_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(glslc_file "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/Release/glslc_file_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(glslc_file "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/MinSizeRel/glslc_file_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(glslc_file "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/RelWithDebInfo/glslc_file_test.exe")
else()
  add_test(glslc_file NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(glslc_stage "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/Debug/glslc_stage_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(glslc_stage "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/Release/glslc_stage_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(glslc_stage "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/MinSizeRel/glslc_stage_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(glslc_stage "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/RelWithDebInfo/glslc_stage_test.exe")
else()
  add_test(glslc_stage NOT_AVAILABLE)
endif()
subdirs(test)
