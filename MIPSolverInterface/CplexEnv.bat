set CPLEX_HOME_128_BIN=
set CPLEX_HOME_BIN=
echo "in CPLEX_ENV SOLVER_DEPS=%SOLVER_DEPS%"
rem if installed on Program files
if exist "C:\Program Files\IBM\ILOG\CPLEX_Studio201\cplex\bin\x64_win64\cplex2010.dll" (
	set CPLEX_HOME=C:\Program Files\IBM\ILOG\CPLEX_Studio201\cplex
	set CPLEX_HOME_BIN=C:\Program Files\IBM\ILOG\CPLEX_Studio201\cplex\bin\x64_win64
	set CPLEX_HOME_LIB=C:\Program Files\IBM\ILOG\CPLEX_Studio201\cplex\lib\x64_windows_msvc14\stat_mda
	goto :END
)
rem if Cplex 20.10
if exist %SOLVER_DEPS%\Cplex\CPLEX_Studio201\cplex\bin\x64_win64\cplex2010.dll (
	set CPLEX_HOME=%SOLVER_DEPS%\Cplex\CPLEX_Studio201\cplex
	set CPLEX_HOME_BIN=%SOLVER_DEPS%\Cplex\CPLEX_Studio201\cplex\bin\x64_win64
	set CPLEX_HOME_LIB=%SOLVER_DEPS%\Cplex\CPLEX_Studio201\cplex\lib\x64_windows_msvc14\stat_mda
	goto :END
)
rem if installed on Program files
if exist "C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\bin\x64_win64\cplex1290.dll" (
	set CPLEX_HOME=C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex
	set CPLEX_HOME_BIN=C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\bin\x64_win64
	set CPLEX_HOME_LIB=C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\lib\x64_windows_vs2015\stat_mda
	goto :END
)
rem if Cplex 12.9
if exist %SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex\bin\x64_win64\cplex1290.dll (
	set CPLEX_HOME=%SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex
	set CPLEX_HOME_BIN=%SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex\bin\x64_win64
	set CPLEX_HOME_LIB=%SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex\lib\x64_windows_vs2015\stat_mda
	goto :END
)
rem if Cplex 12.8
if exist %SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex\bin\x64_win64\cplex1280.dll (
	set CPLEX_HOME=%SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex
	set CPLEX_HOME_BIN=%SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex\bin\x64_win64
	set CPLEX_HOME_LIB=%SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex\lib\x64_windows_vs2015\stat_mda
	goto :END
)
:END
echo " - Add Cplex to path: %CPLEX_HOME_BIN% "
set PATH=%PATH%;%CPLEX_HOME_BIN%
