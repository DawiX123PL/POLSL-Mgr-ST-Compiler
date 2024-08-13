
@REM compile ST code to object file
"../build/build/st_compiler" ../test/test1/test_func.st ../test/test1/fahrenheit_to_celsius.st -o st_program.o

@REM linker 
@REM clang -T plc_linker_script.ld  -fPIC -nostdlib  output.o -target arm-none-eabi -march=armv7e-m+fp -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o clang-out.elf
arm-none-eabi-gcc -T plc_linker_script.ld -fdata-sections -ffunction-sections -OS -fPIC output.o -march=armv7e-m+fp -mcpu=cortex-m4 --specs=nosys.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o output.elf -Wl,--gc-sections


@REM emit binary code
llvm-objcopy -O binary output.elf output.bin

"../build/build/packager" -modules plc_modules.modules -bin output.bin -o output.package



