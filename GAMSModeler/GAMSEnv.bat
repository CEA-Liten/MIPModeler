rem @echo off
set GAMS_HOME=
set USE_GAMS=

if %NOGAMS%==1 goto sortie

if exist C:\GAMS\39 set GAMS_HOME=C:\GAMS\39
if %GAMS_HOME%=="" goto sortie	
set USE_GAMS=%GAMS_HOME%
set PATH=%GAMS_HOME%;%GAMS_HOME%\apifiles\C++\lib\vs2019;%PATH%;

:sortie


