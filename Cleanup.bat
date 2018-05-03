del /Q /F /S /AH .vs\*
del /Q /F /S x64
rmdir /Q /S .vs
rmdir /Q /S x64

del /Q /F /S /AH Debug
rmdir /Q /S Debug

del /Q /F /S /AH Release
rmdir /Q /S Release

rem cd Test_Game1
rem del /Q /F /S Debug
rem del /Q /F /S x64
rem del /Q /F /S Release
rem rmdir /Q /S Debug
rem rmdir /Q /S x64
rem rmdir /Q /S Release
rem cd ../