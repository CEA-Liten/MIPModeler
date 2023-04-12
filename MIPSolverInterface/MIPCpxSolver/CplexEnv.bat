set CPLEX_HOME=
set CPLEX_HOME_LIB=
set CPLEX_HOME_BIN=
set CPLEX_VERSION=

if %NOCPLEX%==1 goto sortie


REM Find cplex installation using system environement variable

REM TEMPLATE
REM if exist "%CPLEX_STUDIO_DIRXXX%\cplex\bin\x64_win64\cplexXXXX.dll" (
	REM set CPLEX_HOME=%CPLEX_STUDIO_DIRXXX%cplex
	REM set CPLEX_HOME_BIN=%CPLEX_STUDIO_DIRXXX%\cplex\bin\x64_win64
	REM set CPLEX_HOME_LIB=%CPLEX_STUDIO_DIRXXX%\lib\x64_windows_msvcNNNN\stat_mda
	REM set CPLEX_VERSION=XXXX
	REM goto :END
REM )

if exist "%CPLEX_STUDIO_DIR201%\cplex\bin\x64_win64\cplex2010.dll" (
	set CPLEX_HOME=%CPLEX_STUDIO_DIR201%\cplex
	set CPLEX_HOME_BIN=%CPLEX_STUDIO_DIR201%\cplex\bin\x64_win64
	set CPLEX_HOME_LIB=%CPLEX_STUDIO_DIR201%\cplex\lib\x64_windows_msvc14\stat_mda
	set CPLEX_VERSION=2010
	goto :END
)

if exist "%CPLEX_STUDIO_DIR129%\cplex\bin\x64_win64\cplex1290.dll" (
	set CPLEX_HOME=%CPLEX_STUDIO_DIR129%\cplex
	set CPLEX_HOME_BIN=%CPLEX_STUDIO_DIR129%\bin\x64_win64
	set CPLEX_HOME_LIB=%CPLEX_STUDIO_DIR129%\lib\x64_windows_vs2015\stat_mda
	set CPLEX_VERSION=1290
	goto :END
)
:END
echo " - Add Cplex to path: %CPLEX_HOME_BIN% "
set PATH=%PATH%;%CPLEX_HOME_BIN%
:sortie
