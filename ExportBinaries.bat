REM for RELEASE set OPTION=release
REM for debug set OPTION=debug
REM OPTION must be defined by calling script
REM Or OPTION is defined by user in interactive mode (detected by void option)

if /i "%OPTION%" == "" (
ECHO A build mode is required. please enter release or debug
set /p OPTION=release or debug?:
)

::if /i "%PEGASE_ROOT%" == "" (
call setDepsPath
::)

cd %~dp0

:: No export to Pegase for Integration branch !

if "%EXPORT_TO_PEGASE%" == "NO" goto persee

set DEPS_HOME=%PEGASE_ROOT%\Deps
set EXPORT_DIR=%DEPS_HOME%\External\MIPModelerLib

set DOC_DIR=%EXPORT_DIR%\doc

copy /Y MIPModelerEnv_build.bat   %EXPORT_DIR%\

rem ---------------------------------------------------------------
rem MIPModeler & MIPSolverInterface *.h, *.lib *.dll, *.pdf, *.bat 
rem ---------------------------------------------------------------
mkdir %EXPORT_DIR%\src\
mkdir %EXPORT_DIR%\doc
mkdir %EXPORT_DIR%\src\MIPModeler\
mkdir %EXPORT_DIR%\src\MIPModeler\MIPModelerCore
mkdir %EXPORT_DIR%\src\MIPModeler\MIPModelerCore\include
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPClpSolver
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCbcSolver
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCpxSolver
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPMskSolver

copy /Y doc\*.pdf 							%EXPORT_DIR%\doc
copy /Y MIPModelerCore\include\*.h 			%EXPORT_DIR%\src\MIPModeler\MIPModelerCore\include
copy /Y MIPSolverInterface\*.bat 			%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface
copy /Y MIPSolverInterface\MIPClpSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPClpSolver
copy /Y MIPSolverInterface\MIPCbcSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCbcSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPMskSolver

mkdir %EXPORT_DIR%\lib
mkdir %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.lib copy /Y lib\%OPTION%\MIPModeler.lib     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.dll copy /Y lib\%OPTION%\MIPModeler.dll     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.pdb copy /Y lib\%OPTION%\MIPModeler.pdb     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.lib copy /Y lib\%OPTION%\MIPClpSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.dll copy /Y lib\%OPTION%\MIPClpSolver.dll   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.lib copy /Y lib\%OPTION%\MIPCbcSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.dll copy /Y lib\%OPTION%\MIPCbcSolver.dll   %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPCpxSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPCpxSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\

::if not /i "%PERSEE_DEPS%" == "" (

:persee
echo "Saving to PERSEE_DEPS %PERSEE_DEPS%\MIPModelerLib "

set EXPORT_DIR=%PERSEE_DEPS%\MIPModelerLib

set DOC_DIR=%EXPORT_DIR%\doc

copy /Y MIPModelerEnv_build.bat   %EXPORT_DIR%\

rem ---------------------------------------------------------------
rem MIPModeler & MIPSolverInterface *.h, *.lib *.dll, *.pdf, *.bat 
rem ---------------------------------------------------------------
mkdir %EXPORT_DIR%\src\
mkdir %EXPORT_DIR%\doc
mkdir %EXPORT_DIR%\src\MIPModeler\
mkdir %EXPORT_DIR%\src\MIPModeler\MIPModelerCore
mkdir %EXPORT_DIR%\src\MIPModeler\MIPModelerCore\include
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPClpSolver
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCbcSolver
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCpxSolver
mkdir %EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPMskSolver

copy /Y doc\*.pdf 							%EXPORT_DIR%\doc
copy /Y MIPModelerCore\include\*.h 			%EXPORT_DIR%\src\MIPModeler\MIPModelerCore\include
copy /Y MIPSolverInterface\*.bat 			%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface
copy /Y MIPSolverInterface\MIPClpSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPClpSolver
copy /Y MIPSolverInterface\MIPCbcSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCbcSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.h 	%EXPORT_DIR%\src\MIPModeler\MIPSolverInterface\MIPMskSolver

mkdir %EXPORT_DIR%\lib
mkdir %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.lib copy /Y lib\%OPTION%\MIPModeler.lib     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.dll copy /Y lib\%OPTION%\MIPModeler.dll     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.pdb copy /Y lib\%OPTION%\MIPModeler.pdb     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.lib copy /Y lib\%OPTION%\MIPClpSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.dll copy /Y lib\%OPTION%\MIPClpSolver.dll   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.lib copy /Y lib\%OPTION%\MIPCbcSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.dll copy /Y lib\%OPTION%\MIPCbcSolver.dll   %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPCpxSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPCpxSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\
