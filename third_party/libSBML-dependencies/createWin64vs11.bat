@echo off
REM ensure visual studio is in the path
if "%INCLUDE%"=="" call vs11.bat
if not exist %BASE_DIR%\build mkdir %BASE_DIR%\build
if not exist %BASE_DIR%\dist mkdir %BASE_DIR%\dist
cd build
mkdir vs10_64
cd vs10_64
cmake -G "Visual Studio 11 Win64" -DWITH_STATIC_RUNTIME:BOOL=ON ..\..
devenv libsbml_dependencies.sln /build RelWithDebInfo
cpack -G ZIP -C RelWithDebInfo 
copy "libSBML Dependencies-1.0.0-b1-win64.zip" ..\..\dist