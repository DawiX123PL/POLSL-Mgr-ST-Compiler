@echo off

if not exist "build" mkdir "build"
"..\..\build\build\bin\stlang" optimize.st -o build\optimize.package

llvm-size ./build/optimize.elf