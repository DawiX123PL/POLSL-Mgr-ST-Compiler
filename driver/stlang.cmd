echo off

set "st_input_files=../test/test1/test_func.st ../test/test1/fahrenheit_to_celsius.st ../build/build/stl/conv.st_extern"
set "cpp_input_files=../build/build/stl/conv.c"

set "triple=thumbv7em-none-unknown-eabi"
set "arch=-march=armv7e-m+fp"
set "cpu=-mcpu=cortex-m4"
set "fpu=-mfpu=fpv4-sp-d16"
set "float=-mfloat-abi=soft"
set "linker-script=plc_linker_script.ld"

set "sysroot=../arm-none-eabi-gcc_libs/lib/thumbv7e-m"

set "libs_path=-L%sysroot%"
set "libs=-lgcc -lc -lnosys"
:: set "lib_obj=%sysroot%/crti.o %sysroot%/crtbegin.o %sysroot%/crt0.o %sysroot%/crtend.o %sysroot%/crtn.o"

@REM https://courses.washington.edu/cp105/GCC/Removing%20unused%20functions%20and%20dead%20code.html
@REM set "DEADCODESTRIP=-Wl,-static  -fdata-sections -ffunction-sections -Wl,--gc-sections -Wl,-s"
set "DEADCODESTRIP=-fdata-sections -ffunction-sections -Wl,--gc-sections"

:: compile ST code to IR file 
"../build/build/bin/st_compiler" -target %triple% %st_input_files% -o output.ll

:: optionaly optimize code
opt output.ll -S -o output_no_opt.ll
opt output.ll -O3 -S -o output_full_opt.ll

:: Compile and link files
clang -T %linker-script% -Os -fPIC "-nostdlib" %DEADCODESTRIP% %libs_path% %libs% %lib_obj% -target %triple% %arch% %cpu% %fpu% %float% -mthumb %cpp_input_files% output.ll -o output.elf


:: emit binary code
llvm-objcopy -O binary output.elf output.bin

:: create binary package
"../build/build/bin/packager" -modules plc_modules.modules -bin output.bin -o output.package

:: send package to plc
"../build/build/bin/sender" -i output.package --address "192.168.1.106" --port 2000

:: emit assembly file to visualy inspect produced binaries
arm-none-eabi-objdump output.elf -marm -D > output.s
