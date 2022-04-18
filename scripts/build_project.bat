@echo off

if exist ..\build\ goto buildFolderExists

if not exist ..\build\ goto buildFolderCreate

:buildFolderExists
echo Folder build\ already exists!
goto runCmake

:buildFolderCreate
mkdir ..\build\
echo Folder build\ has been created successfully!
goto runCmake

:runCmake
pushd %~dp0\..\build\
cmake ..
popd
