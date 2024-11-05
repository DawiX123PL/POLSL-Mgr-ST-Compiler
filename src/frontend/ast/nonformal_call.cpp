#include "ast1.hpp"

static AST::Function *find_function_with_name(AST::PouList *gs, std::string name)
{
    AST::PouPtr callee = nullptr;
    for (AST::PouPtr pou : *gs)
    {
        if (!pou)
            continue;

        if (pou->name == name)
        {
            callee = pou;
            break;
        }
    }

    if (!callee)
    {
        return nullptr;
    }

    AST::Function *function = dynamic_cast<AST::Function *>(callee.get());

    return function;
}

AST::Type AST::NonformalCall::GetType(LocalScope *ls)
{
    // find function in global scope
    AST::Function *function = find_function_with_name(ls->global_scope, callee_name);

    if (!function)
    {
        return Type::UNNOWN;
    }

    // check if function returns any non-void type
    if (!function->result)
    {
        return Type::UNNOWN;
    }

    return function->result->GetType();
}

std::string AST::NonformalCall::ToString()
{
    std::string arg_list;
    for (int i = 0; i < input_arguments.size(); i++)
    {
        arg_list += i ? ", " : "";
        arg_list += input_arguments[i] ? input_arguments[i]->ToString() : "____";
    }
    return "/*non formal call*/ " + callee_name + "(" + arg_list + ")";
}

llvm::Value *AST::NonformalCall::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
{
    AST::Function *function = find_function_with_name(ls->global_scope, callee_name);
    if (!function)
    {
        // TODO: error
        return nullptr;
        ErrorManager::Create(Error::InternalCompilerError("Invalid Function Call"));
    }

    if (this->input_arguments.size() != function->var_input.size())
    {
        // TODO: error inputs number does not match
        ErrorManager::Create(Error::InternalCompilerError("Invalid Function Call"));
        return nullptr;
    }

    // check if input types match
    for (int i = 0; i < this->input_arguments.size(); i++)
    {
        if (!this->input_arguments[i])
        {
            ErrorManager::Create(Error::InternalCompilerError("Invalid Function Call"));
            return nullptr;
        }

        if (this->input_arguments[i]->GetType(ls) != function->var_input[i].GetType())
        {
            ErrorManager::Create(Error::InternalCompilerError("Invalid Function Call"));
            return nullptr;
        }
    }

    llvm::Function *ll_function = function->LLVMGetDeclaration(llvm_cc);
    llvm::Constant *null_pointer = llvm::Constant::getNullValue(llvm::PointerType::get(*llvm_cc->context, 0));

    // first argument must be global memory pointer
    std::vector<llvm::Value *> args = {llvm_cc->global_mem_ptr};

    // input
    for (int i = 0; i < this->input_arguments.size(); i++)
    {
        llvm::Value * val = this->input_arguments[i]->LLVMGetValue(ls, llvm_cc);
        args.push_back(val);
    }

    // inout
    for (int i = 0; i < function->var_in_out.size(); i++)
    {
        args.push_back(null_pointer);
    }

    // output
    for (int i = 0; i < function->var_output.size(); i++)
    {
        args.push_back(null_pointer);
    }
    
    llvm::CallInst * call_result = llvm_cc->ir_builder->CreateCall(ll_function, args, "FunctionCall");

    // check if function returns any non-void type
    if (!function->result)
    {
        ErrorManager::Create(Error::InternalCompilerError("Invalid Function Call"));
        return nullptr;
    }

    return call_result;
}
