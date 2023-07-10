REM for RELEASE set OPTION=release
REM for debug set OPTION=debug
REM OPTION must be defined by calling script
REM Or OPTION is defined by user in interactive mode (detected by void option)
setlocal enabledelayedexpansion

if /i "%OPTION%" == "" (
ECHO A build mode is required. please enter release or debug
set /p OPTION=release or debug?:
)

set BUILD_PATH=%1
set CUR_PATH=%~dp0

set OLD_PATH=%PATH%

cd "%BUILD_PATH%"

REM clean
if %OPTION%==debug (
if exist Makefile call jom -f Makefile.Debug distclean
)
if %OPTION%==release (
if exist Makefile call jom -f Makefile.Release distclean
)

set log_file="%CUR_PATH%\compile.%OPTION%.log"
echo "Compiling %BUILD_PATH% in mode %OPTION%" > %log_file%

REM Create makefiles
call qmake

REM compile
if %OPTION%==debug (
call jom debug >> %log_file%
if not !ERRORLEVEL! == 0 goto sortie
call jom.exe -f Makefile.Debug install
)

if %OPTION%==release (
call jom >> %log_file%
if not !ERRORLEVEL! == 0 goto sortie
call jom.exe -f Makefile.Release install
)

cd %CUR_PATH%
set PATH=%OLD_PATH%

EXIT /B 0
 
:sortie
 echo "FATAL COMPILATION OF %BUILD_PATH% in mode %OPTION%" 
 EXIT /B 1
