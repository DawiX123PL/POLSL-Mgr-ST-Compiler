#include "ast.hpp"

#include <iostream>

namespace AST
{

    DataType StringToDataType(std::string str)
    {
        if (str == "BOOL")
            return DataType::BOOL;
        if (str == "SINT")
            return DataType::SINT;
        if (str == "INT")
            return DataType::INT;
        if (str == "DINT")
            return DataType::DINT;
        if (str == "LINT")
            return DataType::LINT;
        if (str == "USINT")
            return DataType::USINT;
        if (str == "UINT")
            return DataType::UINT;
        if (str == "UDINT")
            return DataType::UDINT;
        if (str == "ULINT")
            return DataType::ULINT;
        if (str == "REAL")
            return DataType::REAL;
        if (str == "LREAL")
            return DataType::LREAL;

        return DataType::UNNOWN;
    }

    llvm::Type *DataTypeToLLVMType(CompilerContext *cc, DataType type)
    {
        switch (type)
        {
        case DataType::BOOL:
            return llvm::Type::getInt1Ty(*cc->llvm_context);
        case DataType::SINT:
            return llvm::Type::getInt8Ty(*cc->llvm_context);
        case DataType::INT:
            return llvm::Type::getInt16Ty(*cc->llvm_context);
        case DataType::DINT:
            return llvm::Type::getInt32Ty(*cc->llvm_context);
        case DataType::LINT:
            return llvm::Type::getInt64Ty(*cc->llvm_context);
        case DataType::USINT:
            return llvm::Type::getInt8Ty(*cc->llvm_context);
        case DataType::UINT:
            return llvm::Type::getInt16Ty(*cc->llvm_context);
        case DataType::UDINT:
            return llvm::Type::getInt32Ty(*cc->llvm_context);
        case DataType::ULINT:
            return llvm::Type::getInt64Ty(*cc->llvm_context);
        case DataType::REAL:
            return llvm::Type::getFloatTy(*cc->llvm_context);
        case DataType::LREAL:
            return llvm::Type::getDoubleTy(*cc->llvm_context);
        }

        return nullptr;
    }

    std::string Function::CodeGenCHeader()
    {

        std::string c_header;

        c_header +=
            "#pragma once\n"
            "\n"
            "#ifndef PLC_DATA_TYPES\n"
            "#define PLC_DATA_TYPES\n"
            "\n"
            "#define BOOL     uint8_t\n"
            "#define SINT     uint8_t\n"
            "#define INT      int16_t\n"
            "#define DINT     int32_t\n"
            "#define LINT     int64_t\n"
            "#define USINT    int8_t\n"
            "#define UINT     uint16_t\n"
            "#define UDINT    uint32_t\n"
            "#define ULINT    uint64_t\n"
            "#define REAL     float\n"
            "#define LREAL    double\n"
            "\n"
            "#endif\n\n";

        c_header += "void " + name + "(";

        // step 1.1 - fill VAR_INPUT;
        for (int i = 0; i < var_input.size(); i++)
        {
            if (i != 0)
                c_header += ",";
            c_header += " SINT " + var_input[i].GetName();
        }

        // step 1.2 - fill VAR_IN_OUT;
        for (int i = 0; i < var_in_out.size(); i++)
        {
            c_header += ", SINT* " + var_in_out[i].GetName();
        }

        // step 1.3 - fill VAR_OUTPUT;
        for (int i = 0; i < var_output.size(); i++)
        {
            c_header += ", SINT* " + var_output[i].GetName();
        }
        c_header += ", SINT* " + name;
        c_header += ");\n\n";

        return c_header;
    };

    llvm::Function *Function::GenerateLLVMFunctionPrototype(CompilerContext *cc)
    {
        // step 1 - create declaration of function protorype

        std::vector<llvm::Type *> args;

        // step 1.1 - fill VAR_INPUT;
        for (int i = 0; i < var_input.size(); i++)
        {
            args.push_back(DataTypeToLLVMType(cc, var_input[i].GetType()));
        }

        // step 1.2 - fill VAR_IN_OUT;
        for (int i = 0; i < var_in_out.size(); i++)
        {
            auto ptr = llvm::PointerType::get(DataTypeToLLVMType(cc, var_in_out[i].GetType()), 0);
            args.push_back(ptr);
        }

        // step 1.3 - fill VAR_OUTPUT;
        for (int i = 0; i < var_output.size(); i++)
        {
            auto ptr = llvm::PointerType::get(DataTypeToLLVMType(cc, var_output[i].GetType()), 0);
            args.push_back(ptr);
        }

        // step 1.4 - fill return value;
        {
            auto ptr = llvm::PointerType::get(DataTypeToLLVMType(cc, var_return.GetType()), 0);
            args.push_back(ptr);
        }

        // step 2 - create function type
        llvm::FunctionType *function_type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(*cc->llvm_context), args, false);

        // step 3 - create function prototype
        llvm::Function *function =
            llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, name, cc->llvm_module.get());

        return function;
    }

    void Function::LLVMAssignArgumentNames(CompilerContext *cc, llvm::Function *function)
    {
        auto arg_iter = function->arg_begin();
        for (int i = 0; i < var_input.size(); i++)
        {
            arg_iter->setName(var_input[i].GetName());
            arg_iter++;
        }

        for (int i = 0; i < var_in_out.size(); i++)
        {
            arg_iter->setName(var_in_out[i].GetName());
            arg_iter++;
        }

        for (int i = 0; i < var_output.size(); i++)
        {
            arg_iter->setName(var_output[i].GetName());
            arg_iter++;
        }

        arg_iter->setName(name);
    }

    llvm::AllocaInst *GenerateEntryBlockAlloca(CompilerContext *cc, llvm::Function *function, VariableDeclaration variable)
    {
        // IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
        // return TmpB.CreateAlloca(Type::getDoubleTy(*TheContext), nullptr, VarName);

        llvm::IRBuilder<> ir_builder_tmp(&function->getEntryBlock(), function->getEntryBlock().begin());

        // llvm::ConstantFP::get(*cc->llvm_context, llvm::APInt(value_ui, 1));
        llvm::Type *type = nullptr;
        switch (variable.GetType())
        {
        case DataType::BOOL:
            type = llvm::Type::getInt1Ty(*cc->llvm_context);
            break; /**/
        case DataType::SINT:
            type = llvm::Type::getInt8Ty(*cc->llvm_context);
            break; /**/
        case DataType::INT:
            type = llvm::Type::getInt16Ty(*cc->llvm_context);
            break; /**/
        case DataType::DINT:
            type = llvm::Type::getInt32Ty(*cc->llvm_context);
            break; /**/
        case DataType::LINT:
            type = llvm::Type::getInt64Ty(*cc->llvm_context);
            break; /**/
        case DataType::USINT:
            type = llvm::Type::getInt8Ty(*cc->llvm_context);
            break; /**/
        case DataType::UINT:
            type = llvm::Type::getInt16Ty(*cc->llvm_context);
            break; /**/
        case DataType::UDINT:
            type = llvm::Type::getInt32Ty(*cc->llvm_context);
            break; /**/
        case DataType::ULINT:
            type = llvm::Type::getInt64Ty(*cc->llvm_context);
            break; /**/
        case DataType::REAL:
            type = llvm::Type::getFloatTy(*cc->llvm_context);
            break; /**/
        case DataType::LREAL:
            type = llvm::Type::getDoubleTy(*cc->llvm_context);
            break; /**/
        }

        return ir_builder_tmp.CreateAlloca(type, nullptr, variable.GetName() + "_alloca");
    }

    void Function::AllocAndInitLocalVariables(CompilerContext *cc, llvm::Function *function)
    {

        // create alloca instances
        // list of all allocas
        std::vector<AST::VariableDeclaration> alloca_vars;
        alloca_vars.insert(alloca_vars.end(), var_input.begin(), var_input.end());
        alloca_vars.insert(alloca_vars.end(), var_in_out.begin(), var_in_out.end());
        alloca_vars.insert(alloca_vars.end(), var_output.begin(), var_output.end());
        alloca_vars.insert(alloca_vars.end(), var_temp.begin(), var_temp.end());
        alloca_vars.insert(alloca_vars.end(), var_return);

        for (int i = 0; i < alloca_vars.size(); i++)
        {
            // create alloca instance
            llvm::AllocaInst *inst = GenerateEntryBlockAlloca(cc, function, alloca_vars[i]);
            CompilerContext::LocalVariable local_Var(alloca_vars[i].GetType(), inst);
            cc->local_variables[alloca_vars[i].GetName()] = local_Var;
        }

        // initialize VAR_OUTPUT and VAR variables:
        // list of variables with default or custom value;
        std::vector<AST::VariableDeclaration> initializable_vars;
        initializable_vars.insert(initializable_vars.end(), var_output.begin(), var_output.end());
        initializable_vars.insert(initializable_vars.end(), var_temp.begin(), var_temp.end());
        initializable_vars.insert(initializable_vars.end(), var_return);

        for (int i = 0; i < initializable_vars.size(); i++)
        {
            AST::VariableDeclaration initializable_var = initializable_vars[i];

            auto local_var = cc->local_variables[initializable_var.GetName()];
            ExprPtr initial_expr = initializable_var.GetInitialValue();

            llvm::AllocaInst *inst = local_var.llvm_alloca_instance;
            llvm::Value *init_value;

            if (initial_expr == nullptr)
            {
                init_value = llvm::ConstantAggregateZero::get(inst->getAllocatedType());
            }
            else
            {
                init_value = initial_expr->CodeGenLLVM(cc);
            }

            cc->llvm_ir_builder->CreateStore(init_value, inst);
        }

        // initialize VAR_INPUT variables:
        for (int i = 0; i < var_input.size(); i++)
        {
            AST::VariableDeclaration var = var_input[i];

            auto local_var = cc->local_variables[var.GetName()];
            ExprPtr initial_expr = var.GetInitialValue();

            llvm::AllocaInst *inst = local_var.llvm_alloca_instance;
            llvm::Value *init_value = function->getArg(i);

            cc->llvm_ir_builder->CreateStore(init_value, inst);
        }

        // initialize VAR_IN_OUT variables:
        const int var_intout_offser = var_input.size();

        for (int i = 0; i < var_in_out.size(); i++)
        {
            AST::VariableDeclaration var = var_in_out[i];

            auto local_var = cc->local_variables[var.GetName()];
            ExprPtr initial_expr = var.GetInitialValue();

            llvm::AllocaInst *inst = local_var.llvm_alloca_instance;
            llvm::Value *arg_val = function->getArg(var_intout_offser + i);

            // cc->llvm_ir_builder->CreateStore(arg_val, inst);
            auto load = cc->llvm_ir_builder->CreateLoad(DataTypeToLLVMType(cc, var.GetType()), arg_val);
            cc->llvm_ir_builder->CreateStore(load, inst);
        }
    }

    llvm::Function *Function::CodeGenLLVM(CompilerContext *cc)
    {

        //////////////////////////////////////

        // step 1 - generate protorype (or get existing)
        llvm::Function *function = cc->llvm_module->getFunction(name);

        if (function == nullptr)
        {
            function = GenerateLLVMFunctionPrototype(cc);
        }

        // step 2 - set names for arguments
        LLVMAssignArgumentNames(cc, function);

        // step 2 - create basic block
        llvm::BasicBlock *bb = llvm::BasicBlock::Create(*cc->llvm_context, "entry", function);
        cc->llvm_ir_builder->SetInsertPoint(bb);

        // step 3 - create mutable representations of arguments variables and initialize them
        AllocAndInitLocalVariables(cc, function);

        // evaluate statements
        for (int i = 0; i < statement_list.size(); i++)
        {
            statement_list[i]->CodeGenLLVM(cc);
        }

        // last step - return values VAR_IN_OUT VAR_OUT and return_value
        // return VAR_IN_OUT
        const int var_in_out_offset = var_input.size();
        const int var_output_offset = var_in_out_offset + var_in_out.size();
        const int var_return_offset = var_output_offset + var_output.size();

        for (int i = 0; i < var_in_out.size(); i++)
        {
            auto local_var_copy = cc->local_variables[var_in_out[i].GetName()];
            auto load_result = cc->llvm_ir_builder->CreateLoad(DataTypeToLLVMType(cc, local_var_copy.data_type), local_var_copy.llvm_alloca_instance);
            cc->llvm_ir_builder->CreateStore(load_result, function->getArg(var_in_out_offset + i));
        }

        for (int i = 0; i < var_output.size(); i++)
        {
            auto local_var_copy = cc->local_variables[var_output[i].GetName()];
            auto load_result = cc->llvm_ir_builder->CreateLoad(DataTypeToLLVMType(cc, local_var_copy.data_type), local_var_copy.llvm_alloca_instance);
            cc->llvm_ir_builder->CreateStore(load_result, function->getArg(var_output_offset + i));
        }

        {
            auto local_var_copy = cc->local_variables[var_return.GetName()];
            auto load_result = cc->llvm_ir_builder->CreateLoad(DataTypeToLLVMType(cc, local_var_copy.data_type), local_var_copy.llvm_alloca_instance);
            cc->llvm_ir_builder->CreateStore(load_result, function->getArg(var_return_offset));
        }

        cc->llvm_ir_builder->CreateRetVoid();

        // verify function
        std::string code_err;
        llvm::raw_string_ostream ostream(code_err);
        llvm::verifyFunction(*function, &ostream);

        std::cout << "\n"
                  << code_err << "\n";

        return function;
    }

    DataType UnaryPlus::GetDataType(CompilerContext *cc)
    {
        if (expr == nullptr)
            return DataType::UNNOWN;

        return expr->GetDataType(cc);
    }

    DataType UnaryMinus::GetDataType(CompilerContext *cc)
    {
        if (expr == nullptr)
            return DataType::UNNOWN;

        return expr->GetDataType(cc);
    }

    DataType BooleanNOT::GetDataType(CompilerContext *cc)
    {
        if (expr == nullptr)
            return DataType::UNNOWN;

        return expr->GetDataType(cc);
    }

    DataType Exponentiation::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Multiply::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Divide::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Modulo::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Add::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Subtract::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType GreaterThan::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType LessThan::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType GreaterOrEqual::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType LessOrEqual::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType Equality::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType Inequality::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType BooleanAND::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType BooleanOR::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType BooleanXOR::GetDataType(CompilerContext *cc)
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType(cc);
        DataType data_r = expr_r->GetDataType(cc);

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Variable::GetDataType(CompilerContext *cc)
    {
        auto iter = cc->local_variables.find(name);
        if (iter == cc->local_variables.end())
        {
            // Error - variable not defined
            return DataType::UNNOWN;
        }
        CompilerContext::LocalVariable local_var = iter->second;
        return local_var.data_type;
    }

    llvm::Value *GetValueFromLLVMPointer(CompilerContext *cc, llvm::Value *local_var, DataType type)
    {
        auto load = cc->llvm_ir_builder->CreateLoad(DataTypeToLLVMType(cc, type), local_var);
        return load;
    }

    llvm::Value *GetValueFromLLVMPointerIfPointerType(CompilerContext *cc, llvm::Value *local_var, DataType type)
    {
        if (local_var->getType()->isPointerTy())
        {
            return GetValueFromLLVMPointer(cc, local_var, type);
        }
        else
        {
            return local_var;
        }
    }

    llvm::Value *Variable::CodeGenLLVM(CompilerContext *cc)
    {

        auto iter = cc->local_variables.find(name);
        if (iter == cc->local_variables.end())
        {
            // Error - variable not defined
            return nullptr;
        }
        CompilerContext::LocalVariable local_var = iter->second;
        // auto load = cc->llvm_ir_builder->CreateLoad(DataTypeToLLVMType(cc, local_var.data_type), local_var.llvm_alloca_instance);
        return local_var.llvm_alloca_instance;
    }

    llvm::Value *LiteralSpecific::CodeGenLLVM(CompilerContext *cc)
    {
        // llvm::ConstantFP::get(*cc->llvm_context, llvm::APInt(value_ui, 1));
        switch (type)
        {
        case DataType::BOOL:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(1, value_ui, false));
        case DataType::SINT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(8, value_i, true));
        case DataType::INT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(16, value_i, true));
        case DataType::DINT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(32, value_i, true));
        case DataType::LINT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(64, value_i, true));
        case DataType::USINT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(8, value_ui, false));
        case DataType::UINT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(16, value_ui, false));
        case DataType::UDINT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(32, value_ui, false));
        case DataType::ULINT:
            return llvm::ConstantInt::get(*cc->llvm_context, llvm::APInt(64, value_ui, false));
        case DataType::REAL:
            return llvm::ConstantFP::get(*cc->llvm_context, llvm::APFloat((float)value_d));
        case DataType::LREAL:
            return llvm::ConstantFP::get(*cc->llvm_context, llvm::APFloat((double)value_d));

        default:
            return nullptr; // this will throw error
        }
    }

    llvm::Value *UnaryPlus::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type = expr->GetDataType(cc);
        if (type == DataType::BOOL)
        {
            // ERROR unnary plus is not alowed for float data type
        }
        llvm::Value *val = expr->CodeGenLLVM(cc);
        val = GetValueFromLLVMPointerIfPointerType(cc, val, type);
        return val;
    }

    llvm::Value *UnaryMinus::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type = expr->GetDataType(cc);
        llvm::Value *val = expr->CodeGenLLVM(cc);
        val = GetValueFromLLVMPointerIfPointerType(cc, val, type);
        switch (type)
        {
        case DataType::BOOL:
            // ERROR negation of value type BOOL is illegal
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_LINT_result");
        case DataType::USINT:
            // ERROR negation of value type USINT is illegal
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_USINT_result");
        case DataType::UINT:
            // ERROR negation of value type UINT is illegal
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_UINT_result");
        case DataType::UDINT:
            // ERROR negation of value type UDINT is illegal
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_UDINT_result");
        case DataType::ULINT:
            // ERROR negation of value type ULINT is illegal
            return cc->llvm_ir_builder->CreateNeg(val, "unary_minus_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFNeg(val, "unary_minus_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFNeg(val, "unary_minus_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *BooleanNOT::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type = expr->GetDataType(cc);
        llvm::Value *val = expr->CodeGenLLVM(cc);
        val = GetValueFromLLVMPointerIfPointerType(cc, val, type);
        switch (type)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_ULINT_result");
        case DataType::REAL:
            // ERROR negation of value type REAL is illegal
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_REAL_result");
        case DataType::LREAL:
            // ERROR negation of value type LREAL is illegal
            return cc->llvm_ir_builder->CreateNot(val, "boolean_NOT_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *Exponentiation::CodeGenLLVM(CompilerContext *cc)
    {
        return nullptr; // this will throw error
    }

    llvm::Value *Multiply::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateMul(val_l, val_r, "multiply_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFMul(val_l, val_r, "multiply_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFMul(val_l, val_r, "multiply_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *Divide::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateUDiv(val_l, val_r, "divide_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateSDiv(val_l, val_r, "divide_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateSDiv(val_l, val_r, "divide_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateSDiv(val_l, val_r, "divide_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateSDiv(val_l, val_r, "divide_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateUDiv(val_l, val_r, "divide_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateUDiv(val_l, val_r, "divide_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateUDiv(val_l, val_r, "divide_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateUDiv(val_l, val_r, "divide_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFDiv(val_l, val_r, "divide_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFDiv(val_l, val_r, "divide_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *Modulo::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateURem(val_l, val_r, "modulo_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateSRem(val_l, val_r, "modulo_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateSRem(val_l, val_r, "modulo_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateSRem(val_l, val_r, "modulo_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateSRem(val_l, val_r, "modulo_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateURem(val_l, val_r, "modulo_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateURem(val_l, val_r, "modulo_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateURem(val_l, val_r, "modulo_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateURem(val_l, val_r, "modulo_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFRem(val_l, val_r, "modulo_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFRem(val_l, val_r, "modulo_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *Add::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateAdd(val_l, val_r, "add_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFAdd(val_l, val_r, "add_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFAdd(val_l, val_r, "add_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *Subtract::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateSub(val_l, val_r, "subtract_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFSub(val_l, val_r, "subtract_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFSub(val_l, val_r, "subtract_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *GreaterThan::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateICmpUGT(val_l, val_r, "GT_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateICmpSGT(val_l, val_r, "GT_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateICmpSGT(val_l, val_r, "GT_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateICmpSGT(val_l, val_r, "GT_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateICmpSGT(val_l, val_r, "GT_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateICmpUGT(val_l, val_r, "GT_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateICmpUGT(val_l, val_r, "GT_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateICmpUGT(val_l, val_r, "GT_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateICmpUGT(val_l, val_r, "GT_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFCmpUGT(val_l, val_r, "GT_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFCmpUGT(val_l, val_r, "GT_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *LessThan::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateICmpULT(val_l, val_r, "LT_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateICmpSLT(val_l, val_r, "LT_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateICmpSLT(val_l, val_r, "LT_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateICmpSLT(val_l, val_r, "LT_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateICmpSLT(val_l, val_r, "LT_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateICmpULT(val_l, val_r, "LT_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateICmpULT(val_l, val_r, "LT_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateICmpULT(val_l, val_r, "LT_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateICmpULT(val_l, val_r, "LT_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFCmpULT(val_l, val_r, "LT_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFCmpULT(val_l, val_r, "LT_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *GreaterOrEqual::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateICmpUGE(val_l, val_r, "GE_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateICmpSGE(val_l, val_r, "GE_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateICmpSGE(val_l, val_r, "GE_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateICmpSGE(val_l, val_r, "GE_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateICmpSGE(val_l, val_r, "GE_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateICmpUGE(val_l, val_r, "GE_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateICmpUGE(val_l, val_r, "GE_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateICmpUGE(val_l, val_r, "GE_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateICmpUGE(val_l, val_r, "GE_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFCmpUGE(val_l, val_r, "GE_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFCmpUGE(val_l, val_r, "GE_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *LessOrEqual::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateICmpULE(val_l, val_r, "LE_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateICmpSLE(val_l, val_r, "LE_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateICmpSLE(val_l, val_r, "LE_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateICmpSLE(val_l, val_r, "LE_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateICmpSLE(val_l, val_r, "LE_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateICmpULE(val_l, val_r, "LE_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateICmpULE(val_l, val_r, "LE_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateICmpULE(val_l, val_r, "LE_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateICmpULE(val_l, val_r, "LE_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFCmpULE(val_l, val_r, "LE_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFCmpULE(val_l, val_r, "LE_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *Equality::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateICmpEQ(val_l, val_r, "EQ_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFCmpUEQ(val_l, val_r, "EQ_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFCmpUEQ(val_l, val_r, "EQ_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *Inequality::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateICmpNE(val_l, val_r, "NE_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateFCmpUNE(val_l, val_r, "NE_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateFCmpUNE(val_l, val_r, "NE_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *BooleanAND::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateAnd(val_l, val_r, "AND_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *BooleanOR::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateOr(val_l, val_r, "OR_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    llvm::Value *BooleanXOR::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);
        llvm::Value *val_l = expr_l->CodeGenLLVM(cc);
        llvm::Value *val_r = expr_r->CodeGenLLVM(cc);
        val_l = GetValueFromLLVMPointerIfPointerType(cc, val_l, type_l);
        val_r = GetValueFromLLVMPointerIfPointerType(cc, val_r, type_r);
        if (type_l != type_r)
        {
            return nullptr;
        }

        switch (type_l)
        {
        case DataType::BOOL:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_BOOL_result");
        case DataType::SINT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_SINT_result");
        case DataType::INT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_INT_result");
        case DataType::DINT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_DINT_result");
        case DataType::LINT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_LINT_result");
        case DataType::USINT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_USINT_result");
        case DataType::UINT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_UINT_result");
        case DataType::UDINT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_UDINT_result");
        case DataType::ULINT:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_ULINT_result");
        case DataType::REAL:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_REAL_result");
        case DataType::LREAL:
            return cc->llvm_ir_builder->CreateXor(val_l, val_r, "XOR_LREAL_result");

        default:
            return nullptr; // this will throw error
        }

        return nullptr; // this will throw error
    }

    void AssignmentStatement::CodeGenLLVM(CompilerContext *cc)
    {
        DataType type_l = expr_l->GetDataType(cc);
        DataType type_r = expr_r->GetDataType(cc);

        llvm::Value *l_value = expr_l->CodeGenLLVM(cc);
        llvm::Value *r_value = expr_r->CodeGenLLVM(cc);

        if (type_l != type_r)
        {
            // Error case - incorrect data type
        }

        cc->llvm_ir_builder->CreateStore(r_value, l_value);
    };
    void ExprStatement::CodeGenLLVM(CompilerContext *cc)
    {
        // expression statement
        // result not assigned to anything
        expr->CodeGenLLVM(cc);
    };
    void EmptyStatement::CodeGenLLVM(CompilerContext *cc) {
        // empty statement:
        // do nothing
    };

}
