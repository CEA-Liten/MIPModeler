cd /D %~dp0 

REM to switch from debug to optim
rem set OPTION=release
rem set OPTION=debug

set OPTION=%1
if "%OPTION%" == "" set /p OPTION=debug or release expected 

if not "%OPTION%"=="debug" if not "%OPTION%"=="release" goto error_option 

REM Do we need to Set path for Visual CPP compiler
echo %PATH% | findstr "Visual" > file.txt

(Call :notEmpty file.txt && (
    Echo the file is not empty
)) || (
    Echo the file is empty
	call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
)
del file.txt

call MIPModelerEnv_build

call build .\

call %~dp0\ExportBinaries.bat

cd /D %~dp0 

EXIT /B 0

:error_option
echo:
echo Error in script usage. The following arguments are expected:
echo argument #1 OPTION=debug or release

EXIT /B 1

::subroutine
:notEmpty
If %~z1 EQU 0 (Exit /B 1) Else (Exit /B 0)