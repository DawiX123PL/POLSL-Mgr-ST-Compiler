
#include "ast1.hpp"

namespace AST
{

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



    llvm::Value *Literal::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
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

    llvm::Value *Exponentiation::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateBinaryIntrinsic(llvm::Intrinsic::pow, left_val, right_val);

        if (left->type.IsInteger())
            return llvm_cc->ir_builder->CreateBinaryIntrinsic(llvm::Intrinsic::powi, left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Add::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFAdd(left_val, right_val);

        if (left->type.IsInteger())
            return llvm_cc->ir_builder->CreateAdd(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Subtract::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFSub(left_val, right_val);

        if (left->type.IsInteger())
            return llvm_cc->ir_builder->CreateSub(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Multiply::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFMul(left_val, right_val);

        if (left->type.IsInteger())
            return llvm_cc->ir_builder->CreateMul(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Divide::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFDiv(left_val, right_val);

        if (left->type.IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateUDiv(left_val, right_val);

        if (left->type.IsSignedInteger())
            return llvm_cc->ir_builder->CreateSDiv(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Modulo::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFRem(left_val, right_val);

        if (left->type.IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateURem(left_val, right_val);

        if (left->type.IsSignedInteger())
            return llvm_cc->ir_builder->CreateSRem(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Or::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsBit())
            return llvm_cc->ir_builder->CreateOr(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Xor::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsBit())
            return llvm_cc->ir_builder->CreateXor(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *And::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsBit())
            return llvm_cc->ir_builder->CreateXor(left_val, right_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Gt::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUGT(left_val, right_val); // unordered greater than

        if (left->type.IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSGT(left_val, right_val); // signed greater than

        if (left->type.IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpUGT(left_val, right_val); // unsigned greater than

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Lt::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpULT(left_val, right_val); // unordered Less than

        if (left->type.IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSLT(left_val, right_val); // signed Less than

        if (left->type.IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpULT(left_val, right_val); // unsigned Less than

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Geq::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUGE(left_val, right_val); // unordered Greater or equal

        if (left->type.IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSGE(left_val, right_val); // signed Greater or equal

        if (left->type.IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpUGE(left_val, right_val); // unsigned Greater or equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Leq::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpULE(left_val, right_val); // unordered Less or equal

        if (left->type.IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSLE(left_val, right_val); // signed Less or equal

        if (left->type.IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpULE(left_val, right_val); // unsigned Less or equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Eq::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUEQ(left_val, right_val); // unordered equal

        if (left->type.IsInteger())
            return llvm_cc->ir_builder->CreateICmpEQ(left_val, right_val); // equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Neq::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        if (left->type != right->type)
            return nullptr; // TODO: ERROR

        llvm::Value *left_val = left->CodeGenLLVM(llvm_cc);
        llvm::Value *right_val = left->CodeGenLLVM(llvm_cc);

        if (!left_val)
            return nullptr; // TODO: ERROR
        if (!right_val)
            return nullptr; // TODO: ERROR

        if (left->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUNE(left_val, right_val); // unordered not equal

        if (left->type.IsInteger())
            return llvm_cc->ir_builder->CreateICmpNE(left_val, right_val); // not equal

        return nullptr; // TODO: ERROR
    }

    llvm::Value *UnaryPlus::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->CodeGenLLVM(llvm_cc);

        if (!expr_val)
            return nullptr; // TODO: ERROR

        if (expr->type.IsNumeric())
            return expr_val;

        return nullptr; // TODO: ERROR
    }

    llvm::Value *UnaryMinus::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->CodeGenLLVM(llvm_cc);

        if (!expr_val)
            return nullptr; // TODO: ERROR

        if (expr->type.IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFNeg(expr_val);

        if (expr->type.IsInteger())
            return llvm_cc->ir_builder->CreateNeg(expr_val);

        return nullptr; // TODO: ERROR
    }

    llvm::Value *Negation::CodeGenLLVM(LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->CodeGenLLVM(llvm_cc);

        if (!expr_val)
            return nullptr; // TODO: ERROR

        if (expr->type.IsBit())
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
