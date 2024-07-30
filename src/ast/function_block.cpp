#include "ast1.hpp"



namespace AST{


    std::string FunctionBlock::ToString()
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

        return "{FUNCTION_BLOCK  " + name + "\n" + vars_str + "\n" + StatementListToString(statement_list) + "\n}";
    }

    void FunctionBlock::LLVMGenerateDeclaration(LLVMCompilerContext *llvm_cc)
    {}
    void FunctionBlock::LLVMGenerateDefinition(LLVMCompilerContext *llvm_cc)
    {}
}