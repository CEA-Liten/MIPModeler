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
