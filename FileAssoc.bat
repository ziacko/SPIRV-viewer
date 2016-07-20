rem set __COMPAT_LAYER=RunAsInvoker
reg add "HKCU\Software\Classes\spv_auto_file\shell" /ve /f
reg add "HKCU\Software\Classes\spv_auto_file\shell\open" /ve /d "open with SPIRV viewer" /f
reg add "HKCU\Software\Classes\spv_auto_file\shell\open\command" /ve /d "\"%~dp0\SPIRV_Viewer.exe\" \"%%1\"" /f

reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.spv" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.spv\OpenWithList" /v "a" /d "SPIRV_Viewer.exe" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.spv\OpenWithList" /v "MRUList" /d "a" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.spv\OpenWithProgids" /v "SPIRV_shader_binary" /d hex(0): /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.spv\OpenWithProgids" /v "spv_auto_file" /d hex(0): /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.spv\UserChoice" /v "Hash" /d "aXQjgjSSe/Q=" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.spv\UserChoice" /v "ProgId" /d "Applications\\SPIRV_Viewer.exe" /f

:: and now for the massive copy-paste job haha

reg add "HKCU\Software\Classes\vspv_auto_file\shell" /ve /f
reg add "HKCU\Software\Classes\vspv_auto_file\shell\open" /ve /d "open with SPIRV viewer" /f
reg add "HKCU\Software\Classes\vspv_auto_file\shell\open\command" /ve /d "\"%~dp0\SPIRV_Viewer.exe\" \"%%1\"" /f

reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.vspv" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.vspv\OpenWithList" /v "a" /d "SPIRV_Viewer.exe" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.vspv\OpenWithList" /v "MRUList" /d "a" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.vspv\OpenWithProgids" /v "SPIRV_shader_binary" /d hex(0): /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.vspv\OpenWithProgids" /v "vspv_auto_file" /d hex(0): /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.vspv\UserChoice" /v "Hash" /d "aXQjgjSSe/Q=" /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.vspv\UserChoice" /v "ProgId" /d "Applications\\SPIRV_Viewer.exe" /f

pause