

if not exist "build" mkdir "build"
"..\..\build\build\bin\stlang" led_line.st -o build\led_line.package
"..\..\build\build\bin\plc_conn.exe" build\led_line.package --address 192.168.0.150 --port 2000 --upload --start --stop --verbose
