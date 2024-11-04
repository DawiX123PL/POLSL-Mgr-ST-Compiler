
#include "ast1.hpp"

#include "exception.hpp"

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
            ErrorManager::Create(Error::UndefinedVariable(position, variable_name));
            throw Exception{};
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
        if (var->GetType(ls) != expr->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, ":=", var->GetType(ls), expr->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *ir_expr = expr->LLVMGetValue(ls, llvm_cc);

        if (!ir_expr)
            return; // TODO: ERROR

        Lvalue *l_value = dynamic_cast<Lvalue *>(var.get());
        if (!l_value)
            return; // TODO: Error: expected lvalue

        l_value->LLVMSetValue(ls, llvm_cc, ir_expr);
    }

    void NonAsssingingStatement::CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // just generate llvm ir code
        // do not assign result
        (void)expr->LLVMGetValue(ls, llvm_cc);
    }

    void IfStatement::CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (condition->GetType(ls) != Type::BOOL)
        {
            ErrorManager::Create(Error::ConditionShouldBeBool(position, condition->GetType(ls)));
            throw Exception{};
        }

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
            try
            {

                if (s)
                    s->CodeGenLLVM(ls, llvm_cc);
            }
            catch (...)
            {
            }
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
        if (condition->GetType(ls) != Type::BOOL)
        {
            ErrorManager::Create(Error::ConditionShouldBeBool(position, condition->GetType(ls)));
            throw Exception{};
        }

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
            try
            {

                if (s)
                    s->CodeGenLLVM(ls, llvm_cc);
            }
            catch (...)
            {
            }
        }

        llvm_cc->ir_builder->CreateBr(condition_block); // jump back to check condition
        llvm_cc->ir_builder->SetInsertPoint(endwhile_block);
    }

    void VariableAccess::LLVMSetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc, llvm::Value *value)
    {
        // TODO: variable access
        llvm::Value *a = llvm_cc->local_variables[variable_name];
        if (!a)
        {
            ErrorManager::Create(Error::UndefinedVariable(position, variable_name));
            throw Exception{};
        }

        llvm_cc->ir_builder->CreateStore(value, a);
    }

    llvm::Value *VariableAccess::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // TODO: variable access
        Variable *var = ls->local_variables[variable_name];
        llvm::Value *a = llvm_cc->local_variables[variable_name];
        if (!a)
        {
            ErrorManager::Create(Error::UndefinedVariable(position, variable_name));
            throw Exception{};
        }

        llvm::Type *t = TypeToLLVMType(var->GetType(), llvm_cc);
        return llvm_cc->ir_builder->CreateLoad(t, a, variable_name);
    }

    llvm::Value *Literal::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        // convert boost::multiprecision to llvm::APint
        std::vector<uint64_t> bits_vector;

        bool is_positive = i_value.sign();
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
            if (!is_positive)
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
        default:
            ErrorManager::Create(Error::InvalidLiteralType(position));
            throw Exception{};
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

        std::initializer_list<llvm::Value *> gep_address;
        if (location == Location::Memory)
        {
            gep_address =
                {
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, 0, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, iqm_address, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, byte_in_module, false)),
                };
        }
        else
        {
            gep_address =
                {
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, 0, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, iqm_address, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, module_number, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, byte_in_module, false)),
                };
        }

        llvm::Value *accessed_address = llvm_cc->ir_builder->CreateGEP(llvm_cc->global_mem_type, llvm_cc->global_mem_ptr, gep_address, this->ToString());

        if (size == 1)
        {
            llvm::LoadInst *tmp_byte = llvm_cc->ir_builder->CreateLoad(u8_type, accessed_address, this->ToString() + "_value_tmp_8bit");
            llvm::Constant *tmp_mask = llvm::ConstantInt::get(u8_type, llvm::APInt(8, 1 << address.back(), false));
            llvm::Value *tmp_8bit_val = llvm_cc->ir_builder->CreateAnd(tmp_byte, tmp_mask, this->ToString() + "_value_8bit");

            // check if non-zero
            llvm::Constant *zero = llvm::ConstantInt::get(u8_type, 0, false);
            return llvm_cc->ir_builder->CreateICmpNE(tmp_8bit_val, zero, this->ToString() + "_value");
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

        ErrorManager::Create(Error::InvalidMemoryAddress(position));
        throw Exception{};
    }

    void GlobalMemoryAccess::LLVMSetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc, llvm::Value *value)
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
        std::vector<llvm::Value *> gep_address;

        if (location == Location::Memory)
        {
            int byte_address = address[0];

            gep_address =
                {
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, 0, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, iqm_address, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, byte_address, false)),
                };
        }
        else
        {
            int module_number = address[0];
            int byte_in_module = address[1];

            gep_address =
                {
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, 0, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, iqm_address, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, module_number, false)),
                    llvm::ConstantInt::get(u32_type, llvm::APInt(32, byte_in_module, false)),
                };
        }

        llvm::Value *accessed_address = llvm_cc->ir_builder->CreateGEP(llvm_cc->global_mem_type, llvm_cc->global_mem_ptr, gep_address, this->ToString());

        if (size == 1)
        {

            // step1 load byte
            llvm::LoadInst *loaded_byte = llvm_cc->ir_builder->CreateLoad(u8_type, accessed_address, this->ToString() + "_value_tmp_8bit");

            // step2 clear selected bit by masking it
            uint8_t clean_mask = ~(1 << address.back());
            llvm::Value *masked_value = llvm_cc->ir_builder->CreateAnd(loaded_byte, clean_mask);

            // step3 set selected bit
            llvm::Value *zext_val = llvm_cc->ir_builder->CreateZExt(value, u8_type);
            llvm::Value *set_mask = llvm_cc->ir_builder->CreateShl(zext_val, address.back());
            llvm::Value *calculated_byte = llvm_cc->ir_builder->CreateOr(masked_value, set_mask);

            // step4 store result
            llvm_cc->ir_builder->CreateStore(calculated_byte, accessed_address);
            return;
        }

        if (size == 8)
        {
            llvm_cc->ir_builder->CreateStore(value, accessed_address);
            return;
        }

        if (size == 16)
        {
            llvm_cc->ir_builder->CreateStore(value, accessed_address);
            return;
        }

        if (size == 32)
        {
            llvm_cc->ir_builder->CreateStore(value, accessed_address);
            return;
        }

        if (size == 64)
        {
            llvm_cc->ir_builder->CreateStore(value, accessed_address);
            return;
        }

        ErrorManager::Create(Error::InvalidMemoryAddress(position));
        throw Exception{};
    }

    llvm::Value *Exponentiation::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "**", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateBinaryIntrinsic(llvm::Intrinsic::pow, left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateBinaryIntrinsic(llvm::Intrinsic::powi, left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "**", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Add::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "+", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFAdd(left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateAdd(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "+", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Subtract::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "-", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFSub(left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateSub(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "-", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Multiply::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "*", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFMul(left_val, right_val);

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateMul(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "*", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Divide::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "/", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFDiv(left_val, right_val);

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateUDiv(left_val, right_val);

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateSDiv(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "/", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Modulo::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "MOD", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFRem(left_val, right_val);

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateURem(left_val, right_val);

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateSRem(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "MOD", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Or::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "OR", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateOr(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "OR", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Xor::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "XOR", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateXor(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "XOR", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *And::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "AND", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateXor(left_val, right_val);

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "AND", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Gt::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, ">", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUGT(left_val, right_val); // unordered greater than

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSGT(left_val, right_val); // signed greater than

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpUGT(left_val, right_val); // unsigned greater than

        ErrorManager::Create(Error::InvalidBinaryOperation(position, ">", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Lt::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "<", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpULT(left_val, right_val); // unordered Less than

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSLT(left_val, right_val); // signed Less than

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpULT(left_val, right_val); // unsigned Less than

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "<", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Geq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, ">=", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUGE(left_val, right_val); // unordered Greater or equal

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSGE(left_val, right_val); // signed Greater or equal

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpUGE(left_val, right_val); // unsigned Greater or equal

        ErrorManager::Create(Error::InvalidBinaryOperation(position, ">=", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Leq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "<=", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpULE(left_val, right_val); // unordered Less or equal

        if (left->GetType(ls).IsSignedInteger())
            return llvm_cc->ir_builder->CreateICmpSLE(left_val, right_val); // signed Less or equal

        if (left->GetType(ls).IsUnsignedInteger())
            return llvm_cc->ir_builder->CreateICmpULE(left_val, right_val); // unsigned Less or equal

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "<=", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Eq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "=", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUEQ(left_val, right_val); // unordered equal

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateICmpEQ(left_val, right_val); // equal

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "=", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Neq::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        if (left->GetType(ls) != right->GetType(ls))
        {
            ErrorManager::Create(Error::InvalidBinaryOperation(position, "<>", left->GetType(ls), right->GetType(ls)));
            throw Exception{};
        }

        llvm::Value *left_val = left->LLVMGetValue(ls, llvm_cc);
        llvm::Value *right_val = right->LLVMGetValue(ls, llvm_cc);

        assert(left_val && right_val);

        if (left->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFCmpUNE(left_val, right_val); // unordered not equal

        if (left->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateICmpNE(left_val, right_val); // not equal

        ErrorManager::Create(Error::InvalidBinaryOperation(position, "<>", left->GetType(ls), right->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *UnaryPlus::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->LLVMGetValue(ls, llvm_cc);

        assert(expr_val);

        if (expr->GetType(ls).IsNumeric())
            return expr_val;

        ErrorManager::Create(Error::InvalidUnaryOperation(position, "+", expr->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *UnaryMinus::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->LLVMGetValue(ls, llvm_cc);

        assert(expr_val);

        if (expr->GetType(ls).IsFloatingPoint())
            return llvm_cc->ir_builder->CreateFNeg(expr_val);

        if (expr->GetType(ls).IsInteger())
            return llvm_cc->ir_builder->CreateNeg(expr_val);

        ErrorManager::Create(Error::InvalidUnaryOperation(position, "-", expr->GetType(ls)));
        throw Exception{};
    }

    llvm::Value *Negation::LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc)
    {
        llvm::Value *expr_val = expr->LLVMGetValue(ls, llvm_cc);

        assert(expr_val);

        if (expr->GetType(ls).IsBit())
            return llvm_cc->ir_builder->CreateNot(expr_val);

        ErrorManager::Create(Error::InvalidUnaryOperation(position, "NOT", expr->GetType(ls)));
        throw Exception{};
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
