#include "ast1.hpp"
#include "../../console/color.hpp"

namespace AST
{

    std::string Program::ToString()
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

        return "{PROGRAM  " + name + "\n" + vars_str + "\n" + StatementListToString(statement_list) + "\n}";
    }

    static void VerifyFunction(llvm::Function *function)
    {
        std::string code_err;
        llvm::raw_string_ostream ostream(code_err);
        llvm::verifyFunction(*function, &ostream);

        if (code_err.size())
        {
            std::cout << "\n"
                      << Console::FgBrightRed(code_err) << "\n";
        }
    }

    llvm::FunctionType *Program::GetFunctionType(LLVMCompilerContext *llvm_cc)
    {
        // create function declaration
        // c equivalent
        // void ProgramName(PointerToGlobalMemory, PointerToProgramStruct);
        // PointerToProgramStruct == this in c++

        llvm::Type *global_mem_ptr = llvm::PointerType::get(*llvm_cc->context, 0);
        llvm::Type *this_pointer = llvm::PointerType::get(*llvm_cc->context, 0);

        std::vector<llvm::Type *> arguments =
            {
                global_mem_ptr,
                this_pointer,
            };

        llvm::Type *void_type = llvm::Type::getVoidTy(*llvm_cc->context);

        return llvm::FunctionType::get(void_type, arguments, false);
    };

    llvm::Function *Program::LLVMCreateInitDeclaration(LLVMCompilerContext *llvm_cc)
    {
        llvm::FunctionType *function_type = GetFunctionType(llvm_cc);

        llvm::Function *function = llvm::Function::Create(
            function_type,
            llvm::Function::ExternalLinkage,
            name + ".init",
            llvm_cc->module.get());

        return function;
    }

    llvm::Function *Program::LLVMCreateBodyDeclaration(LLVMCompilerContext *llvm_cc)
    {
        llvm::FunctionType *function_type = GetFunctionType(llvm_cc);

        llvm::Function *function = llvm::Function::Create(
            function_type,
            llvm::Function::ExternalLinkage,
            name,
            llvm_cc->module.get());

        return function;
    }

    llvm::Function *Program::LLVMGetInitDeclaration(LLVMCompilerContext *llvm_cc)
    {
        llvm::Function *func = llvm_cc->module->getFunction(name + ".init");
        if (func)
        {
            return func;
        }
        else
        {
            return LLVMCreateInitDeclaration(llvm_cc);
        }
    }

    llvm::Function *Program::LLVMGetBodyDeclaration(LLVMCompilerContext *llvm_cc)
    {
        llvm::Function *func = llvm_cc->module->getFunction(name);
        if (func)
        {
            return func;
        }
        else
        {
            return LLVMCreateBodyDeclaration(llvm_cc);
        }
    }

    llvm::StructType *Program::LLVMGetStructType(LLVMCompilerContext *llvm_cc)
    {
        std::string struct_name = name + ".struct";

        // check if structure was already defined
        for (llvm::StructType *str_type : llvm_cc->module->getIdentifiedStructTypes())
        {
            if (str_type->getName() == struct_name)
                return str_type;
        }

        // create structure definition if not already created
        std::vector<llvm::Type *> variables;

        for (auto &v : var)
        {
            variables.emplace_back(TypeToLLVMType(v.GetType(), llvm_cc));
        }

        // create packed struct - to minimize memory consumption
        llvm::StructType *prog_struct = llvm::StructType::create(*llvm_cc->context, variables, struct_name, true);

        return prog_struct;
    }

    void Program::LLVMCreateInit(AST::PouList* gs, LLVMCompilerContext *llvm_cc)
    {
        llvm::Function *function = LLVMGetInitDeclaration(llvm_cc);
        llvm::StructType *struct_type = LLVMGetStructType(llvm_cc);

        // function body

        llvm::BasicBlock *bb = llvm::BasicBlock::Create(*llvm_cc->context, "entry", function);
        llvm_cc->ir_builder->SetInsertPoint(bb);

        // allocate and init local variables
        LocalScope ls; // do not populate ls fields,

        llvm::Function::arg_iterator argument = function->arg_begin();
        llvm_cc->local_variables.clear();
        llvm_cc->global_mem_ptr = argument;
        argument++; // skip GlobalMemoryPointer

        int struct_element_index = 0;
        for (Variable &variable : var)
        {
            llvm::Value *element_ptr = llvm_cc->ir_builder->CreateStructGEP(struct_type, argument, struct_element_index, variable.name);

            llvm::Value *initializer_value;
            if (variable.initial_value)
            {
                initializer_value = variable.initial_value->LLVMGetValue(&ls, llvm_cc);
            }
            else
            {
                llvm::Type *type = TypeToLLVMType(variable.GetType(), llvm_cc);
                initializer_value = llvm::Constant::getNullValue(type); // zero initializer
            }

            // initialize structure variables
            llvm_cc->ir_builder->CreateStore(initializer_value, element_ptr);

            struct_element_index++;
        }

        // generate return keyword
        llvm_cc->ir_builder->CreateRetVoid();

        // verify function
        VerifyFunction(function);
    }

    void Program::LLVMCreateBody(AST::PouList* gs, LLVMCompilerContext *llvm_cc)
    {
        llvm::Function *function = LLVMGetBodyDeclaration(llvm_cc);
        llvm::StructType *struct_type = LLVMGetStructType(llvm_cc);

        // function body

        llvm::BasicBlock *bb = llvm::BasicBlock::Create(*llvm_cc->context, "entry", function);
        llvm_cc->ir_builder->SetInsertPoint(bb);

        // allocate and init local variables
        LocalScope ls;
        ls.global_scope = gs;

        llvm::Function::arg_iterator argument = function->arg_begin();
        llvm_cc->global_mem_ptr = argument;
        argument++; // skip GlobalMemoryPointer

        llvm_cc->local_variables.clear();

        int struct_element_index = 0;
        for (Variable &variable : var)
        {
            llvm::Value *element_ptr = llvm_cc->ir_builder->CreateStructGEP(struct_type, argument, struct_element_index, variable.name);

            llvm_cc->local_variables[variable.name] = element_ptr;
            ls.local_variables[variable.name] = &variable;

            struct_element_index++;
        }

        for (auto &s : statement_list)
        {
            s->CodeGenLLVM(&ls, llvm_cc);
        }

        // generate return keyword
        llvm_cc->ir_builder->CreateRetVoid();

        // verify function
        VerifyFunction(function);
    }

    void Program::LLVMGenerateDeclaration(AST::PouList* gs, LLVMCompilerContext *llvm_cc)
    {
        (void)LLVMCreateInitDeclaration(llvm_cc);
        (void)LLVMCreateBodyDeclaration(llvm_cc);
    };

    void Program::LLVMGenerateDefinition(AST::PouList* gs, LLVMCompilerContext *llvm_cc)
    {
        if (!is_extern)
        {
            LLVMCreateInit(gs, llvm_cc);
            LLVMCreateBody(gs, llvm_cc);
        }
    };

}
