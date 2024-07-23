:: echo tell the the system to not print anything 
@echo off   


mkdir ..\build
pushd ..\build
cl -Zi ..\code\win32_handmade.cpp user32.lib Gdi32.lib
popd
