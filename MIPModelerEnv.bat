rem @echo off

REM for RELEASE set OPTION=release
REM for debug set OPTION=debug
REM OPTION must be defined by calling script
REM Or OPTION is defined by user in interactive mode (detected by void option)

if /i "%OPTION%" == "" (
ECHO A build mode is required. please enter release or debug
set /p OPTION=release or debug?:
)


set extension=

if "%OPTION%" == "debug" ( 
set extension=_debug
)

if not exist setDepsPath.bat (
   echo command file setDepsPath.bat missing in directory
   echo You have to create one by copying setDepsPath.bat.exemple to setDepsPath.bat
   echo Then change the PEGASE_ROOT variable in setDepsPath.bat
   EXIT /B 1
)

call setDepsPath

:: necessary for Cplex and Eigen

set DEPS_HOME=%PEGASE_ROOT%/Deps

rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rem Path for Qt - for compilation using jom !
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
call %~dp0\QtEnv.bat

set PEGASE_MPC_HOME=%~dp0

echo %PEGASE_MPC_HOME%
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rem Path for MILP Solvers
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
call %PEGASE_MPC_HOME%\MIPSolverInterface\OsiEnv.bat
call %PEGASE_MPC_HOME%\MIPSolverInterface\MosekEnv.bat
call %PEGASE_MPC_HOME%\MIPSolverInterface\CplexEnv.bat

echo %PATH%
