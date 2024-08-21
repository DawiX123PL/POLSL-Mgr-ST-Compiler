#include "ast1.hpp"

static AST::Function* find_function_with_name(AST::PouList *gs, std::string name)
{
    AST::PouPtr callee;
    for (AST::PouPtr pou : *gs)
    {
        if (pou)
            continue;

        if (pou->name == name)
        {
            callee = pou;
            break;
        }
    }

    if(!callee){
        return nullptr;
    }

    AST::Function *function = dynamic_cast<AST::Function *>(callee.get());

    return function;
}

AST::Type AST::FormalCall::GetType(LocalScope *ls)
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

std::string AST::FormalCall::ToString()
{
    std::string arg_list;
    for (int i = 0; i < input_arguments.size(); i++)
    {
        arg_list += i ? ", " : "";
        arg_list += input_arguments[i].first ? input_arguments[i].first->ToString() : "____";
        arg_list += " := ";
        arg_list += input_arguments[i].second ? input_arguments[i].second->ToString() : "____";
    }
    for (int i = 0; i < output_arguments.size(); i++)
    {
        arg_list += i ? ", " : "";
        arg_list += output_arguments[i].first ? output_arguments[i].first->ToString() : "____";
        arg_list += " => ";
        arg_list += output_arguments[i].second ? output_arguments[i].second->ToString() : "____";
    }
    return "/*non formal call*/ " + callee_name + "(" + arg_list + ")";
}

llvm::Value *AST::FormalCall::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
{
    return nullptr;
}
