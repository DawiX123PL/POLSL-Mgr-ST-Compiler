#pragma once

#include <memory>
#include <inttypes.h>
#include <string>
#include <vector>
#include <tuple>
#include <map>

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APInt.h>

#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/TypedPointerType.h>
#include <llvm/IR/Verifier.h>

namespace AST
{

    enum class DataType
    {
        UNNOWN, // Error case

        BOOL,
        SINT,
        INT,
        DINT,
        LINT,
        USINT,
        UINT,
        UDINT,
        ULINT,
        REAL,
        LREAL,
    };

    DataType StringToDataType(std::string str);

    struct CompilerContext
    {
        std::unique_ptr<llvm::LLVMContext> llvm_context;
        std::unique_ptr<llvm::IRBuilder<>> llvm_ir_builder;
        std::unique_ptr<llvm::Module> llvm_module;

        struct LocalVariable
        {
            DataType data_type;
            llvm::AllocaInst *llvm_alloca_instance;

            LocalVariable(): data_type(DataType::UNNOWN), llvm_alloca_instance(nullptr) {}
            LocalVariable(DataType dt, llvm::AllocaInst *inst): data_type(dt), llvm_alloca_instance(inst) {}
        };

        std::map<std::string, LocalVariable> local_variables;

        CompilerContext()
        {
            llvm_context = std::make_unique<llvm::LLVMContext>();
            llvm_module = std::make_unique<llvm::Module>("my ST compiler", *llvm_context);
            llvm_ir_builder = std::make_unique<llvm::IRBuilder<>>(*llvm_context);
        }

        std::string IR_ToString()
        {
            std::string ir_code;
            llvm::raw_string_ostream ostream(ir_code);
            ostream << *llvm_module;
            return ir_code;
        }
    };

    // abstract classes
    class Expr
    {
    public:
        //
        virtual void Evaluate() = 0;
        virtual DataType GetDataType() = 0;
        virtual llvm::Value *CodeGenLLVM(CompilerContext *cc) = 0;
    };

    typedef std::shared_ptr<AST::Expr> ExprPtr;

    class Unary : public Expr
    {
    protected:
        ExprPtr expr;

    public:
        Unary(ExprPtr ex) : expr(ex) {}
    };

    class Binary : public Expr
    {
    protected:
        ExprPtr expr_l;
        ExprPtr expr_r;

    public:
        Binary(ExprPtr ex_l, ExprPtr ex_r) : expr_l(ex_l), expr_r(ex_r) {}
    };

    class FunctionCall : public Expr
    {
    };

    class LiteralAmbiguous : public Expr
    {
    };

    class LiteralSpecific : public Expr
    {
        DataType type;

        int64_t value_i;
        uint64_t value_ui;
        double value_d;

    public:
        LiteralSpecific(DataType _type, int64_t val) : type(_type), value_i(val), value_ui(val), value_d(val) {}
        LiteralSpecific(DataType _type, uint64_t val) : type(_type), value_i(val), value_ui(val), value_d(val) {}
        LiteralSpecific(DataType _type, double val) : type(_type), value_i(val), value_ui(val), value_d(val) {}

        static ExprPtr Create_BOOL(bool val) { return std::make_shared<LiteralSpecific>(DataType::BOOL, (uint64_t)val); }
        static ExprPtr Create_SINT(int8_t val) { return std::make_shared<LiteralSpecific>(DataType::SINT, (int64_t)val); }
        static ExprPtr Create_INT(int16_t val) { return std::make_shared<LiteralSpecific>(DataType::INT, (int64_t)val); }
        static ExprPtr Create_DINT(int32_t val) { return std::make_shared<LiteralSpecific>(DataType::DINT, (int64_t)val); }
        static ExprPtr Create_LINT(int64_t val) { return std::make_shared<LiteralSpecific>(DataType::LINT, (int64_t)val); }
        static ExprPtr Create_USINT(uint8_t val) { return std::make_shared<LiteralSpecific>(DataType::USINT, (uint64_t)val); }
        static ExprPtr Create_UINT(uint16_t val) { return std::make_shared<LiteralSpecific>(DataType::UINT, (uint64_t)val); }
        static ExprPtr Create_UDINT(uint32_t val) { return std::make_shared<LiteralSpecific>(DataType::UDINT, (uint64_t)val); }
        static ExprPtr Create_ULINT(uint64_t val) { return std::make_shared<LiteralSpecific>(DataType::ULINT, (uint64_t)val); }
        static ExprPtr Create_REAL(float val) { return std::make_shared<LiteralSpecific>(DataType::REAL, (double)val); }
        static ExprPtr Create_LREAL(double val) { return std::make_shared<LiteralSpecific>(DataType::LREAL, (double)val); }

        void Evaluate() override {};
        DataType GetDataType() override { return type; }
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class VariableDeclaration
    {
        std::string name;
        DataType type;
        ExprPtr initial_value;

    public:
        VariableDeclaration() : name(), type(), initial_value(nullptr) {}
        VariableDeclaration(std::string _name, DataType _type) : name(_name), type(_type), initial_value(nullptr) {}
        VariableDeclaration(std::string _name, DataType _type, ExprPtr _initial_value) : name(_name), type(_type), initial_value(_initial_value) {}

        std::string GetName()
        {
            return name;
        }

        DataType GetType()
        {
            return type;
        }
    };

    class Variable : public Expr
    {
        std::string name;

    public:
        Variable(std::string _name) : name(_name) {}
        static ExprPtr CreateVariable(std::string _name) { return std::make_shared<Variable>(_name); }

        void Evaluate() override {}
        DataType GetDataType() override { return DataType::UNNOWN; } // TODO: get variable data type
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Statement
    {
    public:
        virtual void Evaluate() = 0;
    };

    typedef std::shared_ptr<AST::Statement> StatementPtr;
    typedef std::vector<AST::StatementPtr> StatementList;

    class AssignmentStatement : public Statement
    {
        // expr_l := expr_r;
        ExprPtr expr_l;
        ExprPtr expr_r;

    public:
        AssignmentStatement(ExprPtr expr_l, ExprPtr expr_r){};
        static StatementPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<AssignmentStatement>(expr_l, expr_r); }
        void Evaluate() override {}
    };

    class ExprStatement : public Statement
    {
        // expr;
        ExprPtr expr;

    public:
        ExprStatement(ExprPtr _expr){};
        static StatementPtr Make(ExprPtr _expr) { return std::make_shared<ExprStatement>(_expr); }
        void Evaluate() override {}
    };

    class EmptyStatement : public Statement
    {
        // ;
    public:
        EmptyStatement(){};
        static StatementPtr Make() { return std::make_shared<EmptyStatement>(); }
        void Evaluate() override {}
    };

    class POU
    {
    public:
        virtual void Evaluate() = 0;
        virtual std::string CodeGenCHeader() = 0;
        virtual llvm::Function *CodeGenLLVM(CompilerContext *cc) = 0;
    };

    typedef std::shared_ptr<POU> POUPtr;
    typedef std::vector<POUPtr> POUlist;

    class Function : public POU
    {
    public:
        std::string name;
        VariableDeclaration var_return;
        std::vector<VariableDeclaration> var_input;
        std::vector<VariableDeclaration> var_output;
        std::vector<VariableDeclaration> var_in_out;
        std::vector<VariableDeclaration> var_temp;
        StatementList statement_list;

        Function(){};
        static POUPtr Make(Function fn) { return std::make_shared<Function>(fn); }
        void Evaluate() override {}
        std::string CodeGenCHeader() override;
        llvm::Function *GenerateLLVMFunctionPrototype(CompilerContext *cc);
        void LLVMAssignArgumentNames(CompilerContext *cc, llvm::Function *function);
        llvm::Function *CodeGenLLVM(CompilerContext *cc) override;
    };

    class UnaryPlus : public Unary
    {
    public:
        UnaryPlus(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<UnaryPlus>(expr); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class UnaryMinus : public Unary
    {
    public:
        UnaryMinus(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<UnaryMinus>(expr); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class BooleanNOT : public Unary
    {
    public:
        BooleanNOT(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<BooleanNOT>(expr); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Exponentiation : public Binary
    {
    public:
        Exponentiation(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Exponentiation>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Multiply : public Binary
    {
    public:
        Multiply(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Multiply>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Divide : public Binary
    {
    public:
        Divide(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Divide>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Modulo : public Binary
    {
    public:
        Modulo(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Modulo>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Add : public Binary
    {
    public:
        Add(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Add>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Subtract : public Binary
    {
    public:
        Subtract(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Subtract>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class GreaterThan : public Binary
    {
    public:
        GreaterThan(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<GreaterThan>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class LessThan : public Binary
    {
    public:
        LessThan(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<LessThan>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class GreaterOrEqual : public Binary
    {
    public:
        GreaterOrEqual(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<GreaterOrEqual>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class LessOrEqual : public Binary
    {
    public:
        LessOrEqual(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<LessOrEqual>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Equality : public Binary
    {
    public:
        Equality(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Equality>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class Inequality : public Binary
    {
    public:
        Inequality(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Inequality>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class BooleanAND : public Binary
    {
    public:
        BooleanAND(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanAND>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class BooleanOR : public Binary
    {
    public:
        BooleanOR(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanOR>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

    class BooleanXOR : public Binary
    {
    public:
        BooleanXOR(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanXOR>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
        llvm::Value *CodeGenLLVM(CompilerContext *cc) override;
    };

};