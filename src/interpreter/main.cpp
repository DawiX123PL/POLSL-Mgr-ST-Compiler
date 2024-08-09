
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IR/Verifier.h>
#include <llvm/CodeGen/CommandFlags.h>
#include <llvm/CodeGen/LinkAllCodegenComponents.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>

#include <memory>
#include <iostream>
#include "../console/color.hpp"

#include <llvm/ADT/StringExtras.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/CodeGen/CommandFlags.h>
#include <llvm/CodeGen/LinkAllCodegenComponents.h>
#include <llvm/Config/llvm-config.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/JITEventListener.h>
#include <llvm/ExecutionEngine/JITSymbol.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/ObjectCache.h>
#include <llvm/ExecutionEngine/Orc/DebugUtils.h>
#include <llvm/ExecutionEngine/Orc/Debugging/DebuggerSupport.h>
#include <llvm/ExecutionEngine/Orc/EPCDynamicLibrarySearchGenerator.h>
#include <llvm/ExecutionEngine/Orc/EPCEHFrameRegistrar.h>
#include <llvm/ExecutionEngine/Orc/EPCGenericRTDyldMemoryManager.h>
#include <llvm/ExecutionEngine/Orc/ExecutionUtils.h>
#include <llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ObjectTransformLayer.h>
#include <llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h>
#include <llvm/ExecutionEngine/Orc/SimpleRemoteEPC.h>
#include <llvm/ExecutionEngine/Orc/SymbolStringPool.h>
#include <llvm/ExecutionEngine/Orc/TargetProcess/JITLoaderGDB.h>
#include <llvm/ExecutionEngine/Orc/TargetProcess/RegisterEHFrames.h>
#include <llvm/ExecutionEngine/Orc/TargetProcess/TargetExecutionUtils.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Object/Archive.h>
#include <llvm/Object/ObjectFile.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Debug.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/Format.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/MathExtras.h>
#include <llvm/Support/Memory.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/PluginLoader.h>
#include <llvm/Support/Process.h>
#include <llvm/Support/Program.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/WithColor.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/TargetParser/Triple.h>
#include <llvm/Transforms/Instrumentation.h>

typedef void (*ProgramPtr)(void *);
typedef void (*ProgramInitPtr)(void *);

struct ProgramDescription
{
    ProgramPtr program_ptr;
    ProgramInitPtr program_init_ptr;
    uint32_t program_size;
};

static llvm::codegen::RegisterCodeGenFlags CGF;

int main()
{
    char *ir_code = R"xxxxxx(

; ModuleID = 'my ST compiler'
source_filename = "my ST compiler"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc"

%main.struct = type { i1, float, float, i16 }

@"@ModuleDescription" = constant <{ ptr, ptr, i32 }> <{ ptr @main, ptr @main.init, i32 16 }>

define i1 @test_func(i16 %0, i16 %1, i16 %2, ptr %3, ptr %4) {
entry:
  %test_func.alloca = alloca i1, align 1
  %c.alloca = alloca i16, align 2
  %x.alloca = alloca i16, align 2
  %b1.alloca = alloca float, align 4
  %c1.alloca = alloca i16, align 2
  %b.alloca = alloca i16, align 2
  %aaa.alloca = alloca i16, align 2
  store i16 %0, ptr %aaa.alloca, align 2
  store i16 %1, ptr %b.alloca, align 2
  store i16 %2, ptr %c1.alloca, align 2
  %5 = icmp eq ptr %3, null
  br i1 %5, label %if_pointer_null, label %if_pointer_not_null

if_pointer_null:                                  ; preds = %entry
  br label %if_merge

if_pointer_not_null:                              ; preds = %entry
  %6 = load float, ptr %3, align 4
  br label %if_merge

if_merge:                                         ; preds = %if_pointer_not_null, %if_pointer_null
  %in_out_value = phi float [ %6, %if_pointer_not_null ], [ 0.000000e+00, %if_pointer_null ]
  store float %in_out_value, ptr %b1.alloca, align 4
  store i16 0, ptr %x.alloca, align 2
  store i16 0, ptr %c.alloca, align 2
  store i1 false, ptr %test_func.alloca, align 1
  br label %while_condition

while_condition:                                  ; preds = %while_do, %if_merge
  %c = load i16, ptr %c.alloca, align 2
  %7 = add i16 %c, 0
  %8 = icmp sgt i16 %7, 0
  br i1 %8, label %while_do, label %end_while

while_do:                                         ; preds = %while_condition
  %aaa = load i16, ptr %aaa.alloca, align 2
  %9 = sub i16 0, %aaa
  %b = load i16, ptr %b.alloca, align 2
  %10 = add i16 %9, %b
  %c1 = load i16, ptr %c1.alloca, align 2
  %11 = add i16 %10, %c1
  store i16 %11, ptr %x.alloca, align 2
  br label %while_condition

end_while:                                        ; preds = %while_condition
  br label %return_block

return_block:                                     ; preds = %end_while
  %is_not_null = icmp ne ptr %3, null
  br i1 %is_not_null, label %if_pointer_notnull, label %if_merge1

if_pointer_notnull:                               ; preds = %return_block
  %12 = load float, ptr %b1.alloca, align 4
  store float %12, ptr %3, align 4
  br label %if_merge1

if_merge1:                                        ; preds = %if_pointer_notnull, %return_block
  %is_not_null4 = icmp ne ptr %4, null
  br i1 %is_not_null4, label %if_pointer_notnull2, label %if_merge3

if_pointer_notnull2:                              ; preds = %if_merge1
  %13 = load i16, ptr %x.alloca, align 2
  store i16 %13, ptr %4, align 2
  br label %if_merge3

if_merge3:                                        ; preds = %if_pointer_notnull2, %if_merge1
  %result = load i1, ptr %test_func.alloca, align 1
  ret i1 %result
}

define float @fahrenheit_to_celsius(float %0) {
entry:
  %fahrenheit_to_celsius.alloca = alloca float, align 4
  %f.alloca = alloca float, align 4
  store float %0, ptr %f.alloca, align 4
  store float 0.000000e+00, ptr %fahrenheit_to_celsius.alloca, align 4
  %f = load float, ptr %f.alloca, align 4
  %1 = fsub float %f, 0.000000e+00
  %2 = fdiv float %1, 0.000000e+00
  store float %2, ptr %fahrenheit_to_celsius.alloca, align 4
  br label %return_block

return_block:                                     ; preds = %entry
  %result = load float, ptr %fahrenheit_to_celsius.alloca, align 4
  ret float %result
}

define void @main.init(ptr %0) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 0
  store i1 true, ptr %v1, align 1
  %v2 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 1
  store float 1.0, ptr %v2, align 4
  %v3 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 2
  store float 2137.0, ptr %v3, align 4
  %v4 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 3
  store i16 420, ptr %v4, align 2
  ret void
}

define void @main(ptr %0) {
entry:
  %v1 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 0
  %v2 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 1
  %v3 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 2
  %v4 = getelementptr inbounds %main.struct, ptr %0, i32 0, i32 3
  %v21 = load float, ptr %v2, align 4
  %v32 = load float, ptr %v3, align 4
  %1 = fcmp une float %v21, %v32
  store i1 %1, ptr %v1, align 1
  ret void
}


    )xxxxxx";
    //   ret float %result

    llvm::MemoryBufferRef ir_code_ref(ir_code, "code");

    llvm::SMDiagnostic Err;

    // create instance of llvm module
    std::unique_ptr<llvm::LLVMContext> context = std::make_unique<llvm::LLVMContext>();
    std::unique_ptr<llvm::Module> module = llvm::parseIR(ir_code_ref, Err, *context);

    std::string code_err;
    llvm::raw_string_ostream ostream(code_err);
    llvm::verifyModule(*module, &ostream);

    std::cout << "\n"
              << Console::FgBrightRed(code_err) << "\n";

    std::cout.flush();

    // llvm::StructType * str = *module->getIdentifiedStructTypes().begin();

    LLVMInitializeNativeAsmParser();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeTarget();

    // engine builder
    llvm::EngineBuilder builder(std::move(module));

    builder.setEngineKind(llvm::EngineKind::JIT);
    // builder.setEngineKind(llvm::EngineKind::Interpreter);


    std::string builder_error;
    builder.setErrorStr(&builder_error);
    std::unique_ptr<llvm::ExecutionEngine> engine(builder.create());


    // find program description
    std::string program_name = "main";

    ProgramDescription *program_description = (ProgramDescription*)engine->getGlobalValueAddress("@ModuleDescription");

    // allocate and init program memory

    // uint8_t* program_data = new uint8_t[program_description->program_size];
    std::unique_ptr<uint8_t[]> program_data = std::make_unique<uint8_t[]>(program_description->program_size);
    memset(program_data.get(), 0, program_description->program_size);
    
    // init program memory

    program_description->program_init_ptr(program_data.get());

    // run PLC scans
    // (execute program body in loop)
    while(true)
    {
        program_description->program_ptr(program_data.get());
    }




    return 0;
}