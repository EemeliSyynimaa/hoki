@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl -FC -Zi ..\source\win32_main.cpp user32.lib Gdi32.lib
popd
