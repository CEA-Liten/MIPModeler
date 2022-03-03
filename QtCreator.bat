rem @echo off
color 3F
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rem Ce script permet de démarrer QtCreator avec les bonnes variables
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cd %~dp0

::set extension=_debug
call QtEnv.bat
call MIPModelerEnv_build.bat

rem set COMPONENTS_PATH=%APP_HOME%
rem set QML_IMPORT_TRACE=1

::start C:\Qt\Qt5.14.0\Tools\QtCreator\bin\qtcreator.exe
start qtcreator.exe
exit

