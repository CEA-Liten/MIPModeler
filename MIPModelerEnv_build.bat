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

if /i "%SOLVER_DEPS%" == "" call setDepsPath

if "%SOLVER_DEPS%" == "" (
   echo command file setDepsPath.bat missing in directory
   echo You have to create one by copying setDepsPath.bat.exemple to setDepsPath.bat
   echo Then change the SOLVER_DEPS and PERSEE_APP variable in setDepsPath.bat
   EXIT /B 1
)

echo " Solver_deps = %SOLVER_DEPS%"

rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rem set MIPModeler solvers environement 
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MIPMODELER_HOME=%~dp0
echo "MIPMODELER_HOME=%MIPMODELER_HOME%"

call %MIPMODELER_HOME%\QtEnv.bat
call %MIPMODELER_HOME%\GAMSModeler\GAMSEnv.bat
call %MIPMODELER_HOME%\MIPSolverInterface\CoinOREnv.bat
call %MIPMODELER_HOME%\MIPSolverInterface\CplexEnv.bat
call %MIPMODELER_HOME%\MIPSolverInterface\MosekEnv.bat

set PATH=%MIPMODELER_HOME%\lib\%OPTION%;%PATH%
