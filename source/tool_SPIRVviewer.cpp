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
static string popupString = "About SPIRV Viewer";

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
    if (ImGui::BeginPopupModal(popupString.c_str(), &displayAboutWindow, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::TextColored(ImVec4(0.067f, 0.765f, 0.941f, 1.0f), "SPIRV Viewer" 
                           "                                                                                              ");
        ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), "(c) Copyright 2016 UAA Software");
        ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), "Programming by Ziyad Barakat");
        ImGui::Spacing(); ImGui::Spacing();
        ImGui::TextWrapped(
			"Static viewing tool for the SPIRV file format. loads SPIRV binary files from disk. \n"
            //"Static pipeline layout editor tool for the Vulkan API. Loads & saves from a simple json file format.\n"
            "Quick guide:\n"
        );
        {
            ImGui::Bullet(); 
            ImGui::TextWrapped(
				"A SPIRV Binary can be decompiled into both GLSL(OpenGL and Vulkan) and SPIRV assembly as well as contain useful reflection information. "
				"For Example, a SPIRV binary file is loaded then is decompiled into Vulkan ready GLSL and SPIRV Assembly in addition to information "
				"regarding shader outputs and uniform buffers." 
				//"A descriptor binding layout describes a single binding for a single shader stage. "
                //"For example, a binding layout might represent texture sampler, a uniform buffer object, and so forth."
            );
            ImGui::Bullet(); 
			//ImGui::TextWrapped("Descriptor binding layouts are represented as a global list, shared between all sets & pipelines.");
			ImGui::TextWrapped("SPIRV information is broken down into GLSL source, SPIRV assembly and reflection information.");
            ImGui::Bullet(); 
			ImGui::TextWrapped(
				"Source code is displayed in a text box with GLSL being in the right box and SPIRV assembly displayed in the left text box. "
				"As for reflection information here is what you can expect to see (in order of appearance): \n"
				"\t- GLSL version\n"
				"\t- Whether OpenGL ES is being used\n"
				"\t- Floating point precision\n"
				"\t- Integer precision\n"
				"\t- Atomics\n"
				"\t- Push constant buffers\n"
				"\t- Sampled images\n"
				"\t- Stage inputs\n"
				"\t- Stage outputs\n"
				"\t- Storage buffers\n"
				"\t- Storage images\n"
				"\t- Sub pass inputs\n"
				"\t- Uniform buffer\n"			
				//"A descriptor set layout describes a collection of descriptor bindings. It may be a good idea to group these by update frequency. "
               // "For example, one may have separate sets for per-frame, per-scene, per-camera, per-material and per-object shader data."
            );
			ImGui::Bullet();
			ImGui::TextWrapped(
				"If you are using a .vpsv file then you can change the active shader by clicking on the shader stage you want to view "
				"which is displayed as a button on the left side under \"shader module type\". \n"
				"Clicking one one of these will change the active binary being shown."
			);
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
	//if the shader binary has already been establish via double clicking in windows explorer
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
			/*if (ImGui::MenuItem("New", NULL, nullptr)) {
			}*/
			if (ImGui::MenuItem("Open..", NULL, nullptr)) {
				string p;
				if (openDialog(p, nullptr)) {
					this->load(p);
				}
			}
			/*ImGui::Separator();
			if (ImGui::MenuItem("Save", NULL, nullptr)) {
				this->save(fileName.c_str());
			}
			if (ImGui::MenuItem("Save As..", NULL, nullptr)) {
				string p = fileName;
				if (saveDialog(p, "shader.json")) {
					this->save(p);
				}
			}*/
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
}

void shaderTool_t::DrawShaderTypes()
{
	if (!shaderModules.empty())
	{
		ImGui::TextColored(favColor, "%s:", "Shader module type");
	}

	//for each module, add a button for the type. if it is clicked, switch to drawing that one
	for (unsigned int moduleIter = 0; moduleIter < shaderModules.size(); moduleIter++)
	{
		switch (shaderModules[moduleIter].moduleType)
		{
		case shaderModule_t::vertex:
		{
			if (ImGui::Button("vertex"))
			{
				currentModule = moduleIter;
			}
			break;
		}

		case shaderModule_t::fragment:
		{
			if (ImGui::Button("fragment"))
			{
				currentModule = moduleIter;
			}
			break;
		}

		case shaderModule_t::geometry:
		{
			if (ImGui::Button("geometry"))
			{
				currentModule = moduleIter;
			}
			break;
		}

		case shaderModule_t::tessControl:
		{
			if (ImGui::Button("tess control"))
			{
				currentModule = moduleIter;
			}
			break;
		}

		case shaderModule_t::tessEvaluation:
		{
			if (ImGui::Button("tess evaluation"))
			{
				currentModule = moduleIter;
			}
			break;
		}

		case shaderModule_t::compute:
		{
			if (ImGui::Button("compute"))
			{
				currentModule = moduleIter;
			}
			break;
		}

		default:
			break;
		}
	}
	
	/*switch (shaderModuleType)
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
	}*/
	
	//auto blarg = ImGui::ListBox((string("##") + "Shader Module").c_str(), &activeModuleItem, CStrList(shaderModuleTypes).data(), shaderModuleTypes.size());
}

void shaderTool_t::DrawShaderReflection()
{
	if (!shaderModules.empty())
	{
		ImGui::BeginChild("reflection info");
		ImGui::TextColored(favColor, "%s:", "Shader reflection info");
		//fill out the reflection info for the shader

		ImGui::Text("GLSL Version: %i", shaderModules[currentModule].shaderOptions.version);
		ImGui::Text((std::string("Uses OpenGL ES: ") + (shaderModules[currentModule].shaderOptions.es ? "true" : "false")).c_str());
		//ImGui::Text("float precision", shaderOptions.fragment.default_float_precision)

		shaderModules[currentModule].intPrecision = "integer precision: ";
		shaderModules[currentModule].floatPrecision = "Floating point precision: ";

		switch (shaderModules[currentModule].shaderOptions.fragment.default_float_precision)
		{
		case spirv_cross::CompilerGLSL::Options::Highp:
		{
			shaderModules[currentModule].floatPrecision += "high";
			break;
		}

		case spirv_cross::CompilerGLSL::Options::Mediump:
		{
			shaderModules[currentModule].floatPrecision += "medium";
			break;
		}

		case spirv_cross::CompilerGLSL::Options::Lowp:
		{
			shaderModules[currentModule].floatPrecision += "low";
			break;
		}

		default:
		{
			shaderModules[currentModule].floatPrecision += "N/A";
			break;
		}
		}
		ImGui::Text("%s", shaderModules[currentModule].floatPrecision.c_str());

		switch (shaderModules[currentModule].shaderOptions.fragment.default_int_precision)
		{
		case spirv_cross::CompilerGLSL::Options::Highp:
		{
			shaderModules[currentModule].intPrecision += "high";
			break;
		}

		case spirv_cross::CompilerGLSL::Options::Mediump:
		{
			shaderModules[currentModule].intPrecision += "medium";
			break;
		}

		case spirv_cross::CompilerGLSL::Options::Lowp:
		{
			shaderModules[currentModule].intPrecision += "low";
			break;
		}

		default:
		{
			shaderModules[currentModule].intPrecision += "N/A";
			break;
		}
		}
		ImGui::Text("%s", shaderModules[currentModule].intPrecision.c_str());
		ImGui::Separator();
		ImGui::Spacing();


		//atomic counters
		ImGui::TextColored(favColor, "Atomics Info:");
		for (unsigned int atomicIndex = 0; atomicIndex < shaderModules[currentModule].shaderResources.atomic_counters.size(); atomicIndex++)
		{
			ImGui::Text("Atomic %i", atomicIndex);
			ImGui::Text("Atomic ID: %i", shaderModules[currentModule].shaderResources.atomic_counters[atomicIndex].id);
			ImGui::Text("Atomic name: %s", shaderModules[currentModule].shaderResources.atomic_counters[atomicIndex].name.c_str());
			ImGui::Text("Atomic type ID: %i", shaderModules[currentModule].shaderResources.atomic_counters[atomicIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//push constant buffers // look this up!
		ImGui::TextColored(favColor, "Push constant buffers:");
		for (unsigned int pushIndex = 0; pushIndex < shaderModules[currentModule].shaderResources.push_constant_buffers.size(); pushIndex++)
		{
			ImGui::Text("Push constant %i", pushIndex);
			ImGui::Text("Push constant ID: %i", shaderModules[currentModule].shaderResources.push_constant_buffers[pushIndex].id);
			ImGui::Text("Push constant name: %s", shaderModules[currentModule].shaderResources.push_constant_buffers[pushIndex].name.c_str());
			ImGui::Text("Push constant type ID: %i", shaderModules[currentModule].shaderResources.push_constant_buffers[pushIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//sampled images
		ImGui::TextColored(favColor, "Sampled images:");
		for (unsigned int sampleIndex = 0; sampleIndex < shaderModules[currentModule].shaderResources.sampled_images.size(); sampleIndex++)
		{
			ImGui::Text("Sample %i", sampleIndex);
			ImGui::Text("Sample ID: %i", shaderModules[currentModule].shaderResources.sampled_images[sampleIndex].id);
			ImGui::Text("Sample name: %s", shaderModules[currentModule].shaderResources.sampled_images[sampleIndex].name.c_str());
			ImGui::Text("Sample type ID: %i", shaderModules[currentModule].shaderResources.sampled_images[sampleIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//shader stage inputs
		ImGui::TextColored(favColor, "Stage inputs:");
		for (unsigned int inputIndex = 0; inputIndex < shaderModules[currentModule].shaderResources.stage_inputs.size(); inputIndex++)
		{
			ImGui::Text("Input %i", inputIndex);
			ImGui::Text("Input ID: %i", shaderModules[currentModule].shaderResources.stage_inputs[inputIndex].id);
			ImGui::Text("Input name: %s", shaderModules[currentModule].shaderResources.stage_inputs[inputIndex].name.c_str());
			ImGui::Text("Input type ID: %i", shaderModules[currentModule].shaderResources.stage_inputs[inputIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//shader stage outputs
		ImGui::TextColored(favColor, "Stage outputs:");
		for (unsigned int outputIndex = 0; outputIndex < shaderModules[currentModule].shaderResources.stage_outputs.size(); outputIndex++)
		{
			ImGui::Text("Output %i", outputIndex);
			ImGui::Text("Output ID: %i", shaderModules[currentModule].shaderResources.stage_outputs[outputIndex].id);
			ImGui::Text("Output name: %s", shaderModules[currentModule].shaderResources.stage_outputs[outputIndex].name.c_str());
			ImGui::Text("Output type ID: %i", shaderModules[currentModule].shaderResources.stage_outputs[outputIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//shader storage buffers
		ImGui::TextColored(favColor, "Storage buffers:");
		for (unsigned int storageIndex = 0; storageIndex < shaderModules[currentModule].shaderResources.storage_buffers.size(); storageIndex++)
		{
			ImGui::Text("Storage buffer %i", storageIndex);
			ImGui::Text("Storage buffer ID: %i", shaderModules[currentModule].shaderResources.storage_buffers[storageIndex].id);
			ImGui::Text("Storage buffer name: %s", shaderModules[currentModule].shaderResources.storage_buffers[storageIndex].name.c_str());
			ImGui::Text("Storage buffer type ID: %i", shaderModules[currentModule].shaderResources.storage_buffers[storageIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//shader storage images? //need to look that one up 
		//i think these can be written to (similar to render targets)
		shaderModules[currentModule].shaderResources.storage_images;
		ImGui::TextColored(favColor, "Storage images:");
		for (unsigned int imageIndex = 0; imageIndex < shaderModules[currentModule].shaderResources.storage_images.size(); imageIndex++)
		{
			ImGui::Text("Storage image %i", imageIndex);
			ImGui::Text("Storage image ID: %i", shaderModules[currentModule].shaderResources.storage_images[imageIndex].id);
			ImGui::Text("Storage image name: %s", shaderModules[currentModule].shaderResources.storage_images[imageIndex].name.c_str());
			ImGui::Text("Storage image type ID: %i", shaderModules[currentModule].shaderResources.storage_images[imageIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//shader sub pass inputs
		shaderModules[currentModule].shaderResources.subpass_inputs;
		ImGui::TextColored(favColor, "Sub pass inputs:");
		for (unsigned int subpassIndex = 0; subpassIndex < shaderModules[currentModule].shaderResources.storage_images.size(); subpassIndex++)
		{
			ImGui::Text("Sub pass input %i", subpassIndex);
			ImGui::Text("Sub pass input ID: %i", shaderModules[currentModule].shaderResources.subpass_inputs[subpassIndex].id);
			ImGui::Text("Sub pass input name: %s", shaderModules[currentModule].shaderResources.subpass_inputs[subpassIndex].name.c_str());
			ImGui::Text("Sub pass input type ID: %i", shaderModules[currentModule].shaderResources.subpass_inputs[subpassIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		//shader uniform buffers
		shaderModules[currentModule].shaderResources.uniform_buffers;
		ImGui::TextColored(favColor, "Uniform buffers:");
		for (unsigned int uniformIndex = 0; uniformIndex < shaderModules[currentModule].shaderResources.storage_images.size(); uniformIndex++)
		{
			ImGui::Text("Uniform buffer %i", uniformIndex);
			ImGui::Text("Uniform buffer ID: %i", shaderModules[currentModule].shaderResources.uniform_buffers[uniformIndex].id);
			ImGui::Text("Uniform buffer name: %s", shaderModules[currentModule].shaderResources.uniform_buffers[uniformIndex].name.c_str());
			ImGui::Text("Uniform buffer type ID: %i", shaderModules[currentModule].shaderResources.uniform_buffers[uniformIndex].type_id);
			ImGui::Spacing();
		}
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::EndChild(); //reflection info
	}
}

void shaderTool_t::DrawSPIRV(ImVec2 dimensions)
{
	if (!shaderModules.empty())
	{
		ImGui::BeginChild("SPIRV", dimensions, true, ImGuiWindowFlags_NoScrollbar);
		ImGui::SetWindowSize("SPIRV", dimensions);
		ImGui::SetScrollX(20.0f);
		//ImGui::SetScrollY(10.0f);
		ImGui::TextColored(favColor, "%s:", "\t SPIRV source code");
		ImGui::Separator();
		//add open in in editor button and open in vim button
		ImGui::InputTextMultiline("##", (char*)shaderModules[currentModule].spirvSource.c_str(), shaderModules[currentModule].spirvSource.size() * sizeof(char), dimensions, ImGuiInputTextFlags_ReadOnly);

		ImGui::EndChild();
		ImGui::SameLine();
	}
}

void shaderTool_t::DrawGLSL(ImVec2 dimensions)
{
	if (!shaderModules.empty())
	{
		ImGui::BeginChild("GLSL", dimensions, true, ImGuiWindowFlags_NoScrollbar);
		ImGui::SetScrollX(20.0f);
		
		//ImGui::SetScrollY(10.0f);
		ImGui::TextColored(favColor, "%s:", "\t GLSL source code");
		ImGui::Separator();
		ImGui::InputTextMultiline("##", (char*)shaderModules[currentModule].glslSource.c_str(), shaderModules[currentModule].glslSource.size() * sizeof(char), dimensions, ImGuiInputTextFlags_ReadOnly);
		
		ImGui::EndChild();
	}
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
		if (displayAboutWindow) 
		{
			ImGui::OpenPopup(popupString.c_str());
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
		ImGui::BeginChild("test", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
		ImVec2 windowDimensions = ImGui::GetWindowSize();
		ImVec2 newDimensions = ImVec2(windowDimensions.x / 2, windowDimensions.y);
		ImGui::SetScrollX(20.0f);
		// --------------------------- Second column : SPIRV ---------------------------------
		DrawSPIRV(newDimensions);
		// --------------------------- Third column : GLSL ---------------------------------
		DrawGLSL(newDimensions);

		ImGui::EndChild(); // tests*/
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
	shaderModules.clear();
	if (fileName.length() <= 0)
	{
		return; //if filename is empty, return. dont bother loading that
	}

	//get the extension name of the filename
	auto position = fileName.find_last_of(".");
	std::string extensionType = fileName.substr(position + 1);
	if (!extensionType.compare("spv"))
	{
		//if it's just a regular SPIRV file then continue as normal
		shaderModule_t module = {};
		spirv_cross::CompilerGLSL glsl(std::move(ReadSPIRVFile(fileName.c_str())));
		module.shaderResources = glsl.get_shader_resources();
		module.shaderOptions = glsl.get_options();
		module.shaderOptions.vulkan_semantics = true;
		glsl.set_options(module.shaderOptions);
		module.glslSource = glsl.compile();

		if (module.glslSource.empty())
		{
			//if the SPIRV binary cannot be compiled to GLSL then quit here
			return;
		}
		module.glslSource += "\n";

		DetermineShaderModuleType(module, glsl.execution.model);
		shaderModules.push_back(module);
	}

	else
	{
		//if not then loop for each binary
		ReadVectorSPIRVFile(fileName.c_str());

		for (unsigned int moduleIter = 0; moduleIter < shaderModules.size(); moduleIter++)
		{
			spirv_cross::CompilerGLSL glsl(std::move(shaderModules[moduleIter].binaryList));
			shaderModules[moduleIter].shaderResources = glsl.get_shader_resources();
			shaderModules[moduleIter].shaderOptions = glsl.get_options();
			shaderModules[moduleIter].shaderOptions.vulkan_semantics = true;
			glsl.set_options(shaderModules[moduleIter].shaderOptions);

			//spirv_cross::CompilerGLSL::execution.model;
			shaderModules[moduleIter].glslSource = glsl.compile();

			if (shaderModules[moduleIter].glslSource.empty())
			{
				//if the SPIRV binary cannot be compiled then quit here
				return;
			}

			shaderModules[moduleIter].glslSource += "\n";
			shaderc::Compiler compiler;
			shaderc::CompileOptions options;

			switch (shaderModules[moduleIter].moduleType)
			{
				case shaderModule_t::vertex:
				{
					shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderModules[moduleIter].glslSource.c_str(), shaderModules[moduleIter].glslSource.size(), shaderc_shader_kind::shaderc_glsl_vertex_shader, "vertex", options);
					if (result.GetCompilationStatus() == shaderc_compilation_status_success)
					{
						shaderModules[moduleIter].spirvSource = std::string(result.cbegin(), result.cend());
						shaderModules[moduleIter].spirvSource += "\n";
					}

					else
					{
						shaderModules[moduleIter].spirvSource = result.GetErrorMessage();
						shaderModules[moduleIter].spirvSource += "\n";
					}
					break;
				}
				case shaderModule_t::fragment:
				{
					shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderModules[moduleIter].glslSource.c_str(), shaderModules[moduleIter].glslSource.size(), shaderc_shader_kind::shaderc_glsl_fragment_shader, "fragment", options);
					if (result.GetCompilationStatus() == shaderc_compilation_status_success)
					{
						shaderModules[moduleIter].spirvSource = std::string(result.cbegin(), result.cend());
						shaderModules[moduleIter].spirvSource += "\n";
					}

					else
					{
						shaderModules[moduleIter].spirvSource = result.GetErrorMessage();
						shaderModules[moduleIter].spirvSource += "\n";
					}
					break;
				}
				case shaderModule_t::geometry:
				{
					shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderModules[moduleIter].glslSource.c_str(), shaderModules[moduleIter].glslSource.size(), shaderc_shader_kind::shaderc_glsl_geometry_shader, "geometry", options);
					if (result.GetCompilationStatus() == shaderc_compilation_status_success)
					{
						shaderModules[moduleIter].spirvSource = std::string(result.cbegin(), result.cend());
						shaderModules[moduleIter].spirvSource += "\n";
					}

					else
					{
						shaderModules[moduleIter].spirvSource = result.GetErrorMessage();
						shaderModules[moduleIter].spirvSource += "\n";
					}
					break;
				}
				case shaderModule_t::tessControl:
				{
					shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderModules[moduleIter].glslSource.c_str(), shaderModules[moduleIter].glslSource.size(), shaderc_shader_kind::shaderc_glsl_tess_control_shader, "tessellation control", options);
					if (result.GetCompilationStatus() == shaderc_compilation_status_success)
					{
						shaderModules[moduleIter].spirvSource = std::string(result.cbegin(), result.cend());
						shaderModules[moduleIter].spirvSource += "\n";
					}

					else
					{
						shaderModules[moduleIter].spirvSource = result.GetErrorMessage();
						shaderModules[moduleIter].spirvSource += "\n";
					}
					break;
				}
				case shaderModule_t::tessEvaluation:
				{
					shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderModules[moduleIter].glslSource.c_str(), shaderModules[moduleIter].glslSource.size(), shaderc_shader_kind::shaderc_glsl_tess_evaluation_shader, "tessellation evaluation", options);
					if (result.GetCompilationStatus() == shaderc_compilation_status_success)
					{
						shaderModules[moduleIter].spirvSource = std::string(result.cbegin(), result.cend());
						shaderModules[moduleIter].spirvSource += "\n";
					}

					else
					{
						shaderModules[moduleIter].spirvSource = result.GetErrorMessage();
						shaderModules[moduleIter].spirvSource += "\n";
					}
					break;
				}

				case shaderModule_t::compute:
				{
					shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(shaderModules[moduleIter].glslSource.c_str(), shaderModules[moduleIter].glslSource.size(), shaderc_shader_kind::shaderc_glsl_compute_shader, "compute", options);
					if (result.GetCompilationStatus() == shaderc_compilation_status_success)
					{
						shaderModules[moduleIter].spirvSource = std::string(result.cbegin(), result.cend());
						shaderModules[moduleIter].spirvSource += "\n";
					}

					else
					{
						shaderModules[moduleIter].spirvSource = result.GetErrorMessage();
						shaderModules[moduleIter].spirvSource += "\n";
					}
					break;
				}

				default:
				{
					shaderModules[moduleIter].moduleType = shaderModule_t::invalid;
					break;
				}
			}			
		}
	}
}

bool shaderTool_t::CheckShaderType(shaderModule_t& module, shaderc::AssemblyCompilationResult& result)
{
	return false;
}

void shaderTool_t::DetermineShaderModuleType(shaderModule_t& module, spv::ExecutionModel model)
{
	shaderc::Compiler compiler;
	shaderc::CompileOptions options;
	//if successful, return the result. else break until default.
	switch (model)
	{
	case spv::ExecutionModel::ExecutionModelVertex:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(module.glslSource.c_str(), module.glslSource.size(), shaderc_shader_kind::shaderc_glsl_vertex_shader, "vertex", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				module.moduleType = shaderModule_t::moduleType_t::vertex;
				module.spirvSource = std::string(result.cbegin(), result.cend());
			}

			else
			{
				module.spirvSource = result.GetErrorMessage();
			}
			break;
		}

		case spv::ExecutionModel::ExecutionModelFragment:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(module.glslSource.c_str(), module.glslSource.size(), shaderc_shader_kind::shaderc_glsl_fragment_shader, "fragment", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				module.moduleType = shaderModule_t::moduleType_t::fragment;
				module.spirvSource = std::string(result.cbegin(), result.cend());
			}

			else
			{
				module.spirvSource = result.GetErrorMessage();
			}
			break;
		}

		case spv::ExecutionModel::ExecutionModelGLCompute:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(module.glslSource.c_str(), module.glslSource.size(), shaderc_shader_kind::shaderc_glsl_compute_shader, "compute", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				module.moduleType = shaderModule_t::moduleType_t::compute;
				module.spirvSource = std::string(result.cbegin(), result.cend());
			}

			else
			{
				module.spirvSource = result.GetErrorMessage();
			}
			break;
		}

		case spv::ExecutionModel::ExecutionModelGeometry:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(module.glslSource.c_str(), module.glslSource.size(), shaderc_shader_kind::shaderc_glsl_geometry_shader, "geometry", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				module.moduleType = shaderModule_t::moduleType_t::geometry;
				module.spirvSource = std::string(result.cbegin(), result.cend());
			}

			else
			{
				module.spirvSource = result.GetErrorMessage();
			}
			break;
		}

		case spv::ExecutionModel::ExecutionModelTessellationControl:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(module.glslSource.c_str(), module.glslSource.size(), shaderc_shader_kind::shaderc_glsl_tess_control_shader, "tess control", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				module.moduleType = shaderModule_t::moduleType_t::tessControl;
				module.spirvSource = std::string(result.cbegin(), result.cend());
			}

			else
			{
				module.spirvSource = result.GetErrorMessage();
			}
			break;
		}

		case spv::ExecutionModel::ExecutionModelTessellationEvaluation:
		{
			shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(module.glslSource.c_str(), module.glslSource.size(), shaderc_shader_kind::shaderc_glsl_tess_evaluation_shader, "tess eval", options);
			if (result.GetCompilationStatus() == shaderc_compilation_status_success)
			{
				module.moduleType = shaderModule_t::moduleType_t::tessEvaluation;
				module.spirvSource = std::string(result.cbegin(), result.cend());
			}

			else
			{
				module.spirvSource = result.GetErrorMessage();
			}
			break;
		}

		default:
		{
			//return empty string if the shader type cannot be determined
			module.moduleType = shaderModule_t::moduleType_t::invalid;
			return;
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

void shaderTool_t::ReadVectorSPIRVFile(const char* fileName)
{
	//get the number of binaries
	FILE* file = fopen(fileName, "rb");

	//move the cursor to the end
	fseek(file, 0, SEEK_END);
	unsigned int totalSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned int numInts = totalSize / sizeof(uint32_t);
	
	//get the total size of the file
	//move the cursor back to the beginning

	unsigned int magicalBullshit = 0;
	unsigned int position = 0;
	unsigned int numBinaries = 0;
	position = fread(&magicalBullshit, sizeof(uint32_t), 1, file);

	if (magicalBullshit == 0x5be1273b)
	{
		position += fread(&numBinaries, sizeof(uint32_t), 1, file);

		for (int binaryIiter = 0; binaryIiter < numBinaries; binaryIiter++)
		{
			unsigned int stage = 0;
			position += fread(&stage, sizeof(uint32_t), 1, file);

			//using stage we can determine the shader type without consulting shaderc
			unsigned int binarySize = 0;
			position += fread(&binarySize, sizeof(uint32_t), 1, file);

			std::vector<uint32_t> outBuffer;
			uint32_t numInts = binarySize / sizeof(uint32_t);

			position = 0;
			for (int bufferIter = 0; (position * sizeof(uint32_t)) < binarySize; bufferIter++)
			{
				unsigned int buffer = 0;
				position += fread(&buffer, sizeof(uint32_t), 1, file);

				if (feof(file))
				{
					//check if end of file was found!
					//printf("eof found ! \n");
					break;
				}

				outBuffer.push_back(buffer);
			}

			/*printf("position (num elements) processed %i \n", position);
			printf("binary size %i \n", binarySize);
			printf("bytes read (32 bit ints) %i \n", position * sizeof(uint32_t));*/
			//if everything is all good create a shader module and push it back :)
			//binaryList.push_back(outBuffer);
			shaderModule_t module = {};
			module.binaryList = std::move(outBuffer);
			module.moduleType = (shaderModule_t::moduleType_t)stage;			
			shaderModules.push_back(module);
		}
	}
}