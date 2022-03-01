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
rem Root of SVN repo
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
::set DEPS_HOME=%~dp0\..\Deps

set USER_APP_DATA=%LOCALAPPDATA%
echo "Set USER_APP_DATA = %LOCALAPPDATA%"

set PERSEE_HOME=%~dp0
echo "Set PERSEE_HOME = %PERSEE_HOME%"

set PERSEE_DEPS=%PERSEE_APP%\Deps
echo "Set PERSEE_DEPS = %PERSEE_DEPS%"

set SOLVER_DEPS=%PERSEE_DEPS%\External
echo "Set SOLVER_DEPS = %SOLVER_DEPS%"

set PATH=%PERSEE_DEPS%\Openssl\%OPTION%;%PATH%

::if "%PEGASE_ROOT%" == "" goto PERSEE_TREATMENT
::if not "%PEGASE_ROOT%" == "" goto PEGASE_TREATMENT

:PERSEE_TREATMENT
echo "Configure PERSEE_TREATMENT"

call %PERSEE_HOME%\QtEnv.bat
call %PERSEE_DEPS%\QtCsv\1.5%extension%\PegaseQtCsvEnv.bat 
call %PERSEE_DEPS%\GAMSModelerInterfaceLib\GAMSEnv.bat
call %PERSEE_DEPS%\MIPModelerLib\src\MIPModeler\MIPSolverInterface\OsiEnv.bat
call %PERSEE_DEPS%\MIPModelerLib\src\MIPModeler\MIPSolverInterface\MosekEnv.bat
call %PERSEE_DEPS%\MIPModelerLib\src\MIPModeler\MIPSolverInterface\CplexEnv.bat
call %PERSEE_DEPS%\coin-or\osi_0.107_msvc2015\OsiEnv.bat 

set PATH=%PERSEE_HOME%\lib\%OPTION%;%PATH%
set PATH=%PERSEE_DEPS%\PerseeLib\lib\%OPTION%;%PATH%
set PATH=%PERSEE_DEPS%\MIPModelerLib\lib\%OPTION%;%PATH%
set PATH=%PERSEE_DEPS%\GAMSModelerInterfaceLib\lib\%OPTION%;%PATH%

EXIT /B 0
