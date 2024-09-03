@echo off

if not exist "build" mkdir "build"
"..\..\build\build\bin\stlang" empty.st -o build\empty.package

