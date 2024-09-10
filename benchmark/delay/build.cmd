@echo off

if not exist "build" mkdir "build"
"..\..\build\build\bin\stlang" delay.st -o build\delay.package

