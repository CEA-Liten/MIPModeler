REM for RELEASE set OPTION=release
REM for debug set OPTION=debug
REM OPTION must be defined by calling script
REM Or OPTION is defined by user in interactive mode (detected by void option)

if /i "%OPTION%" == "" (
ECHO A build mode is required. please enter release or debug
set /p OPTION=release or debug?:
)

set BUILD_PATH=%1
set CUR_PATH=%~dp0

set OLD_PATH=%PATH%

cd "%BUILD_PATH%"

REM Set path for Qt, FBSF and Pegase
REM call AppEnv.bat -> replaced by PegaseEnv

REM clean
if exist Makefile call jom distclean

REM Create makefiles
call qmake

REM compile
if %OPTION%==debug (
call jom debug
)
if %OPTION%==release (
call jom
)

cd %CUR_PATH%
set PATH=%OLD_PATH%