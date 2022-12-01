REM for RELEASE set OPTION=release
REM for debug set OPTION=debug
REM OPTION must be defined by calling script
REM Or OPTION is defined by user in interactive mode (detected by void option)

if /i "%OPTION%" == "" (
ECHO A build mode is required. please enter release or debug
set /p OPTION=release or debug?:
)

if /i "%PEGASE_ROOT%" == "" (
call setDepsPath
)

cd %~dp0

:: No export to Pegase for Integration branch !

if "%EXPORT_TO_PEGASE%" == "NO" goto persee

set EXPORT_DIR=%PEGASE_ROOT%\Deps\External\MIPModeler

set DOC_DIR=%EXPORT_DIR%\doc

copy /Y MIPModelerEnv_build.bat   %EXPORT_DIR%\

rem ---------------------------------------------------------------
rem MIPModeler & MIPSolverInterface *.h, *.lib *.dll, *.pdf, *.bat 
rem ---------------------------------------------------------------
mkdir %EXPORT_DIR%\doc
mkdir %EXPORT_DIR%\lib
mkdir %EXPORT_DIR%\lib\%OPTION%\
mkdir %EXPORT_DIR%\GAMSModeler
mkdir %EXPORT_DIR%\core
mkdir %EXPORT_DIR%\MIPSolverInterface
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
mkdir %EXPORT_DIR%\external
mkdir %EXPORT_DIR%\external\Eigen
mkdir %EXPORT_DIR%\external\CoinOR
mkdir %EXPORT_DIR%\external\CoinOR\Cbc
mkdir %EXPORT_DIR%\external\CoinOR\Cgl
mkdir %EXPORT_DIR%\external\CoinOR\Clp
mkdir %EXPORT_DIR%\external\CoinOR\CoinUtils
mkdir %EXPORT_DIR%\external\CoinOR\Osi
mkdir %EXPORT_DIR%\external\CoinOR\lib
mkdir %EXPORT_DIR%\external\CoinOR\lib\%OPTION%

copy /Y doc\*.pdf 										%EXPORT_DIR%\doc
copy /Y GAMSModeler\*.h 								%EXPORT_DIR%\GAMSModeler
copy /Y GAMSModeler\*.bat 								%EXPORT_DIR%\GAMSModeler
copy /Y core\*.h 								        %EXPORT_DIR%\core
copy /Y MIPSolverInterface\MIPClpSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
copy /Y MIPSolverInterface\MIPCbcSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.bat 			%EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.bat 			%EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
xcopy /Y /E /I external\Eigen				 			%EXPORT_DIR%\external\Eigen
xcopy /Y /E /I external\CoinOR\Cbc\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Cbc\src
xcopy /Y /E /I external\CoinOR\Cgl\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Cgl\src
xcopy /Y /E /I external\CoinOR\Clp\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Clp\src
xcopy /Y /E /I external\CoinOR\CoinUtils\src\*.h* 		%EXPORT_DIR%\external\CoinOR\CoinUtils\src
xcopy /Y /E /I external\CoinOR\Osi\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Osi\src

copy /Y lib\%OPTION%\GAMSModeler*.lib					%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\GAMSModeler*.dll   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\GAMSModeler*.pdb   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPModeler.lib     				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPModeler.dll     				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPModeler.pdb     				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPClpSolver.lib   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPClpSolver.dll   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCbcSolver.lib   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCbcSolver.dll   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCpxSolver*.lib  				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCpxSolver*.dll  				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPMskSolver*.lib  				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPMskSolver*.dll  				%EXPORT_DIR%\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCbc*.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCbc*.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCgl.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCgl.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libClp.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libClp.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCoinUtils.dll 	%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCoinUtils.lib 	%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libOsi*.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libOsi*.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%

::if not /i "%PERSEE_DEPS%" == "" (

:persee
set PERSEE_DEPS=%PERSEE_APP%\Deps
set EXPORT_DIR=%PERSEE_DEPS%\MIPModeler
set DOC_DIR=%EXPORT_DIR%\doc

echo "Exporting to %EXPORT_DIR% "

copy /Y MIPModelerEnv_build.bat   %EXPORT_DIR%\

rem ---------------------------------------------------------------
rem MIPModeler & MIPSolverInterface *.h, *.lib *.dll, *.pdf, *.bat 
rem ---------------------------------------------------------------
mkdir %EXPORT_DIR%\doc
mkdir %EXPORT_DIR%\lib
mkdir %EXPORT_DIR%\lib\%OPTION%\
mkdir %EXPORT_DIR%\GAMSModeler\
mkdir %EXPORT_DIR%\core
mkdir %EXPORT_DIR%\MIPSolverInterface
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
mkdir %EXPORT_DIR%\external
mkdir %EXPORT_DIR%\external\Eigen
mkdir %EXPORT_DIR%\external\CoinOR
mkdir %EXPORT_DIR%\external\CoinOR\Cbc
mkdir %EXPORT_DIR%\external\CoinOR\Cgl
mkdir %EXPORT_DIR%\external\CoinOR\Clp
mkdir %EXPORT_DIR%\external\CoinOR\CoinUtils
mkdir %EXPORT_DIR%\external\CoinOR\Osi
mkdir %EXPORT_DIR%\external\CoinOR\lib
mkdir %EXPORT_DIR%\external\CoinOR\lib\%OPTION%

copy /Y doc\*.pdf 										%EXPORT_DIR%\doc
copy /Y GAMSModeler\*.h 								%EXPORT_DIR%\GAMSModeler
copy /Y GAMSModeler\*.bat 								%EXPORT_DIR%\GAMSModeler
copy /Y core\*.h 								        %EXPORT_DIR%\core
copy /Y MIPSolverInterface\MIPClpSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
copy /Y MIPSolverInterface\MIPCbcSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.bat 			%EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.h 			%EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.bat 			%EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
xcopy /Y /E /I external\Eigen				 			%EXPORT_DIR%\external\Eigen
xcopy /Y /E /I external\CoinOR\Cbc\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Cbc\src
xcopy /Y /E /I external\CoinOR\Cgl\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Cgl\src
xcopy /Y /E /I external\CoinOR\Clp\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Clp\src
xcopy /Y /E /I external\CoinOR\CoinUtils\src\*.h* 		%EXPORT_DIR%\external\CoinOR\CoinUtils\src
xcopy /Y /E /I external\CoinOR\Osi\src\*.h* 			%EXPORT_DIR%\external\CoinOR\Osi\src

copy /Y lib\%OPTION%\GAMSModeler*.lib					%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\GAMSModeler*.dll   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\GAMSModeler*.pdb   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPModeler.lib     				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPModeler.dll     				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPModeler.pdb     				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPClpSolver.lib   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPClpSolver.dll   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCbcSolver.lib   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCbcSolver.dll   				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCpxSolver*.lib  				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPCpxSolver*.dll  				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPMskSolver*.lib  				%EXPORT_DIR%\lib\%OPTION%
copy /Y lib\%OPTION%\MIPMskSolver*.dll  				%EXPORT_DIR%\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCbc*.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCbc*.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCgl.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCgl.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libClp.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libClp.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCoinUtils.dll 	%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libCoinUtils.lib 	%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libOsi*.dll 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
copy /Y external\CoinOR\lib\%OPTION%\libOsi*.lib 		%EXPORT_DIR%\external\CoinOR\lib\%OPTION%
