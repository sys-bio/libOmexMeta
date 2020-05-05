@echo off
REM ensure visual studio is in the path
if "%INCLUDE%"=="" call vs10.bat

if not exist %BASE_DIR%\build mkdir %BASE_DIR%\build
if not exist %BASE_DIR%\dist mkdir %BASE_DIR%\dist
cd build
mkdir nmake
cd nmake
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DBUILD_SHARED_LIBS:BOOL=OFF -DWITH_STATIC_RUNTIME:BOOL=ON ..\..
nmake
cpack -G ZIP
copy "libSBML Dependencies-1.0.0-b1-win32.zip" ..\..\dist
cd ..\..