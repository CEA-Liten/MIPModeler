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

set HIGHSPATH=%2
if "%HIGHSPATH%"=="" (
	set HIGHSPATH=external/HiGHS
)
echo %HIGHSPATH%
set MIPMODELER_HOME=%~dp0

cd %HIGHSPATH%


rem remove build directory
set BUILD_PATH=out/%OPTION% 
if exist %BUILD_PATH%(
	rmdir /s /q "%BUILD_PATH%"
	)
mkdir "%BUILD_PATH%"

rem Generate config
"%CMAKEPATH%/cmake.exe" -DCMAKE_BUILD_TYPE=%OPTION% -DBUILD_SHARED_LIBS=ON -S. -B%BUILD_PATH%

cd %BUILD_PATH%
rem build
"%CMAKEPATH%/cmake.exe" --build . --config %OPTION% 

rem remove previous install directory
set BIN_PATH=%MIPMODELER_HOME%/external/HiGHS/%OPTION%
if exist %BIN_PATH% (
	rmdir /s /q "%BIN_PATH%"
	)
mkdir /s /q "%BIN_PATH%"	

rem Install
"%CMAKEPATH%/cmake.exe" --install . --config %OPTION% --prefix %BIN_PATH%

cd ..
