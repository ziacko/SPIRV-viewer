/*
 Copyright (c) 2016 UAA Software
 
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SPIRV_VIEWER_
#define SPIRV_VIEWER_

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "tool_framework.hpp"
#include <cross/spirv_glsl.hpp>
#include <cross/spirv_common.hpp>
#include <cross/spirv.hpp>

#include <shaderc/shaderc.hpp>

#define textBoxSize 40960

// -------------------------------------------------------- PipelineLayoutTool -----------------------------------------------

class shaderTool_t : public ToolFramework
{
   // std::vector<PipelineLayout> m_layouts;
    //std::vector< std::unique_ptr<shaderGLSLModule_t> > m_dlayouts;
    //std::vector<std::string> m_dsets;
    std::string fileName = "default.vert.spv";
	std::string glslSource = {};
	std::string SPIRVSource = {};
	spirv_cross::ShaderResources shaderResources = {};
	spirv_cross::CompilerGLSL::Options shaderOptions = {};
	std::string intPrecision;
	std::string floatPrecision;

    // ---------------------- Names list UI helper ----------------------

    int displayNamedList(const char* title, const char* listboxName, const char* objname, const char* abbrev,
                         std::vector<const char*> listItems, int& activeItem, int listSize,
                         char *newNameBuffer, char *renameBuffer, bool *listChanged = nullptr);
	void DrawMenu();
	void DrawMeta();
	void DrawShaderTypes();
	void DrawShaderReflection();
	void DrawSPIRV(ImVec2 dimensions);
	void DrawGLSL(ImVec2 dimensions);

    void save(std::string fileName);
    void load(std::string fileName);

	std::vector<uint32_t> ReadSPIRVFile(const char* fileName);

public:
    const char* getWindowTitle(void) override;
    void init(void) override;
    void render(int screenWidth, int screenHeight) override;
};

#endif //SPIRV_VIEWER_