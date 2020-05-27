set MOSEK_HOME_81_BIN=
rem if Mosek 8.1
if exist %DEPS_HOME%\External\mosek\mosek_8.1\bin\mosek64_8_1.dll (
	set MOSEK_HOME_81=%DEPS_HOME%\External\mosek\mosek_8.1\
	set MOSEK_HOME_81_BIN=%DEPS_HOME%\External\mosek\mosek_8.1\\bin
	set MOSEK_HOME_81_LIB=%DEPS_HOME%\External\mosek\mosek_8.1\\bin
)
set PATH=%PATH%;%MOSEK_HOME_81_BIN%