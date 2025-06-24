echo off
set CMAKEPATH=C:/PROGRAM FILES/MICROSOFT VISUAL STUDIO/2022/COMMUNITY/COMMON7/IDE/COMMONEXTENSIONS/MICROSOFT/CMAKE/CMake/bin/
if exist "cmakepath.bat" (	
	call cmakepath.bat
)
echo %CMAKEPATH%

set OPTION=%1
if "%OPTION%"=="" (
	set OPTION=release
)
echo %OPTION%
rem remove build directory
set BUILD_PATH=out/%OPTION% 
if exist %BUILD_PATH%(
	rmdir /s /q "%BUILD_PATH%"
	)
mkdir "%BUILD_PATH%"
set WORKSPACE=%~dp0

rem Generate config
"%CMAKEPATH%/cmake.exe"  -DCMAKE_BUILD_TYPE=%OPTION% -S. -B%BUILD_PATH%

rem build
cd %BUILD_PATH%
"%CMAKEPATH%/cmake.exe" --build . --config %OPTION% 

rem remove previous install directory
set BIN_PATH=%WORKSPACE%/bin/%OPTION%
if exist %BIN_PATH% (
	rmdir /s /q "%BIN_PATH%"
	)

	
rem Install
"%CMAKEPATH%/cmake.exe" --install . --config %OPTION% --prefix %BIN_PATH%

cd %WORKSPACE%
