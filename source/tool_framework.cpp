#include "tool_framework.hpp"
#include <nfd.h>

ToolFramework::ToolFramework()
{
}

ToolFramework::~ToolFramework()
{
}

const char* ToolFramework::getWindowTitle(void)
{
    return "VK ToolFramework";
}

void ToolFramework::init(void)
{
}

void ToolFramework::render(int screenWidth, int screenHeight)
{
}

bool ToolFramework::openDialog(std::string& out, const char* filter)
{
    nfdchar_t *outPath = nullptr;
    auto res = NFD_OpenDialog( filter, NULL, &outPath );
    if (res == NFD_OKAY) {
        out = outPath;
        free(outPath);
        return true;
    }
    return false;
}

bool ToolFramework::saveDialog(std::string& out, const char* filter)
{
    nfdchar_t *outPath = nullptr;
    auto res = NFD_SaveDialog( filter, nullptr, &outPath );
    if (res == NFD_OKAY) {
        out = outPath;
        free(outPath);
        return true;
    }
    return false;
}