set MOSEK_HOME_81_BIN=
rem if Mosek 8.1
if exist %SOLVER_DEPS%\mosek\mosek_8.1\bin\mosek64_8_1.dll (
	set MOSEK_HOME_81=%SOLVER_DEPS%\mosek\mosek_8.1\
	set MOSEK_HOME_81_BIN=%SOLVER_DEPS%\mosek\mosek_8.1\\bin
	set MOSEK_HOME_81_LIB=%SOLVER_DEPS%\mosek\mosek_8.1\\bin
)
set PATH=%PATH%;%MOSEK_HOME_81_BIN%