
#include "ast1.hpp"

namespace AST
{

    llvm::Type* TypeToLLVMType(Type t, LLVMCompilerContext* llvm_cc)
    {
        if (t == Type::DataType::REAL)
        {
            return llvm::Type::getFloatTy(*llvm_cc->context);
        }
        if (t == Type::DataType::LREAL)
        {
            return llvm::Type::getDoubleTy(*llvm_cc->context);
        }
        if (t.IsInteger() || t.IsBit())
        {
            return llvm::Type::getIntNTy(*llvm_cc->context, t.GetSize());
        }
        return nullptr;
    }

    // *********************************************************************************************
    // String Helper functions

    std::string Indent(std::string str)
    {
        std::string new_str = "\t";
        for (int i = 0; i < str.size(); i++)
        {
            char c = str[i];
            new_str.push_back(c);
            if (c == '\n')
            {
                new_str.push_back('\t');
            }
        }
        return new_str;
    }

    std::string StatementListToString(StmtList list)
    {
        std::string str = "";
        bool first = true;

        for (StmtPtr stmt : list)
        {
            std::string stmt_str = stmt ? stmt->ToString() : "____";

            if (!first)
            {
                str += "\n" + stmt_str;
            }
            else
            {
                str += stmt_str;
                first = false;
            }
        }
        return Indent(str);
    }

    // *********************************************************************************************
    // ToString

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

    // *********************************************************************************************
    // LLVM Codegen

    Type VariableAccess::GetType(LocalScope *ls)
    {
        auto iter = ls->local_variables.find(variable_name);
        if(iter == ls->local_variables.end()){
            // ERROR - undefined variable
            return Type::UNNOWN;
        }
        
        return iter->second->GetType();
    }

    // *********************************************************************************************
    // LLVM Codegen

    llvm::AllocaInst *CreateEntryBlockAlloca(LLVMCompilerContext *llvm_cc, llvm::Function *function, Variable& var)
    {
        llvm::IRBuilder<> TmpB(&function->getEntryBlock(), function->getEntryBlock().begin());
        Type type = var.GetType();
        llvm::Type* lltype = TypeToLLVMType(type, llvm_cc);
        return TmpB.CreateAlloca(lltype, nullptr, var.name + "@alloca");
    }

    llvm::Function *Function::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        // c equivalent
        // result_type function_name(input_list, inout_list, output_list);

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

        // end of function declaration

        // function body

        llvm::BasicBlock *bb = llvm::BasicBlock::Create(*llvm_cc->context, "entry", function);
        llvm_cc->ir_builder->SetInsertPoint(bb);

        // allocate and init local variables
        LocalScope ls;
        llvm::Function::arg_iterator arg = function->arg_begin();
        for (Variable& v : var_input)
        {
            llvm::AllocaInst *a = CreateEntryBlockAlloca(llvm_cc, function, v);
            llvm_cc->ir_builder->CreateStore(arg++, a, false);
            llvm_cc->local_variables[v.name] = a;
            ls.local_variables[v.name] = &v;
        }

        for (Variable& v : var_in_out)
        {
            llvm_cc->local_variables[v.name] = arg++;
            ls.local_variables[v.name] = &v;
        }

        for (Variable& v : var_output)
        {
            llvm_cc->local_variables[v.name] = arg++;
            ls.local_variables[v.name] = &v;
        }

        for (Variable& v : var)
        {
            llvm::AllocaInst *a = CreateEntryBlockAlloca(llvm_cc, function, v);
            llvm_cc->local_variables[v.name] = a;
            ls.local_variables[v.name] = &v;
        }

        if (result)
        {
            llvm::AllocaInst *a = CreateEntryBlockAlloca(llvm_cc, function, *result);
            llvm_cc->local_variables[result->name] = a;
            ls.local_variables[result->name] = &(*result);
        }

        for (auto &s : statement_list)
        {
            s->CodeGenLLVM(&ls, llvm_cc);
            break; // FIXME: remove this in future
        }

        llvm::verifyFunction(*function);

        return function;
    }

    void AssignmentStatement::CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // TODO: AssignmentStatement
        if (var->GetType(ls) != expr->GetType(ls))
            return; // TODO: ERROR

        llvm::Value *ir_variable = var->LLVMGetReference(ls, llvm_cc);
        llvm::Value *ir_expr = expr->LLVMGetValue(ls, llvm_cc);

        if (!ir_variable)
            return; // TODO: ERROR
        if (!ir_expr)
            return; // TODO: ERROR

        llvm_cc->ir_builder->CreateStore(ir_expr, ir_variable, false);
    }

    void IfStatement::CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // TODO: IfStatement
    }

    void WhileStatement::CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // TODO: WhileStatement
    }

    llvm::Value *VariableAccess::LLVMGetReference(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // TODO: variable access
        llvm::Value *a = llvm_cc->local_variables[variable_name];
        if (!a)
        {
            // TODO: ERRROR
            return nullptr;
        }
        return a;
    }

    llvm::Value *VariableAccess::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // TODO: variable access
        Variable* var = ls->local_variables[variable_name];
        llvm::Value *a = llvm_cc->local_variables[variable_name];
        if (!a)
        {
            // TODO: ERRROR
            return nullptr;
        }
        llvm::Type* t = TypeToLLVMType(var->GetType(), llvm_cc);
        return llvm_cc->ir_builder->CreateLoad(t, a, variable_name);
    }

    llvm::Value *Literal::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        int tmp_val = 0; // FIXME: fix this
        switch (type)
        {
        case Type::BOOL:
        case Type::BYTE:
        case Type::WORD:
        case Type::DWORD:
        case Type::LWORD:
        case Type::SINT:
        case Type::INT:
        case Type::DINT:
        case Type::LINT:
        case Type::USINT:
        case Type::UINT:
        case Type::UDINT:
        case Type::ULINT:
            return llvm::ConstantInt::get(*llvm_cc->context, llvm::APInt(type.GetSize(), tmp_val, type.IsSignedType()));

        case Type::REAL:
            return llvm::ConstantFP::get(*llvm_cc->context, llvm::APFloat((float)tmp_val));
        case Type::LREAL:
            return llvm::ConstantFP::get(*llvm_cc->context, llvm::APFloat((double)tmp_val));

        case Type::STRUCT:
        case Type::ARRAY:
        case Type::TIME:
        case Type::LTIME:
        case Type::DATE:
        case Type::LDATE:
        case Type::TOD:
        case Type::LTOD:
        case Type::DT:
        case Type::LDT:
        case Type::STRING:
        case Type::WSTRING:
        case Type::CHAR:
        case Type::WCHAR:
            return nullptr;
        default:
            return nullptr; // TODO: ERROR
        }
    }

    llvm::Value *Exponentiation::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateBinaryIntrinsic(llvm::Intrinsic::pow, left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateBinaryIntrinsic(llvm::Intrinsic::powi, left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Add::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFAdd(left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateAdd(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Subtract::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFSub(left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateSub(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Multiply::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFMul(left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateMul(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Divide::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFDiv(left_val, right_val);

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateUDiv(left_val, right_val);

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateSDiv(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Modulo::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFRem(left_val, right_val);

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateURem(left_val, right_val);

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateSRem(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Or::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateOr(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Xor::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateXor(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *And::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateXor(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Gt::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUGT(left_val, right_val); // unordered greater than

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSGT(left_val, right_val); // signed greater than

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpUGT(left_val, right_val); // unsigned greater than

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Lt::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpULT(left_val, right_val); // unordered Less than

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSLT(left_val, right_val); // signed Less than

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpULT(left_val, right_val); // unsigned Less than

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Geq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUGE(left_val, right_val); // unordered Greater or equal

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSGE(left_val, right_val); // signed Greater or equal

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpUGE(left_val, right_val); // unsigned Greater or equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Leq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpULE(left_val, right_val); // unordered Less or equal

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSLE(left_val, right_val); // signed Less or equal

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpULE(left_val, right_val); // unsigned Less or equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Eq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUEQ(left_val, right_val); // unordered equal

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateICmpEQ(left_val, right_val); // equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Neq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUNE(left_val, right_val); // unordered not equal

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateICmpNE(left_val, right_val); // not equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *UnaryPlus::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->LLVMGetValue(ls, llvm_cc);

        if (!expr_val)
            return nullptr; // TODO: ERROR

        if (expr->GetType(ls).IsNumeric())
            return expr_val;

        return nullptr; // TODO: ERROR
    }

    llvm::Value *UnaryMinus::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->LLVMGetValue(ls, llvm_cc);

        if (!expr_val)
            return nullptr; // TODO: ERROR

        if (expr->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFNeg(expr_val);

        if (expr->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateNeg(expr_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Negation::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->LLVMGetValue(ls, llvm_cc);

        if (!expr_val)
            return nullptr; // TODO: ERROR

        if (expr->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateNot(expr_val);

        return nullptr; // TODO: ERROR
    }

}

// bool IsDirectImplicitConversionPossible(std::string source_type, std::string target_type)
// {
//     const std::map<std::pair<std::string_view, std::string_view>, bool> conversion_map = {
//         {{"BOOL", "BYTE"}, true},
//         {{"BYTE", "WORD"}, true},
//         {{"WORD", "DWORD"}, true},
//         {{"DWORD", "LWORD"}, true},

//         {{"CHAR", "STRING"}, true},
//         {{"WCHAR", "WSTRING"}, true},
//         {{"TOD", "LTOD"}, true},
//         {{"TOD", "LTOD"}, true},
//         {{"DT", "LDT"}, true},
//         {{"DATE", "LDATE"}, true},
//         {{"TIME", "LTIME"}, true},

//         {{"SINT", "INT"}, true},
//         {{"USINT", "INT"}, true},
//         {{"USINT", "UINT"}, true},

//         {{"INT", "DINT"}, true},
//         {{"INT", "REAL"}, true},

//         {{"UINT", "DINT"}, true},
//         {{"UINT", "REAL"}, true},
//         {{"UINT", "UDINT"}, true},

//         {{"REAL", "LREAL"}, true},

//         {{"DINT", "LINT"}, true},
//         {{"DINT", "LREAL"}, true},

//         {{"UDINT", "LREAL"}, true},
//         {{"UDINT", "ULINT"}, true},
//     };

//     auto iter = conversion_map.find({source_type, target_type});
//     if (iter == conversion_map.end())
//     {
//         return false;
//     }

//     return true;
// }

// void ImplicitConversion(std::string type_l, std::string type_r)
// {
// }
