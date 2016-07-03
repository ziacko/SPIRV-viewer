#include <windows.h>
#include <stdio.h>
#include <ShlObj.h>
#include <string>

void SetRegistry(HKEY keyHandle, const char* variable, const char* value)
{
	HKEY key;
	char currentValue[MAX_PATH];
	DWORD type;
	DWORD size = sizeof(currentValue);

	int keyVal = RegGetValue(keyHandle, variable, NULL, RRF_RT_ANY, &type, currentValue, &size);
	bool didntExist = keyVal == ERROR_FILE_NOT_FOUND;

	if (keyVal != ERROR_SUCCESS && !didntExist)
	{
		printf("RegGetValue(%s): %s \n", variable, strerror(keyVal));
	}

	if (!didntExist)
	{
		if (type != REG_SZ)
		{
			printf("RegGetValue(%s) found type unhandled %d \n", variable, type);
		}

		if (!strcmp(currentValue, value))
		{
			printf("RegSet(\"%s\" \"%s\" ): already correct \n", variable, value);
			return;
		}
	}

	DWORD disposition;
	keyVal = RegCreateKeyEx(keyHandle, variable, NULL, NULL, NULL, KEY_ALL_ACCESS, NULL, &key, &disposition);
	if (keyVal != ERROR_SUCCESS)
	{
		printf("RegSetValueEx( %s ): %s \n", variable, strerror(keyVal));
	}

	if (didntExist)
	{
		printf("RegSet(%s): set to \"%s\" \n", variable, value);
	}
	else
	{
		printf("RegSet(%s): changed \"%s\" to \"%s\" \n", variable, currentValue, value);
	}
	RegCloseKey(key);
}

void SetupAssociation()
{
	//get the path of THIS exe. for this trick to work the Assoc exe MUST be in the same folder as the SPIRV viewer exe
	char stringBuffer[MAX_PATH];
	GetModuleFileName(NULL, stringBuffer, MAX_PATH);
	std::string filePath = stringBuffer;
	//remove the filename. I just want to path
	auto position = filePath.rfind('\\');
	if (position != std::string::npos && (position + 1) != std::string::npos)
	{
		filePath.erase(position + 1);
	}
	//add in the RIGHT file name
	filePath += "SPIRV_Viewer.exe";
	filePath += " \"%1\"";
	SetRegistry(HKEY_CURRENT_USER, "Software\\Classes\\.UUASoftware.SPIRV_Viewer.v1\\shell\\open\\command", filePath.c_str());
	SetRegistry(HKEY_CURRENT_USER, "Software\\Classes\\.spv", "UUASoftware.SPIRV_Viewer.v1");
	SetRegistry(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.spv", NULL);
	SetRegistry(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.spv\\OpenWithProgids", "SPIRV_shader_binary");
	SetRegistry(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.spv\\OpenWithProgids", "spv_auto_file");
																							  //SetRegistry(HKEY_CURRENT_USER, "Software\\Classes\\PercievedType", "SPIRV");
	//SetRegistry(HKEY_CURRENT_USER, "Software\\Classes\\SPIRV_Viewer.1", "SPIRV_Viewer");
	//SetRegistry(HKEY_CURRENT_USER, "Software\\Classes\\SPIRV_Viewer.1\\Shell\\Open\\Command", (filePath).c_str());
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL); //essentially refresh the registry
}

int main()
{
	SetupAssociation();
	return 0;
}