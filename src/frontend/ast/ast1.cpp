
#include "ast1.hpp"

namespace AST
{

    llvm::Type *TypeToLLVMType(Type t, LLVMCompilerContext *llvm_cc)
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
    // LLVM Codegen

    Type VariableAccess::GetType(LocalScope *ls)
    {
        auto iter = ls->local_variables.find(variable_name);
        if (iter == ls->local_variables.end())
        {
            // ERROR - undefined variable
            return Type::UNNOWN;
        }

        return iter->second->GetType();
    }

    // *********************************************************************************************
    // LLVM helper functions

    llvm::AllocaInst *CreateEntryBlockAlloca(LLVMCompilerContext *llvm_cc, llvm::Function *function, Variable &var)
    {
        llvm::IRBuilder<> TmpB(&function->getEntryBlock(), function->getEntryBlock().begin());
        Type type = var.GetType();
        llvm::Type *lltype = TypeToLLVMType(type, llvm_cc);
        return TmpB.CreateAlloca(lltype, nullptr, var.name + ".alloca");
    }

    // *********************************************************************************************
    // LLVM Codegen

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

        llvm::Value *cond = condition->LLVMGetValue(ls, llvm_cc);

        if (!cond)
            return; // TODO: error

        llvm::Function *function = llvm_cc->ir_builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *if_block = llvm::BasicBlock::Create(*llvm_cc->context, "if", function);
        llvm::BasicBlock *else_block = llvm::BasicBlock::Create(*llvm_cc->context, "else", function); // todo else
        llvm::BasicBlock *endif_block = llvm::BasicBlock::Create(*llvm_cc->context, "end_if", function);

        llvm_cc->ir_builder->CreateCondBr(cond, if_block, else_block);

        // insert code in IF block
        llvm_cc->ir_builder->SetInsertPoint(if_block);
        for (auto &s : statement_list)
        {
            s->CodeGenLLVM(ls, llvm_cc);
        }
        llvm_cc->ir_builder->CreateBr(endif_block);

        // insert code in ELSE block
        llvm_cc->ir_builder->SetInsertPoint(else_block);
        // TODO: else block code insert here

        llvm_cc->ir_builder->CreateBr(endif_block);

        // endif block
        llvm_cc->ir_builder->SetInsertPoint(endif_block);
    }

    void WhileStatement::CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        llvm::Function *function = llvm_cc->ir_builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *condition_block = llvm::BasicBlock::Create(*llvm_cc->context, "while_condition", function);
        llvm::BasicBlock *while_block = llvm::BasicBlock::Create(*llvm_cc->context, "while_do", function);
        llvm::BasicBlock *endwhile_block = llvm::BasicBlock::Create(*llvm_cc->context, "end_while", function);

        llvm_cc->ir_builder->CreateBr(condition_block);
        llvm_cc->ir_builder->SetInsertPoint(condition_block);

        llvm::Value *cond = condition->LLVMGetValue(ls, llvm_cc);
        if (!cond)
            return; // TODO: error

        llvm_cc->ir_builder->CreateCondBr(cond, while_block, endwhile_block);
        llvm_cc->ir_builder->SetInsertPoint(while_block);

        for (auto &s : statement_list)
        {
            s->CodeGenLLVM(ls, llvm_cc);
        }

        llvm_cc->ir_builder->CreateBr(condition_block); // jump back to check condition
        llvm_cc->ir_builder->SetInsertPoint(endwhile_block);
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
        Variable *var = ls->local_variables[variable_name];
        llvm::Value *a = llvm_cc->local_variables[variable_name];
        if (!a)
        {
            // TODO: ERRROR
            return nullptr;
        }
        llvm::Type *t = TypeToLLVMType(var->GetType(), llvm_cc);
        return llvm_cc->ir_builder->CreateLoad(t, a, variable_name);
    }

    llvm::Value *Literal::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // convert boost::multiprecision to llvm::APint
        std::vector<uint64_t> bits_vector;

        bool is_negative = i_value.sign();
        boost::multiprecision::export_bits(i_value, std::back_inserter(bits_vector), 64);

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
        {
            llvm::APInt value = llvm::APInt(type.GetSize(), bits_vector);
            if (is_negative)
            {
                value.negate();
            }
            return llvm::ConstantInt::get(*llvm_cc->context, value);
        }

        case Type::REAL:
            return llvm::ConstantFP::get(*llvm_cc->context, llvm::APFloat((float)f_value));
        case Type::LREAL:
            return llvm::ConstantFP::get(*llvm_cc->context, llvm::APFloat((double)f_value));

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

    Type GlobalMemoryAccess::GetType(LocalScope *ls)
    {
        switch (size)
        {
        case 1:
            return Type::BOOL;
        case 8:
            return Type::BYTE;
        case 16:
            return Type::WORD;
        case 32:
            return Type::DWORD;
        case 64:
            return Type::LWORD;
        }
        return Type::UNNOWN;
    }

    llvm::Value *GlobalMemoryAccess::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {

        // struct GlobalMem
        // {
        //     uint8_t input[max_io_modules][bytes_per_module];  // %Ix.x.x
        //     uint8_t output[max_io_modules][bytes_per_module]; // %Qx.x.x
        //     uint8_t memory[max_io_modules][bytes_per_module]; // %Mx.x
        // };
        // module '0' means adressing CPU module

        // global = {I, Q, M}

        llvm::IntegerType *u8_type = llvm::IntegerType::getInt8Ty(*llvm_cc->context);
        llvm::IntegerType *u16_type = llvm::IntegerType::getInt16Ty(*llvm_cc->context);
        llvm::IntegerType *u32_type = llvm::IntegerType::getInt32Ty(*llvm_cc->context);
        llvm::IntegerType *u64_type = llvm::IntegerType::getInt64Ty(*llvm_cc->context);

        // FIXME: check if address in bounds

        // adresy w gep {0, IQM, Module, ByteInModule}
        int iqm_address = (int)location;
        int module_number = address[0];
        int byte_in_module = address[1];

        std::initializer_list<llvm::Value *> gep_address =
            {
                llvm::ConstantInt::get(u32_type, llvm::APInt(32, 0, false)),
                llvm::ConstantInt::get(u32_type, llvm::APInt(32, iqm_address, false)),
                llvm::ConstantInt::get(u32_type, llvm::APInt(32, module_number, false)),
                llvm::ConstantInt::get(u32_type, llvm::APInt(32, byte_in_module, false)),
            };

        llvm::Value *accessed_address = llvm_cc->ir_builder->CreateGEP(llvm_cc->global_mem_type, llvm_cc->global_mem_ptr, gep_address, this->ToString());

        if (size == 1)
        {
            llvm::LoadInst *tmp_8bit = llvm_cc->ir_builder->CreateLoad(u8_type, accessed_address, this->ToString() + "_value_tmp_8bit");
            llvm::Constant *tmp_mask = llvm::ConstantInt::get(u8_type, llvm::APInt(8, 1 << address[2], false));
            return llvm_cc->ir_builder->CreateAnd(tmp_8bit, tmp_mask, this->ToString() + "_value");
        }

        if (size == 8)
        {
            return llvm_cc->ir_builder->CreateLoad(u8_type, accessed_address, this->ToString() + "_value");
        }

        if (size == 16)
        {
            return llvm_cc->ir_builder->CreateLoad(u16_type, accessed_address, this->ToString() + "_value");
        }

        if (size == 32)
        {
            return llvm_cc->ir_builder->CreateLoad(u32_type, accessed_address, this->ToString() + "_value");
        }

        if (size == 64)
        {
            return llvm_cc->ir_builder->CreateLoad(u64_type, accessed_address, this->ToString());
        }

        return nullptr;
    }

    llvm::Value *GlobalMemoryAccess::LLVMGetReference(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        return nullptr;
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
