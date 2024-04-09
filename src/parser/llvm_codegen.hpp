#pragma once

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <map>
#include <string>

struct LLVMCodegenContext
{
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> llvm_module;
    std::map<std::string, llvm::AllocaInst*> named_values;

    LLVMCodegenContext()
    {
        context = std::make_unique<llvm::LLVMContext>();
        llvm_module = std::make_unique<llvm::Module>("My ST module", *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
    }
};
