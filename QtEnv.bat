rem @echo off
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rem Ce script définit les chemins nécessaire à l'environnement Qt
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rem Choix de la version de Qt
rem ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set QTDIR=C:\Qt

rem special overwritting for Odyssey multiple Qt environment
if exist C:\Qt\Qt5.15.0 set QTDIR=C:\Qt\Qt5.15.0

set QTPATH=%QTDIR%\5.15.0\msvc2019_64\bin;%QTDIR%\Tools\QtCreator\bin;

set PATH=C:\Program Files (x86)\Windows Kits\10\bin\x64\ucrt;%PATH%

set PATH=%QTPATH%;%PATH%
