
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

static llvm::codegen::RegisterCodeGenFlags CGF;

int main()
{
    char *ir_code = R"xxxxxx(


%PLC_PRG.struct = type { i1, float, float, i16 }

define void @PLC_PRG.init(ptr %0) {
entry:
  %v1 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 0
  store i1 false, ptr %v1, align 1
  %v2 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 1
  store float 0.000000e+00, ptr %v2, align 4
  %v3 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 2
  store float 0.000000e+00, ptr %v3, align 4
  %v4 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 3
  store i16 0, ptr %v4, align 2
  ret void
}

define void @PLC_PRG(ptr %0) {
entry:
  %v1 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 0
  %v2 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 1
  %v3 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 2
  %v4 = getelementptr inbounds %PLC_PRG.struct, ptr %0, i32 0, i32 3
  %v21 = load float, ptr %v2, align 4
  %v32 = load float, ptr %v3, align 4
  %1 = fcmp une float %v21, %v32
  store i1 %1, ptr %v1, align 1
  ret void
}

; define %PLC_PRG.struct @PLC_PRG.construct() {
; entry:
;   %v1 = %PLC_PRG.struct zeroinitializer
;   ret v1
; }

; define void @PLC_PRG.construct1() {
; entry:
;   ret void
; }

define %PLC_PRG.struct @PLC_PRG.construct() {
entry:
  ret %PLC_PRG.struct { i1 false, float 1.000000e+00, float 1.000000e+00, i16 1 }
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
    // builder.setMArch(llvm::codegen::getMArch());
    // builder.setMCPU(llvm::codegen::getCPUStr());
    // builder.setMAttrs(llvm::codegen::getFeatureList());
    // if (auto RM = llvm::codegen::getExplicitRelocModel())
    //     builder.setRelocationModel(*RM);
    // if (auto CM = llvm::codegen::getExplicitCodeModel())
    //     builder.setCodeModel(*CM);

    // builder.setEngineKind(llvm::EngineKind::JIT);
    builder.setEngineKind(llvm::EngineKind::Interpreter);

    // llvm::RTDyldMemoryManager *RTDyldMM = new llvm::SectionMemoryManager();
    // builder.setMCJITMemoryManager(std::unique_ptr<llvm::RTDyldMemoryManager>(RTDyldMM));

    // auto o = llvm::CodeGenOpt::parseLevel('0');
    // builder.setOptLevel(o.value());

//     llvm::TargetOptions Options =
//       llvm::codegen::InitTargetOptionsFromCodeGenFlags(llvm::sys::getDefaultTargetTriple());
//   if (llvm::codegen::getFloatABIForCalls() != llvm::FloatABI::Default)

//     Options.FloatABIType = llvm::codegen::getFloatABIForCalls();

//   builder.setTargetOptions(Options);

    std::string builder_error;
    builder.setErrorStr(&builder_error);
    std::unique_ptr<llvm::ExecutionEngine> engine(builder.create());
    // llvm::GenericValue program_struct;

    // find entry point

    std::string program_name = "PLC_PRG";
    std::string program_name_init = program_name + ".init";
    std::string program_name_construct = program_name + ".construct";

    llvm::Function *program = engine->FindFunctionNamed(program_name);
    llvm::Function *program_init = engine->FindFunctionNamed(program_name_init);
    llvm::Function *program_construct = engine->FindFunctionNamed(program_name_construct);


    uint8_t prog_mem [127] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    llvm::GenericValue input;
    input.PointerVal = prog_mem;


    llvm::GenericValue output;

    output = engine->runFunction(program_init, {input});

    // engine->getFunctionAddress()

    return 0;
}