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
mkdir %EXPORT_DIR%\GAMSModeler
mkdir %EXPORT_DIR%\MIPModelerCore
mkdir %EXPORT_DIR%\MIPSolverInterface
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
mkdir %EXPORT_DIR%\External
mkdir %EXPORT_DIR%\External\CoinOR
mkdir %EXPORT_DIR%\External\CoinOR\Cbc
mkdir %EXPORT_DIR%\External\CoinOR\Cgl
mkdir %EXPORT_DIR%\External\CoinOR\Clp
mkdir %EXPORT_DIR%\External\CoinOR\CoinUtils
mkdir %EXPORT_DIR%\External\CoinOR\Osi

copy /Y doc\*.pdf 									%EXPORT_DIR%\doc
copy /Y GAMSModeler\*.h 							%EXPORT_DIR%\GAMSModeler
copy /Y GAMSModeler\*.bat 							%EXPORT_DIR%\GAMSModeler
copy /Y MIPModelerCore\*.h 							%EXPORT_DIR%\MIPModelerCore
copy /Y MIPSolverInterface\*.bat 					%EXPORT_DIR%\MIPSolverInterface
copy /Y MIPSolverInterface\MIPClpSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
copy /Y MIPSolverInterface\MIPCbcSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
xcopy /Y /E /I External\CoinOR\Cbc\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Cbc\src
xcopy /Y /E /I External\CoinOR\Cgl\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Cgl\src
xcopy /Y /E /I External\CoinOR\Clp\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Clp\src
xcopy /Y /E /I External\CoinOR\CoinUtils\src\*.h* 	%EXPORT_DIR%\External\CoinOR\CoinUtils\src
xcopy /Y /E /I External\CoinOR\Osi\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Osi\src

mkdir %EXPORT_DIR%\lib
mkdir %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\GAMSModeler*.lib 	copy /Y lib\%OPTION%\GAMSModeler*.lib	%EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\GAMSModeler*.dll 	copy /Y lib\%OPTION%\GAMSModeler*.dll   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\GAMSModeler*.pdb 	copy /Y lib\%OPTION%\GAMSModeler*.pdb   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.lib 	copy /Y lib\%OPTION%\MIPModeler.lib     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.dll 	copy /Y lib\%OPTION%\MIPModeler.dll     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.pdb 	copy /Y lib\%OPTION%\MIPModeler.pdb     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.lib 	copy /Y lib\%OPTION%\MIPClpSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.dll 	copy /Y lib\%OPTION%\MIPClpSolver.dll   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.lib 	copy /Y lib\%OPTION%\MIPCbcSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.dll 	copy /Y lib\%OPTION%\MIPCbcSolver.dll   %EXPORT_DIR%\lib\%OPTION%\

copy /Y lib\%OPTION%\MIPCpxSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPCpxSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\

mkdir %EXPORT_DIR%\External
mkdir %EXPORT_DIR%\External\CoinOR
mkdir %EXPORT_DIR%\External\CoinOR\lib
mkdir %EXPORT_DIR%\External\CoinOR\lib\%OPTION%
if exist External\CoinOR\lib\%OPTION%\libCbc*.dll 	    copy /Y External\CoinOR\lib\%OPTION%\libCbc*.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCbc*.lib 		copy /Y External\CoinOR\lib\%OPTION%\libCbc*.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCgl.dll 		copy /Y External\CoinOR\lib\%OPTION%\libCgl.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCgl.lib 		copy /Y External\CoinOR\lib\%OPTION%\libCgl.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libClp.dll 		copy /Y External\CoinOR\lib\%OPTION%\libClp.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libClp.lib 		copy /Y External\CoinOR\lib\%OPTION%\libClp.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCoinUtils.dll 	copy /Y External\CoinOR\lib\%OPTION%\libCoinUtils.dll 	%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCoinUtils.lib 	copy /Y External\CoinOR\lib\%OPTION%\libCoinUtils.lib 	%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libOsi*.dll 		copy /Y External\CoinOR\lib\%OPTION%\libOsi*.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libOsi*.lib 		copy /Y External\CoinOR\lib\%OPTION%\libOsi*.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\

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
mkdir %EXPORT_DIR%\GAMSModeler\
mkdir %EXPORT_DIR%\MIPModelerCore
mkdir %EXPORT_DIR%\MIPSolverInterface
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
mkdir %EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
mkdir %EXPORT_DIR%\External
mkdir %EXPORT_DIR%\External\CoinOR
mkdir %EXPORT_DIR%\External\CoinOR\Cbc
mkdir %EXPORT_DIR%\External\CoinOR\Cgl
mkdir %EXPORT_DIR%\External\CoinOR\Clp
mkdir %EXPORT_DIR%\External\CoinOR\CoinUtils
mkdir %EXPORT_DIR%\External\CoinOR\Osi

copy /Y doc\*.pdf 									%EXPORT_DIR%\doc
copy /Y GAMSModeler\*.h 							%EXPORT_DIR%\GAMSModeler
copy /Y GAMSModeler\*.bat 							%EXPORT_DIR%\GAMSModeler
copy /Y MIPModelerCore\*.h 							%EXPORT_DIR%\MIPModelerCore
copy /Y MIPSolverInterface\*.bat 					%EXPORT_DIR%\MIPSolverInterface
copy /Y MIPSolverInterface\MIPClpSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPClpSolver
copy /Y MIPSolverInterface\MIPCbcSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPCbcSolver
copy /Y MIPSolverInterface\MIPCpxSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPCpxSolver
copy /Y MIPSolverInterface\MIPMskSolver\*.h 		%EXPORT_DIR%\MIPSolverInterface\MIPMskSolver
xcopy /Y /E /I External\CoinOR\Cbc\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Cbc\src
xcopy /Y /E /I External\CoinOR\Cgl\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Cgl\src
xcopy /Y /E /I External\CoinOR\Clp\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Clp\src
xcopy /Y /E /I External\CoinOR\CoinUtils\src\*.h* 	%EXPORT_DIR%\External\CoinOR\CoinUtils\src
xcopy /Y /E /I External\CoinOR\Osi\src\*.h* 		%EXPORT_DIR%\External\CoinOR\Osi\src

mkdir %EXPORT_DIR%\lib
mkdir %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\GAMSModeler*.lib 	copy /Y lib\%OPTION%\GAMSModeler*.lib	%EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\GAMSModeler*.dll 	copy /Y lib\%OPTION%\GAMSModeler*.dll   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\GAMSModeler*.pdb 	copy /Y lib\%OPTION%\GAMSModeler*.pdb   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.lib 	copy /Y lib\%OPTION%\MIPModeler.lib     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.dll 	copy /Y lib\%OPTION%\MIPModeler.dll     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPModeler.pdb 	copy /Y lib\%OPTION%\MIPModeler.pdb     %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.lib 	copy /Y lib\%OPTION%\MIPClpSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPClpSolver.dll 	copy /Y lib\%OPTION%\MIPClpSolver.dll   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.lib 	copy /Y lib\%OPTION%\MIPCbcSolver.lib   %EXPORT_DIR%\lib\%OPTION%\
if exist lib\%OPTION%\MIPCbcSolver.dll 	copy /Y lib\%OPTION%\MIPCbcSolver.dll   %EXPORT_DIR%\lib\%OPTION%\

copy /Y lib\%OPTION%\MIPCpxSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPCpxSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.lib  %EXPORT_DIR%\lib\%OPTION%\
copy /Y lib\%OPTION%\MIPMskSolver*.dll  %EXPORT_DIR%\lib\%OPTION%\

mkdir %EXPORT_DIR%\External
mkdir %EXPORT_DIR%\External\CoinOR
mkdir %EXPORT_DIR%\External\CoinOR\lib
mkdir %EXPORT_DIR%\External\CoinOR\lib\%OPTION%
if exist External\CoinOR\lib\%OPTION%\libCbc*.dll 		copy /Y External\CoinOR\lib\%OPTION%\libCbc*.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCbc*.lib 		copy /Y External\CoinOR\lib\%OPTION%\libCbc*.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCgl.dll 		copy /Y External\CoinOR\lib\%OPTION%\libCgl.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCgl.lib 		copy /Y External\CoinOR\lib\%OPTION%\libCgl.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libClp.dll 		copy /Y External\CoinOR\lib\%OPTION%\libClp.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libClp.lib 		copy /Y External\CoinOR\lib\%OPTION%\libClp.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCoinUtils.dll  copy /Y eEternal\CoinOR\lib\%OPTION%\libCoinUtils.dll 	%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libCoinUtils.lib  copy /Y eEternal\CoinOR\lib\%OPTION%\libCoinUtils.lib 	%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libOsi*.dll 		copy /Y External\CoinOR\lib\%OPTION%\libOsi*.dll 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
if exist External\CoinOR\lib\%OPTION%\libOsi*.lib 		copy /Y External\CoinOR\lib\%OPTION%\libOsi*.lib 		%EXPORT_DIR%\External\CoinOR\lib\%OPTION%\
