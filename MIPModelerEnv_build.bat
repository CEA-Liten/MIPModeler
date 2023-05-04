rem @echo off

REM for RELEASE set OPTION=release
REM for debug set OPTION=debug
REM OPTION must be defined by calling script
REM Or OPTION is defined by user in interactive mode (detected by void option)

if /i "%OPTION%" == "" (
ECHO A build mode is required. please enter release or debug
set /p OPTION=release or debug:
)

set extension=

if "%OPTION%" == "debug" ( 
set extension=_debug
)

rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rem set MIPModeler solvers environement 
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MIPMODELER_HOME=%~dp0
echo "MIPMODELER_HOME=%MIPMODELER_HOME%"

set NOGAMS=%1
if "%NOGAMS%" == "" set NOGAMS=0
if "%NOGAMS%" == "false" set NOGAMS=0
if "%NOGAMS%" == "true" set NOGAMS=1
set NOCPLEX=%2
if "%NOCPLEX%" == "" set NOCPLEX=0
if "%NOCPLEX%" == "false" set NOCPLEX=0
if "%NOCPLEX%" == "true" set NOCPLEX=1

echo "MIPModeler build Settings are : NOGAMS=%NOGAMS%, NOCPLEX=%NOCPLEX%"

call %MIPMODELER_HOME%\GAMSModeler\GAMSEnv.bat
call %MIPMODELER_HOME%\MIPSolverInterface\MIPCpxSolver\CplexEnv.bat
call %MIPMODELER_HOME%\MIPSolverInterface\MIPMskSolver\MosekEnv.bat

set PATH=%MIPMODELER_HOME%\external\CoinOR\lib\%OPTION%;%PATH%
set PATH=%MIPMODELER_HOME%\lib\%OPTION%;%PATH%
