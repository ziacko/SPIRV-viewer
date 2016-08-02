# CMake generated Testfile for 
# Source directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/test
# Build directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(spirv-tools-UnitSPIRV "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/test/Debug/UnitSPIRV.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(spirv-tools-UnitSPIRV "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/test/Release/UnitSPIRV.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(spirv-tools-UnitSPIRV "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/test/MinSizeRel/UnitSPIRV.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(spirv-tools-UnitSPIRV "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/spirv-tools/test/RelWithDebInfo/UnitSPIRV.exe")
else()
  add_test(spirv-tools-UnitSPIRV NOT_AVAILABLE)
endif()
