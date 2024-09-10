@echo off

@REM .\build
"..\..\build\build\bin\plc_conn.exe" build\delay.package --address 192.168.0.150 --port 2000 --upload --start --stop --performance --verbose
