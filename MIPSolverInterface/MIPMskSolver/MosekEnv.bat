set MOSEK_HOME=
set MOSEK_HOME_LIB=
set MOSEK_HOME_BIN=
set MOSEK_LIB_VERSION=

rem if Mosek 8.1
if exist %SOLVER_DEPS%\mosek\mosek_8.1\bin\mosek64_8_1.dll (
	set MOSEK_HOME=%SOLVER_DEPS%\mosek\mosek_8.1\
	set MOSEK_HOME_BIN=%SOLVER_DEPS%\mosek\mosek_8.1\\bin
	set MOSEK_HOME_LIB=%SOLVER_DEPS%\mosek\mosek_8.1\\bin
	set MOSEK_LIB_VERSION=_8_1
)
set PATH=%PATH%;%MOSEK_HOME_BIN%