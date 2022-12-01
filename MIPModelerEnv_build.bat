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

call %MIPMODELER_HOME%\GAMSModeler\GAMSEnv.bat
call %MIPMODELER_HOME%\MIPSolverInterface\MIPCpxSolver\CplexEnv.bat
call %MIPMODELER_HOME%\MIPSolverInterface\MIPMskSolver\MosekEnv.bat

set PATH=%MIPMODELER_HOME%\external\CoinOR\lib\%OPTION%;%PATH%
set PATH=%MIPMODELER_HOME%\lib\%OPTION%;%PATH%
