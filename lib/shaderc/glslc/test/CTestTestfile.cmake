# CMake generated Testfile for 
# Source directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test
# Build directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(glslc_tests "C:/Users/ziyad/AppData/Local/Programs/Python/Python35-32/python.exe" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test/glslc_test_framework.py" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/Debug/glslc.exe" "--test-dir" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(glslc_tests "C:/Users/ziyad/AppData/Local/Programs/Python/Python35-32/python.exe" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test/glslc_test_framework.py" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/Release/glslc.exe" "--test-dir" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(glslc_tests "C:/Users/ziyad/AppData/Local/Programs/Python/Python35-32/python.exe" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test/glslc_test_framework.py" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/MinSizeRel/glslc.exe" "--test-dir" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(glslc_tests "C:/Users/ziyad/AppData/Local/Programs/Python/Python35-32/python.exe" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test/glslc_test_framework.py" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/RelWithDebInfo/glslc.exe" "--test-dir" "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/glslc/test")
else()
  add_test(glslc_tests NOT_AVAILABLE)
endif()
