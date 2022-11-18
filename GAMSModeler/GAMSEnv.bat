rem @echo off
set GAMS_HOME=

if exist C:\GAMS\39 set GAMS_HOME=C:\GAMS\39

set USE_GAMS = %GAMS_HOME%

set PATH=%GAMS_HOME%;%GAMS_HOME%\apifiles\C++\lib\vs2019;%PATH%;
