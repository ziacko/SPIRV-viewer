# CMake generated Testfile for 
# Source directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party
# Build directory: C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(glslang-testsuite "bash" "runtests")
  set_tests_properties(glslang-testsuite PROPERTIES  WORKING_DIRECTORY "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/test-glslang/Debug")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(glslang-testsuite "bash" "runtests")
  set_tests_properties(glslang-testsuite PROPERTIES  WORKING_DIRECTORY "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/test-glslang/Release")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(glslang-testsuite "bash" "runtests")
  set_tests_properties(glslang-testsuite PROPERTIES  WORKING_DIRECTORY "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/test-glslang/MinSizeRel")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(glslang-testsuite "bash" "runtests")
  set_tests_properties(glslang-testsuite PROPERTIES  WORKING_DIRECTORY "C:/Users/ziyad/Documents/SPIRV-viewer/lib/shaderc/third_party/test-glslang/RelWithDebInfo")
else()
  add_test(glslang-testsuite NOT_AVAILABLE)
endif()
subdirs(googletest)
subdirs(glslang)
subdirs(spirv-tools)
