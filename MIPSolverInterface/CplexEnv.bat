set CPLEX_HOME_128_BIN=
set CPLEX_HOME_129_BIN=
set CPLEX_HOME_1210_BIN=
rem if Cplex 12.8
if exist %SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex\bin\x64_win64\cplex1280.dll (
	set CPLEX_HOME_128=%SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex
	set CPLEX_HOME_128_BIN=%SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex\bin\x64_win64
	set CPLEX_HOME_128_LIB=%SOLVER_DEPS%\Cplex\CPLEX_Studio128\cplex\lib\x64_windows_vs2015\stat_mda
)
rem if installed on Program files
if exist "C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\bin\x64_win64\cplex1290.dll" (
	set CPLEX_HOME_129=C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex
	set CPLEX_HOME_129_BIN=C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\bin\x64_win64
	set CPLEX_HOME_129_LIB=C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\lib\x64_windows_vs2015\stat_mda
)
rem if Cplex 12.9
if exist %SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex\bin\x64_win64\cplex1290.dll (
	set CPLEX_HOME_129=%SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex
	set CPLEX_HOME_129_BIN=%SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex\bin\x64_win64
	set CPLEX_HOME_129_LIB=%SOLVER_DEPS%\Cplex\CPLEX_Studio129\cplex\lib\x64_windows_vs2015\stat_mda
)
rem if Cplex 12.10
if exist %SOLVER_DEPS%\Cplex\CPLEX_Studio1210\cplex\bin\x64_win64\cplex12100.dll (
	set CPLEX_HOME_1210=%SOLVER_DEPS%\Cplex\CPLEX_Studio1210\cplex
	set CPLEX_HOME_1210_BIN=%SOLVER_DEPS%\Cplex\CPLEX_Studio1210\cplex\bin\x64_win64
	set CPLEX_HOME_1210_LIB=%SOLVER_DEPS%\Cplex\CPLEX_Studio1210\cplex\lib\x64_windows_msvc14\stat_mda
)
set PATH=%PATH%;%CPLEX_HOME_128_BIN%;%CPLEX_HOME_129_BIN%;%CPLEX_HOME_1210_BIN%