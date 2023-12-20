rem XCOPY documentation
rem https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/xcopy
rem https://ss64.com/nt/xcopy.html

rem xcopy s:\ z:\* /S /Y /D
rem S will copy all subfolders and files within them Y prevents any overwrite prompts D essentially copies anything newer than what is already in the destination
rem '*' at the end of the destination to surpress directory/file prompt

set sourceDir=..\Libraries\
set targetDir=..\

xcopy "%sourceDir%assimp\Release\x86\assimp-vc140-mt.dll" "%targetDir%assimp-vc140-mt.dll*" /Y
xcopy "%sourceDir%freetype2\x86\freetype.dll" "%targetDir%freetype.dll*" /Y
xcopy "%sourceDir%glew\glew32d.dll" "%targetDir%glew32d.dll*" /Y
xcopy "%sourceDir%glfw\glfw3.dll" "%targetDir%glfw3.dll*" /Y
xcopy "%sourceDir%OpenAL\libs\Win32\OpenAL32.dll" "%targetDir%OpenAL32.dll*" /Y
rem xcopy "%sourceDir%OpenAL\libs\soft_oal.dll" "%targetDir%soft_oal.dll*" /Y
xcopy "%sourceDir%pThreads\lib\x86\pthreadVC2.dll" "%targetDir%pthreadVC2.dll*" /Y
xcopy "%sourceDir%RakNet\RakNet_VS2008_DLL_Debug_Win32.dll" "%targetDir%RakNet_VS2008_DLL_Debug_Win32.dll*" /Y
xcopy "%sourceDir%RakNet\RakNet_VS2008_DLL_Release_Win32.dll" "%targetDir%RakNet_VS2008_DLL_Release_Win32.dll*" /Y