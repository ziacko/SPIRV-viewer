# SPIRV-viewer
a tool for viewing SPIRV binaries to GLSL and SPIRV assembly as well as reflection data

Static viewing tool for the SPIRV file format. loads SPIRV binary files from disk.

Quick guide:

A SPIRV Binary can be decompiled into both GLSL(OpenGL and Vulkan) and SPIRV assembly as well as contain useful reflection information. For Example, a SPIRV binary file is loaded then is decompiled into Vulkan ready GLSL and SPIRV Assembly in addition to information regarding shader outputs and uniform buffers.



Please note that this library uses a specialized version of shaderc ans SPIRV-cross libraries
