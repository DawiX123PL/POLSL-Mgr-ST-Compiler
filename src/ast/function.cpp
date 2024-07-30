#include "ast1.hpp"
#include "../console/color.hpp"

namespace AST
{

    std::string Function::ToString()
    {
        std::string vars_str;
        vars_str += "var:\n";
        for (auto v : var)
            vars_str += "\t" + v.ToString() + "\n";

        vars_str += "var_input:\n";
        for (auto v : var_input)
            vars_str += "\t" + v.ToString() + "\n";

        vars_str += "var_output:\n";
        for (auto v : var_output)
            vars_str += "\t" + v.ToString() + "\n";

        vars_str += "var_in_out:\n";
        for (auto v : var_in_out)
            vars_str += "\t" + v.ToString() + "\n";

        return "{FUNCTION " + name + "\n" + vars_str + "\n" + StatementListToString(statement_list) + "\n}";
    }

    static llvm::AllocaInst *CreateInputVariable(LLVMCompilerContext *llvm_cc, llvm::Function *function, llvm::Argument *argument, Variable &variable)
    {
        llvm::AllocaInst *alloca = CreateEntryBlockAlloca(llvm_cc, function, variable);
        llvm_cc->ir_builder->CreateStore(argument, alloca, false);
        return alloca;
    }

    static llvm::AllocaInst *CreateInOutVariable(LLVMCompilerContext *llvm_cc, llvm::Function *function, llvm::Argument *argument, Variable &variable)
    {
        llvm::AllocaInst *alloca = CreateEntryBlockAlloca(llvm_cc, function, variable);

        // rest of code represents:
        // alloca := if (ptr==nullptr) then *ptr else 0;

        // check if pointer is null
        llvm::Constant *null_pointer = llvm::Constant::getNullValue(llvm::PointerType::get(*llvm_cc->context, 0));
        llvm::Value *nullcheck = llvm_cc->ir_builder->CreateICmpEQ(argument, null_pointer);

        // if statement checking for null pointer
        llvm::BasicBlock *pointer_null_block = llvm::BasicBlock::Create(*llvm_cc->context, "if_pointer_null", function);
        llvm::BasicBlock *pointer_notnull_block = llvm::BasicBlock::Create(*llvm_cc->context, "if_pointer_not_null", function);
        llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(*llvm_cc->context, "if_merge", function);

        llvm_cc->ir_builder->CreateCondBr(nullcheck, pointer_null_block, pointer_notnull_block);

        llvm_cc->ir_builder->SetInsertPoint(pointer_null_block);
        llvm::ConstantAggregateZero *zeroinitializer = llvm::ConstantAggregateZero::get(alloca->getAllocatedType());
        llvm_cc->ir_builder->CreateBr(merge_block);

        llvm_cc->ir_builder->SetInsertPoint(pointer_notnull_block);
        llvm::Value *dereferenced_value = llvm_cc->ir_builder->CreateLoad(alloca->getAllocatedType(), argument);
        llvm_cc->ir_builder->CreateBr(merge_block);

        llvm_cc->ir_builder->SetInsertPoint(merge_block);
        llvm::PHINode *inout_value = llvm_cc->ir_builder->CreatePHI(alloca->getAllocatedType(), 2, "in_out_value");
        inout_value->addIncoming(dereferenced_value, pointer_notnull_block);
        inout_value->addIncoming(zeroinitializer, pointer_null_block);

        llvm_cc->ir_builder->CreateStore(inout_value, alloca);

        return alloca;
    }

    static llvm::AllocaInst *CreateOutputVariable(LLVMCompilerContext *llvm_cc, llvm::Function *function, Variable variable)
    {
        llvm::AllocaInst *alloca = CreateEntryBlockAlloca(llvm_cc, function, variable);
        llvm::ConstantAggregateZero *zeroinitializer = llvm::ConstantAggregateZero::get(alloca->getAllocatedType());
        llvm_cc->ir_builder->CreateStore(zeroinitializer, alloca);

        return alloca;
    }

    static llvm::AllocaInst *CreateTempVariable(LLVMCompilerContext *llvm_cc, llvm::Function *function, Variable variable)
    {
        llvm::AllocaInst *alloca = CreateEntryBlockAlloca(llvm_cc, function, variable);
        llvm::ConstantAggregateZero *zeroinitializer = llvm::ConstantAggregateZero::get(alloca->getAllocatedType());
        llvm_cc->ir_builder->CreateStore(zeroinitializer, alloca);

        return alloca;
    }

    static void StoreBackVarIntoPointer(LLVMCompilerContext *llvm_cc, llvm::Function *function, Variable variable, llvm::Argument *argument)
    {

        llvm::BasicBlock *pointer_notnull_block = llvm::BasicBlock::Create(*llvm_cc->context, "if_pointer_notnull", function);
        llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(*llvm_cc->context, "if_merge", function);

        llvm::Constant *null_pointer = llvm::Constant::getNullValue(llvm::PointerType::get(*llvm_cc->context, 0));
        llvm::Value *is_not_null = llvm_cc->ir_builder->CreateICmpNE(argument, null_pointer, "is_not_null");

        llvm_cc->ir_builder->CreateCondBr(is_not_null, pointer_notnull_block, merge_block);
        llvm_cc->ir_builder->SetInsertPoint(pointer_notnull_block);

        // load value from alloca and store in pointer
        llvm::Value *alloca_inst = llvm_cc->local_variables[variable.name];
        llvm::Type *type = TypeToLLVMType(variable.GetType(), llvm_cc);
        llvm::Value *alloca_value = llvm_cc->ir_builder->CreateLoad(type, alloca_inst);
        llvm_cc->ir_builder->CreateStore(alloca_value, argument);

        llvm_cc->ir_builder->CreateBr(pointer_notnull_block);
        llvm_cc->ir_builder->SetInsertPoint(merge_block);
    }

    static void VerifyFunction(llvm::Function *function)
    {
        std::string code_err;
        llvm::raw_string_ostream ostream(code_err);
        llvm::verifyFunction(*function, &ostream);

        std::cout << "\n"
                  << Console::FgBrightRed(code_err) << "\n";
    }

    llvm::Function *Function::LLVMGetDeclaration(LLVMCompilerContext *llvm_cc)
    {
        llvm::Function *func = llvm_cc->module->getFunction(name);
        if (func)
        {
            return func;
        }
        else
        {
            return LLVMBuildDeclaration(llvm_cc);
        }
    }

    llvm::Function *Function::LLVMBuildDeclaration(LLVMCompilerContext *llvm_cc)
    {
        std::vector<llvm::Type *> arguments;
        for (auto v : var_input)
        {
            llvm::Type *value_ptr = TypeToLLVMType(v.GetType(), llvm_cc);
            if (value_ptr)
            {
                arguments.push_back(value_ptr);
            }
            else
            {
                // TODO: emit error
            }
        }

        for (auto v : var_in_out)
        {
            llvm::Type *value_ptr = llvm::PointerType::get(*llvm_cc->context, 0);
            if (value_ptr)
            {
                arguments.push_back(value_ptr);
            }
            else
            {
                // TODO: emit error
            }
        }

        for (auto v : var_output)
        {
            llvm::Type *value_ptr = llvm::PointerType::get(*llvm_cc->context, 0);
            if (value_ptr)
            {
                arguments.push_back(value_ptr);
            }
            else
            {
                // TODO: emit error
            }
        }

        // c equivalent
        // result_type function_name(input_list, inout_list, output_list);

        llvm::Type *return_type = result ? TypeToLLVMType(result->GetType(), llvm_cc) : llvm::Type::getVoidTy(*llvm_cc->context);
        if (!return_type)
        {
            // Error
        }

        llvm::FunctionType *function_type = llvm::FunctionType::get(return_type, arguments, false);

        llvm::Function *function = llvm::Function::Create(
            function_type,
            llvm::Function::ExternalLinkage,
            name, llvm_cc->module.get());

        return function;
    }

    llvm::Function *Function::LLVMBuildBody(LLVMCompilerContext *llvm_cc)
    {
        llvm::Function *function = LLVMGetDeclaration(llvm_cc);

        // function body

        llvm::BasicBlock *bb = llvm::BasicBlock::Create(*llvm_cc->context, "entry", function);
        llvm_cc->ir_builder->SetInsertPoint(bb);

        // allocate and init local variables
        LocalScope ls;
        llvm::Function::arg_iterator argument = function->arg_begin();
        for (Variable &variable : var_input)
        {
            llvm_cc->local_variables[variable.name] = CreateInputVariable(llvm_cc, function, argument++, variable);
            ls.local_variables[variable.name] = &variable;
        }

        for (Variable &variable : var_in_out)
        {
            llvm_cc->local_variables[variable.name] = CreateInOutVariable(llvm_cc, function, argument++, variable);
            ls.local_variables[variable.name] = &variable;
        }

        for (Variable &variable : var_output)
        {
            llvm_cc->local_variables[variable.name] = CreateOutputVariable(llvm_cc, function, variable);
            ls.local_variables[variable.name] = &variable;
        }

        for (Variable &variable : var)
        {
            llvm_cc->local_variables[variable.name] = CreateTempVariable(llvm_cc, function, variable);
            ls.local_variables[variable.name] = &variable;
        }

        if (result)
        {
            llvm_cc->local_variables[result->name] = CreateTempVariable(llvm_cc, function, *result);
            ls.local_variables[result->name] = &(*result);
        }

        for (auto &s : statement_list)
        {
            s->CodeGenLLVM(&ls, llvm_cc);
        }

        // FIXME: generate return sequence

        llvm::BasicBlock *return_block = llvm::BasicBlock::Create(*llvm_cc->context, "return_block", function);

        llvm_cc->ir_builder->CreateBr(return_block);
        llvm_cc->ir_builder->SetInsertPoint(return_block);

        // store local bariables back to IN_OUT and OUTPUT pointers,

        argument = function->arg_begin();
        for (Variable &variable : var_input)
        {
            argument++; // skip inputs
        }

        for (Variable &variable : var_in_out)
        {
            StoreBackVarIntoPointer(llvm_cc, function, variable, argument++);
        }

        for (Variable &variable : var_output)
        {
            StoreBackVarIntoPointer(llvm_cc, function, variable, argument++);
        }

        if (result)
        {
            llvm::Value *alloca = llvm_cc->local_variables[result->name];
            llvm::Type *type = TypeToLLVMType(result->GetType(), llvm_cc);
            llvm::Value *value = llvm_cc->ir_builder->CreateLoad(type, alloca, "result");
            llvm_cc->ir_builder->CreateRet(value);
        }
        else
        {
            llvm_cc->ir_builder->CreateRetVoid();
        }

        // for (Variable &variable : var)
        // {
        // }

        // verify function
        VerifyFunction(function);

        return function;
    }

    void Function::LLVMGenerateDeclaration(LLVMCompilerContext *llvm_cc)
    {
        (void)LLVMGetDeclaration(llvm_cc); // oncy generate declaration if needed
    }

    void Function::LLVMGenerateDefinition(LLVMCompilerContext *llvm_cc)
    {
        (void)LLVMBuildBody(llvm_cc);
    }

}