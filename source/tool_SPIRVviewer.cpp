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

#include "tool_framework.hpp"
#include "tool_SPIRVviewer.hpp"
#include <algorithm>
#include <string>
#include <fstream>
#include <json/json.h>

using namespace std;

static vector<string> shaderModuleTypes =
{
	"VERTEX",
	"FRAGMENT",
	"GEOMETRY",
	"TESS_CONTROL",
	"TESS_EVALUATION",
	"COMPUTE",
};

static int activeModuleItem = 0;
static int activeDescsetItem = 0;
static int activeDesclayoutItem = 0;
static int activeDescBindingItem = 0;

static ImVec4 favColor = ImVec4(0.067f, 0.765f, 0.941f, 1.0f);

// -------------------------------------------------------- Helpers -----------------------------------------------

template <typename T>
static vector<const char*> CStrList(vector<T> & list)
{
    vector<const char*> list_;
    for (auto& item: list) list_.push_back(item.name.c_str());
    return list_;
}
static vector<const char*> CStrList(vector<std::string>& list)
{
    vector<const char*> list_;
    for (auto& item: list) list_.push_back(item.c_str());
    return list_;
}

static int DisplayConfirmWindow(const char* text)
{
    if (ImGui::BeginPopupModal(text, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::TextColored(ImVec4(0.953f, 0.208f, 0.42f, 1.0f), "%s Are you sure?", text);
        ImGui::Text("This cannot be undone.");
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        if (ImGui::Button("OK", ImVec2(100, 0))) {
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return 1;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(100, 0))) {
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return -1;
        }
        ImGui::EndPopup();
    }
    return 0;
}

static bool displayAboutWindow = false;
static void DisplayAboutWindow(void)
{
    if (ImGui::BeginPopupModal("About VK Pipeline Layout Editor", &displayAboutWindow, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::TextColored(ImVec4(0.067f, 0.765f, 0.941f, 1.0f), "Vulkan Pipeline Layout Editor" 
                           "                                                                                              ");
        ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), "(c) Copyright 2016 UAA Software");
        ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), "Programming by Xi Ma Chen");
        ImGui::Spacing(); ImGui::Spacing();
        ImGui::TextWrapped(
            "Static pipeline layout editor tool for the Vulkan API. Loads & saves from a simple json file format.\n"
            "Quick guide:\n"
        );
        {
            ImGui::Bullet(); 
            ImGui::TextWrapped(
                "A descriptor binding layout describes a single binding for a single shader stage. "
                "For example, a binding layout might represent texture sampler, a uniform buffer object, and so forth."
            );
            ImGui::Bullet(); ImGui::TextWrapped("Descriptor binding layouts are represented as a global list, shared between all sets & pipelines.");
            ImGui::Bullet(); ImGui::TextWrapped(
                "A descriptor set layout describes a collection of descriptor bindings. It may be a good idea to group these by update frequency. "
                "For example, one may have separate sets for per-frame, per-scene, per-camera, per-material and per-object shader data."
            );
            ImGui::Bullet(); ImGui::TextWrapped("A pipeline layout describes a collection of descriptor set layouts.");
        }
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        if (ImGui::Button("OK", ImVec2(100, 0))) {
            displayAboutWindow = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

static void DisplayCombo(const char* title, int *current, vector<const char*>& items, vector<char>& buffer)
{
    size_t totalsz = 0;
    for (auto str : items) totalsz += (strlen(str) + 1);
    buffer.resize(totalsz + 1);
    size_t off = 0;
    for (auto str : items) {
        memcpy(&buffer[off], str, (strlen(str) + 1));
        off += (strlen(str) + 1);
    }
    buffer[off] = '\0';
    ImGui::Combo(title, current, buffer.data());
}

// src: http://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c
inline bool EndsWith(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

const char* shaderTool_t::getWindowTitle()
{
    return "Shader Tool";
}

void shaderTool_t::init(void)
{
	//if the shader binary has already been establish via double clicking in wondows explorer
	if (!binaryPath.empty())
	{
		load(binaryPath);
	}
}

void shaderTool_t::DrawMenu()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("New", NULL, nullptr)) {
			}
			if (ImGui::MenuItem("Open..", NULL, nullptr)) {
				string p;
				if (openDialog(p, "shader.json")) {
					this->load(p);
				}
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Save", NULL, nullptr)) {
				this->save(fileName.c_str());
			}
			if (ImGui::MenuItem("Save As..", NULL, nullptr)) {
				string p = fileName;
				if (saveDialog(p, "shader.json")) {
					this->save(p);
				}
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", NULL, nullptr)) {
				exit(0);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About", NULL, nullptr)) {
				displayAboutWindow = true;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void shaderTool_t::DrawMeta()
{
	ImGui::TextColored(ImVec4(0.067f, 0.765f, 0.941f, 1.0f), "SPIRV-GLSL shader Editor");
	ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), "(c) Copyright 2016 UAA Software");
	ImGui::Spacing(); ImGui::Spacing();
	ImGui::TextWrapped("%s", fileName.c_str());
	ImGui::Spacing(); ImGui::Spacing();
}

void shaderTool_t::DrawShaderTypes()
{
	ImGui::TextColored(favColor, "%s:", "Shader module type");
	switch (shaderModuleType)
	{
	case shaderModuleType_t::vertex:
		ImGui::Text("vertex shader");
		break;
	case shaderModuleType_t::fragment:
		ImGui::Text("fragment sahder");
		break;
	case shaderModuleType_t::geometry:
		ImGui::Text("geometry");
		break;
	case shaderModuleType_t::tessControl:
		ImGui::Text("tesselation control");
		break;
	case shaderModuleType_t::tessEvaluation:
		ImGui::Text("tesselation evaluation");
		break;
	case shaderModuleType_t::compute:
		ImGui::Text("compute");
		break;
	case shaderModuleType_t::kernel:
		ImGui::Text("kernel");
		break;
	case shaderModuleType_t::invalid:
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "invalid shader");
		break;
	default:
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "invalid shader");
		break;
	}
	
	//auto blarg = ImGui::ListBox((string("##") + "Shader Module").c_str(), &activeModuleItem, CStrList(shaderModuleTypes).data(), shaderModuleTypes.size());
}

void shaderTool_t::DrawShaderReflection()
{
	ImGui::BeginChild("reflection info");
	ImGui::TextColored(favColor, "%s:", "Shader reflection info");
	//fill out the reflection info for the shader

	shaderOptions.es;
	shaderOptions.version;
	shaderOptions.fragment.default_float_precision;
	shaderOptions.fragment.default_int_precision;

	ImGui::Text("GLSL Version: %i", shaderOptions.version);
	ImGui::Text((std::string("Uses OpenGL ES: ") + (shaderOptions.es ? "true" : "false")).c_str());
	//ImGui::Text("float precision", shaderOptions.fragment.default_float_precision)

	intPrecision = "integer precision: ";
	floatPrecision = "Floating point precision: ";

	switch (shaderOptions.fragment.default_float_precision)
	{
	case spirv_cross::CompilerGLSL::Options::Highp:
	{
		floatPrecision += "high";
		break;
	}

	case spirv_cross::CompilerGLSL::Options::Mediump:
	{
		floatPrecision += "medium";
		break;
	}

	case spirv_cross::CompilerGLSL::Options::Lowp:
	{
		floatPrecision += "low";
		break;
	}

	default:
	{
		floatPrecision += "N/A";
		break;
	}
	}
	ImGui::Text("%s", floatPrecision.c_str());

	switch (shaderOptions.fragment.default_int_precision)
	{
	case spirv_cross::CompilerGLSL::Options::Highp:
	{
		intPrecision += "high";
		break;
	}

	case spirv_cross::CompilerGLSL::Options::Mediump:
	{
		intPrecision += "medium";
		break;
	}

	case spirv_cross::CompilerGLSL::Options::Lowp:
	{
		intPrecision += "low";
		break;
	}

	default:
	{
		intPrecision += "N/A";
		break;
	}
	}
	ImGui::Text("%s", intPrecision.c_str());


	//atomic counters
	ImGui::Text("Atomics Info");
	for (unsigned int atomicIndex = 0; atomicIndex < shaderResources.atomic_counters.size(); atomicIndex++)
	{
		ImGui::Text("Atomic #%i:", atomicIndex);
		ImGui::Text("Atomic ID: %i", shaderResources.atomic_counters[atomicIndex].id);
		ImGui::Text("Atomic Name: %s", shaderResources.atomic_counters[atomicIndex].name.c_str());
		ImGui::Text("Atomic type ID: %i", shaderResources.atomic_counters[atomicIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	//push constant buffers // look this up!
	ImGui::Text("Push constant buffers");
	for (unsigned int pushIndex = 0; pushIndex < shaderResources.push_constant_buffers.size(); pushIndex++)
	{
		ImGui::Text("Push constant #%i:", pushIndex);
		ImGui::Text("Push constant ID: %i", shaderResources.push_constant_buffers[pushIndex].id);
		ImGui::Text("Push constant Name: %s", shaderResources.push_constant_buffers[pushIndex].name.c_str());
		ImGui::Text("Push constant type ID: %i", shaderResources.push_constant_buffers[pushIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	//sampled images
	ImGui::Text("Sampled images");
	for (unsigned int sampleIndex = 0; sampleIndex < shaderResources.sampled_images.size(); sampleIndex++)
	{
		ImGui::Text("Sample #%i:", sampleIndex);
		ImGui::Text("Sample ID: %i", shaderResources.sampled_images[sampleIndex].id);
		ImGui::Text("Sample Name: %s", shaderResources.sampled_images[sampleIndex].name.c_str());
		ImGui::Text("Sample type ID: %i", shaderResources.sampled_images[sampleIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	//shader stage inputs
	ImGui::Text("Shader stage inputs");
	for (unsigned int inputIndex = 0; inputIndex < shaderResources.stage_inputs.size(); inputIndex++)
	{
		ImGui::Text("Input #%i:", inputIndex);
		ImGui::Text("Input ID: %i", shaderResources.stage_inputs[inputIndex].id);
		ImGui::Text("Input Name: %s", shaderResources.stage_inputs[inputIndex].name.c_str());
		ImGui::Text("Input type ID: %i", shaderResources.stage_inputs[inputIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	//shader stage outputs
	ImGui::Text("Stage outputs");
	for (unsigned int outputIndex = 0; outputIndex < shaderResources.stage_outputs.size(); outputIndex++)
	{
		ImGui::Text("Output #%i:", outputIndex);
		ImGui::Text("Output ID: %i", shaderResources.stage_outputs[outputIndex].id);
		ImGui::Text("Output Name: %s", shaderResources.stage_outputs[outputIndex].name.c_str());
		ImGui::Text("Output type ID: %i", shaderResources.stage_outputs[outputIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	//shader storage buffers
	ImGui::Text("Storage buffers");
	for (unsigned int storageIndex = 0; storageIndex < shaderResources.storage_buffers.size(); storageIndex++)
	{
		ImGui::Text("Storage buffer #%i:", storageIndex);
		ImGui::Text("Storage buffer ID: %i", shaderResources.storage_buffers[storageIndex].id);
		ImGui::Text("Storage buffer Name: %s", shaderResources.storage_buffers[storageIndex].name.c_str());
		ImGui::Text("Storage buffer type ID: %i", shaderResources.storage_buffers[storageIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	//shader storage images? //need to look that one up 
	//i think these can be written to (similar to render targets)
	shaderResources.storage_images;
	ImGui::Text("Storage images");
	for (unsigned int imageIndex = 0; imageIndex < shaderResources.storage_images.size(); imageIndex++)
	{
		ImGui::Text("Storage image #%i:", imageIndex);
		ImGui::Text("Storage image ID: %i", shaderResources.storage_images[imageIndex].id);
		ImGui::Text("Storage image Name: %s", shaderResources.storage_images[imageIndex].name.c_str());
		ImGui::Text("Storage image type ID: %i", shaderResources.storage_images[imageIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	//shader sub pass inputs
	shaderResources.subpass_inputs;
	ImGui::Text("Sub pass inputs");
	for (unsigned int subpassIndex = 0; subpassIndex < shaderResources.storage_images.size(); subpassIndex++)
	{
		ImGui::Text("Sub pass input #%i:", subpassIndex);
		ImGui::Text("Sub pass input ID: %i", shaderResources.subpass_inputs[subpassIndex].id);
		ImGui::Text("Sub pass input Name: %s", shaderResources.subpass_inputs[subpassIndex].name.c_str());
		ImGui::Text("Sub pass input type ID: %i", shaderResources.subpass_inputs[subpassIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();
	
	//shader uniform buffers
	shaderResources.uniform_buffers;
	ImGui::Text("Uniform buffers");
	for (unsigned int uniformIndex = 0; uniformIndex < shaderResources.storage_images.size(); uniformIndex++)
	{
		ImGui::Text("Uniform buffer #%i:", uniformIndex);
		ImGui::Text("Uniform buffer ID: %i", shaderResources.uniform_buffers[uniformIndex].id);
		ImGui::Text("Uniform buffer Name: %s", shaderResources.uniform_buffers[uniformIndex].name.c_str());
		ImGui::Text("Uniform buffer type ID: %i", shaderResources.uniform_buffers[uniformIndex].type_id);
		ImGui::Spacing();
	}
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::EndChild(); //reflection info
}

void shaderTool_t::DrawSPIRV(ImVec2 dimensions)
{
	ImGui::BeginChild("SPIRV", dimensions, true);
	ImGui::SetWindowSize("SPIRV", dimensions);
	ImGui::TextColored(favColor, "%s:", "GLSL source code");
	ImGui::Separator();
	//add open in in editor button and open in vim button
	ImGui::InputTextMultiline("##", (char*)SPIRVSource.c_str(), SPIRVSource.size() * sizeof(char), ImVec2(dimensions.x, dimensions.y - 100), ImGuiInputTextFlags_ReadOnly);
	ImGui::Button("open in editor"); //if clicked, open the source code in a editor
	ImGui::Button("open in vim"); //if clicked, open the source code in vim

	ImGui::EndChild();
	ImGui::SameLine();
}

void shaderTool_t::DrawGLSL(ImVec2 dimensions)
{
	ImGui::BeginChild("GLSL", dimensions, true);
	ImGui::TextColored(favColor, "%s:", "SPIRV source code");
	ImGui::Separator();
	ImGui::InputTextMultiline("##", (char*)glslSource.c_str(), glslSource.size() * sizeof(char), ImVec2(dimensions.x, dimensions.y - 100), ImGuiInputTextFlags_ReadOnly);

	ImGui::Button("open in editor"); //if clicked, open the source code in a editor
	ImGui::Button("open in vim"); //if clicked, open the source code in vim
	ImGui::EndChild();
}

void shaderTool_t::render(int screenWidth, int screenHeight)
{
    ImGui::SetNextWindowPos(ImVec2(4, 4));
    ImGui::SetNextWindowSize(ImVec2(screenWidth - 8, screenHeight - 8));


    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_HorizontalScrollbar;
    ImGui::Begin("Main window", nullptr, windowFlags);
    {
        

        // --------------------------- Menu bar ---------------------------------
		DrawMenu();
       
        if (displayAboutWindow) {
            ImGui::OpenPopup("About SPIRV-GLSL Editor");
            DisplayAboutWindow();
        }

        // --------------------------- First column : info and pipeline layouts ---------------------------------

        ImGui::BeginChild("Column1", ImVec2(350, 0), true);
		DrawMeta();
		ImGui::Separator();
		DrawShaderTypes();
		ImGui::Separator();
		//add reflection info to the bottom
		DrawShaderReflection();
		ImGui::EndChild(); // column 1
		ImGui::SameLine();

		//get the size of the window the halve it for the children
		ImGui::BeginChild("test", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize);
		ImVec2 windowDimensions = ImGui::GetWindowSize();
		ImVec2 newDimensions = ImVec2(windowDimensions.x / 2, windowDimensions.y - 10);

        // --------------------------- Second column : SPIRV ---------------------------------
		DrawSPIRV(newDimensions);
        // --------------------------- Third column : GLSL ---------------------------------
		DrawGLSL(newDimensions);

		ImGui::EndChild(); // tests
       
    }

	ImGui::End();
}

void shaderTool_t::save(std::string fileName)
{
    if (fileName.length() <= 0) return;
    if (!EndsWith(fileName, ".vkpipeline.json")) {
        if (EndsWith(fileName, ".vkpipeline")) {
            fileName += ".json";
        } else {
            fileName += ".vkpipeline.json";
        }
    }

/*
    Json::Value value;
    value["num_layouts"] = m_layouts.size();  
    for (auto& playout: m_layouts) {
        Json::Value vplayout;
        vplayout["name"] = playout.name;
        auto setIdx = 0;
        for (auto& dset : playout.descsets) {
            Json::Value vdset;
            vdset["set_index"] = setIdx++;
            for (auto& dl : dset.dlayouts) {
                Json::Value vdl = this->findDescLayoutByPtr(dl);
                vdset["desc_layouts"].append(vdl);
            }
            vplayout["desc_sets"].append(vdset);
        }
        value["layouts"].append(vplayout);
    }
    value["num_sets"] = m_dsets.size();  
    for (auto& dset: m_dsets) {
        Json::Value vdset;
        vdset = dset;
        value["sets"].append(vdset);
    }
    value["num_bindings"] = m_dlayouts.size();  
    for (auto& binding: m_dlayouts) {
        Json::Value vbinding;
        vbinding["name"] = binding->name;
        vbinding["type"] = binding->typeIdx;
        vbinding["typeName"] = shaderModuleTypes[binding->typeIdx];
        vbinding["data"] = binding->data;
        vbinding["comment"] = binding->comment;
        vbinding["stageFlagBits"] = binding->stageFlagBits;
        value["bindings"].append(vbinding);
    }

    ofstream ofs;
    ofs.open(fileName.c_str(), std::ofstream::out);
    Json::StyledStreamWriter writer;
    writer.write(ofs, value);
    ofs.close();

    m_filename = fileName;*/
}

void shaderTool_t::load(std::string fileName)
{
	if (fileName.length() <= 0)
	{
		return; //if filename is empty, return. dont bother loading that
	}

	spirv_cross::CompilerGLSL glsl(std::move(ReadSPIRVFile(fileName.c_str())));
	shaderResources = glsl.get_shader_resources();
	shaderOptions = glsl.get_options();
	shaderOptions.vulkan_semantics = true;
	glsl.set_options(shaderOptions);

	//spirv_cross::CompilerGLSL::execution.model;
	glslSource = glsl.compile();

	if (glslSource.empty())
	{
		//if the SPIRV binary cannot be compiled then quit here
		return;
	}

	SPIRVSource = DetermineShaderModuleType(glslSource);

}

std::string shaderTool_t::DetermineShaderModuleType(std::string shaderSource)
{
	shaderc::Compiler compiler;
	shaderc::CompileOptions options;

	for (unsigned int moduleIter = 0; moduleIter < 5; moduleIter++)
	{
		switch (moduleIter)
		{
		case shaderc_shader_kind::shaderc_glsl_vertex_shader:
		{
			//if successful, return the result. else break until default.
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderSource.c_str(), shaderSource.size(), shaderc_shader_kind::shaderc_glsl_vertex_shader, "vertex", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				shaderModuleType = shaderModuleType_t::vertex;
				return std::string(result.cbegin(), result.cend());
			}
			break;
		}

		case shaderc_shader_kind::shaderc_glsl_fragment_shader:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderSource.c_str(), shaderSource.size(), shaderc_shader_kind::shaderc_glsl_fragment_shader, "fragment", options);
			if(result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				shaderModuleType = shaderModuleType_t::fragment;
				return std::string(result.cbegin(), result.cend());
			}
			break;
		}

		case shaderc_shader_kind::shaderc_glsl_compute_shader:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderSource.c_str(), shaderSource.size(), shaderc_shader_kind::shaderc_glsl_compute_shader, "compute", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				shaderModuleType = shaderModuleType_t::compute;
				return std::string(result.cbegin(), result.cend());
			}
			break;
		}

		case shaderc_shader_kind::shaderc_glsl_geometry_shader:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderSource.c_str(), shaderSource.size(), shaderc_shader_kind::shaderc_glsl_geometry_shader, "geometry", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				shaderModuleType = shaderModuleType_t::geometry;
				return std::string(result.cbegin(), result.cend());
			}
			break;
		}

		case shaderc_shader_kind::shaderc_glsl_tess_control_shader:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderSource.c_str(), shaderSource.size(), shaderc_shader_kind::shaderc_glsl_tess_control_shader, "tess control", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				shaderModuleType = shaderModuleType_t::tessControl;
				return std::string(result.cbegin(), result.cend());
			}
			break;
		}

		case shaderc_shader_kind::shaderc_glsl_tess_evaluation_shader:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderSource.c_str(), shaderSource.size(), shaderc_shader_kind::shaderc_glsl_tess_evaluation_shader, "tess evaluation", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				shaderModuleType = shaderModuleType_t::tessEvaluation;
				return std::string(result.cbegin(), result.cend());
			}
			break;
		}

		default:
		{
			//return empty string if the shader type cannot be determined
			shaderModuleType = shaderModuleType_t::invalid;
			return nullptr;
			
		}
		}

		
	}
}

std::vector<uint32_t> shaderTool_t::ReadSPIRVFile(const char* fileName)
{
	FILE* file = fopen(fileName, "r+");
	if (file == nullptr)
	{
		return std::vector<uint32_t>();
	}

	fseek(file, 0, SEEK_END);
	long int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned int* inBuffer = (unsigned int*)malloc(size);
	int bytesRead = fread(inBuffer, sizeof(unsigned int), size, file);

	fclose(file);

	std::vector<uint32_t> outBuffer;

	for (int bufferIter = 0; bufferIter < bytesRead; bufferIter++)
	{
		outBuffer.push_back(inBuffer[bufferIter]);
	}
	return outBuffer;
}