#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/TypedPointerType.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Intrinsics.h>
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

#include "type.hpp"
#include "ast1_makros.hpp"
#include "error/error_manager.hpp"
#include "position.hpp"
#include "exception.hpp"

typedef boost::multiprecision::cpp_int big_int;
typedef boost::multiprecision::cpp_bin_float_oct big_float;

namespace AST
{

    struct LLVMCompilerContext;
    struct LocalScope;

    //******************************************************************************************
    // interface
    struct Expression
    {
        Position position;
        Expression(Position _position) : position(_position) {}

        virtual Type GetType(LocalScope *ls) = 0;
        virtual std::string ToString() = 0;
    };

    struct Rvalue : public Expression
    {
        Rvalue(Position _position) : Expression(_position) {}
        virtual llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) = 0;
    };

    struct Lvalue : public Rvalue
    {
        Lvalue(Position _position) : Rvalue(_position) {}
        virtual void LLVMSetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc, llvm::Value *) = 0;
    };

    typedef std::shared_ptr<Rvalue> ExprPtr;

    class BinaryExpression : public Rvalue
    {
    protected:
        ExprPtr left;
        ExprPtr right;
        BinaryExpression(Position _position, ExprPtr l, ExprPtr r) : Rvalue(_position), left(l), right(r) {}
    };

    class BinaryArithmeticExpression : public BinaryExpression
    {
    protected:
        BinaryArithmeticExpression(Position pos, ExprPtr l, ExprPtr r) : BinaryExpression(pos, l, r) {}
        Type GetType(LocalScope *ls) override
        {
            if (!left || !right)
            {
                return Type::UNNOWN;
            }

            Type type_left = left->GetType(ls);
            Type type_right = right->GetType(ls);

            if (type_left != type_right)
            {
                ErrorManager::Create(Error::InvalidBinaryOperation(position, "", type_left, type_right));
                throw Exception{};
            }

            return type_left;
        }
    };

    class BinaryComparisonExpression : public BinaryExpression
    {
    protected:
        BinaryComparisonExpression(Position pos, ExprPtr l, ExprPtr r) : BinaryExpression(pos, l, r) {}
        Type GetType(LocalScope *ls) override
        {
            if (!left || !right)
            {
                return Type::UNNOWN;
            }

            Type type_left = left->GetType(ls);
            Type type_right = right->GetType(ls);

            if (type_left != type_right)
            {
                ErrorManager::Create(Error::InvalidBinaryOperation(position, "", type_left, type_right));
                throw Exception{};
            }

            return Type::BOOL;
        }
    };

    class UnaryExpression : public Rvalue
    {
    protected:
        ExprPtr expr;
        UnaryExpression(Position pos, ExprPtr e) : Rvalue(pos), expr(e) {}

    public:
        Type GetType(LocalScope *ls)
        {
            if (!expr)
                return Type::UNNOWN;

            return expr->GetType(ls);
        }
    };

    //********************************************************************************************

    struct Statement
    {
        Position position;
        Statement(Position _position) : position(_position) {}

        virtual std::string ToString() = 0;
        virtual void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) = 0;
    };

    typedef std::shared_ptr<Statement> StmtPtr;
    typedef std::vector<StmtPtr> StmtList;

    //********************************************************************************************

    struct Pou;

    struct Pou
    {
        typedef std::shared_ptr<Pou> PouPtr;
        typedef std::vector<PouPtr> PouList;

        std::string name;
        virtual std::string ToString() = 0;
        virtual void LLVMGenerateDeclaration(PouList *gs, LLVMCompilerContext *llvm_cc) = 0;
        virtual void LLVMGenerateDefinition(PouList *gs, LLVMCompilerContext *llvm_cc) = 0;
    };

    typedef Pou::PouPtr PouPtr;
    typedef Pou::PouList PouList;

    //********************************************************************************************

    template <class E>
    StmtPtr MakeStmt(E expr)
    {
        return std::make_shared<E>(expr);
    }

    template <class E>
    ExprPtr MakeExpr(E expr)
    {
        return std::make_shared<E>(expr);
    }

    template <class E>
    PouPtr MakePou(E expr)
    {
        return std::make_shared<E>(expr);
    }

    //*******************************************************************************************

    std::string Indent(std::string str);
    std::string StatementListToString(StmtList list);

    //********************************************************************************************

    struct Variable
    {
        std::string name;
        std::string type;
        ExprPtr initial_value;
        // TODO: type;
        Variable() : name(""), type(""), initial_value(nullptr) {} // constructor for invalid variable
        Variable(std::string _name, std::string _type) : name(_name), type(_type), initial_value(nullptr) {}
        Variable(std::string _name, std::string _type, ExprPtr init_val) : name(_name), type(_type), initial_value(init_val) {}

        bool IsValid()
        {
            return name.size() != 0 && type.size() != 0;
        }

        std::string ToString()
        {
            if (initial_value)
            {
                return name + " : " + type + " := " + initial_value->ToString();
            }
            else
            {
                return name + " : " + type;
            }
        }

        Type GetType()
        {
            return Type::FromString(type);
        }
    };

    typedef std::vector<Variable> VarList;

    struct Function : public Pou
    {
        bool is_extern;
        Function(bool _is_extern) : is_extern(_is_extern) {}

        StmtList statement_list;
        std::shared_ptr<Variable> result;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString() override;

        void LLVMGenerateDeclaration(AST::PouList *gs, LLVMCompilerContext *llvm_cc) override;
        void LLVMGenerateDefinition(AST::PouList *gs, LLVMCompilerContext *llvm_cc) override;

    private:
        llvm::Function *LLVMBuildDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMBuildBody(AST::PouList *gs, LLVMCompilerContext *llvm_cc);

    public:
        llvm::Function *LLVMGetDeclaration(LLVMCompilerContext *llvm_cc);
    };

    struct FunctionBlock : public Pou
    {
        bool is_extern;
        FunctionBlock(bool _is_extern) : is_extern(_is_extern) {}

        StmtList statement_list;
        std::shared_ptr<Variable> result;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString() override;

        void LLVMGenerateDeclaration(AST::PouList *gs, LLVMCompilerContext *llvm_cc) override;
        void LLVMGenerateDefinition(AST::PouList *gs, LLVMCompilerContext *llvm_cc) override;
    };

    struct Program : public Pou
    {
        bool is_extern;
        Program(bool _is_extern) : is_extern(_is_extern) {}

        StmtList statement_list;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString() override;

        void LLVMGenerateDeclaration(AST::PouList *gs, LLVMCompilerContext *llvm_cc) override;
        void LLVMGenerateDefinition(AST::PouList *gs, LLVMCompilerContext *llvm_cc) override;

        llvm::Function *LLVMGetInitDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMGetBodyDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::StructType *LLVMGetStructType(LLVMCompilerContext *llvm_cc);
    private:
        llvm::FunctionType *GetFunctionType(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMCreateInitDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMCreateBodyDeclaration(LLVMCompilerContext *llvm_cc);
        void LLVMCreateInit(AST::PouList *gs, LLVMCompilerContext *llvm_cc);
        void LLVMCreateBody(AST::PouList *gs, LLVMCompilerContext *llvm_cc);
    };

    //********************************************************************************************

    struct EmptyStatement : public Statement
    {
        EmptyStatement(Position pos) : Statement(pos) {}

        std::string ToString() override
        {
            return "{}";
        }

        void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) override
        {
            // DO NOTHING
            // NO NOT EMIT CODE FROM THIS CLASS
        }
    };

    struct AssignmentStatement : public Statement
    {
        ExprPtr var;
        ExprPtr expr;

        AssignmentStatement(Position pos, ExprPtr _var, ExprPtr _expr) : Statement(pos), var(_var), expr(_expr) {}

        std::string ToString() override
        {
            std::string expr_str = expr ? expr->ToString() : "____";
            std::string var_str = var ? var->ToString() : "____";
            return "{" + var_str + " := " + expr_str + "}";
        }

        void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct NonAsssingingStatement : public Statement
    {
        ExprPtr expr;
        NonAsssingingStatement(Position pos, ExprPtr _expr) : Statement(pos), expr(_expr) {}

        std::string ToString() override
        {
            std::string expr_str = expr ? expr->ToString() : "____";
            return "{" + expr_str + "}";
        }

        void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct IfStatement : public Statement
    {
        ExprPtr condition;
        StmtList statement_list;

        IfStatement(Position pos, ExprPtr cond, StmtList stmt_list) : Statement(pos), condition(cond), statement_list(stmt_list) {}

        std::string ToString() override
        {
            std::string expr_str = condition ? condition->ToString() : "____";
            return "{IF " + expr_str + " THEN\n" + StatementListToString(statement_list) + "\n}";
        }

        void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct WhileStatement : public Statement
    {
        ExprPtr condition;
        StmtList statement_list;

        WhileStatement(Position pos, ExprPtr cond, StmtList stmt_list) : Statement(pos), condition(cond), statement_list(stmt_list) {}

        std::string ToString() override
        {
            std::string expr_str = condition ? condition->ToString() : "____";
            std::string str = "{\nt\tWHILE " + expr_str + " THEN\n";
            for (StmtPtr stmt : statement_list)
            {
                std::string stmt_str = stmt ? stmt->ToString() : "____";
                str += "\t" + stmt_str + "\n";
            }
            str += "\n}";
            return str;
        }

        void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    //********************************************************************************************

    struct NonformalCall : public Rvalue
    {
        std::vector<ExprPtr> input_arguments;
        std::string callee_name;

        NonformalCall(Position pos, std::string callee, std::vector<ExprPtr> args) : Rvalue(pos), callee_name(callee), input_arguments(args) {};

        Type GetType(LocalScope *ls) override;
        std::string ToString() override;
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct FormalCall : public Rvalue
    {
        // first := second
        std::vector<std::pair<ExprPtr, ExprPtr>> input_arguments;

        // first => second
        std::vector<std::pair<ExprPtr, ExprPtr>> output_arguments;

        std::string callee_name;

        FormalCall(Position pos,
                   std::string callee) : Rvalue(pos), callee_name(callee), input_arguments(), output_arguments() {};

        FormalCall(Position pos,
                   std::string callee,
                   std::vector<std::pair<ExprPtr, ExprPtr>> input_args,
                   std::vector<std::pair<ExprPtr, ExprPtr>> output_args) : Rvalue(pos), callee_name(callee), input_arguments(input_args), output_arguments(output_args) {};

        Type GetType(LocalScope *ls) override;
        std::string ToString() override;
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct Literal : public Rvalue
    {
        Type type;

        big_int i_value; // holds integer-like values
        double f_value;  // holds float-like values

        Literal(Position pos, bool v) : Rvalue(pos), i_value((int)v), f_value((int)v), type(Type::BOOL) {};
        Literal(Position pos, big_int v, Type t) : Rvalue(pos), i_value(v), f_value(v), type(t) {};
        Literal(Position pos, double v, Type t) : Rvalue(pos), i_value(v), f_value(v), type(t) {};

        Type GetType(LocalScope *ls) override
        {
            return type;
        }

        std::string ToString() override
        {
            if (type.IsFloatingPoint())
            {
                return type.ToString() + "#" + std::to_string(f_value);
            }
            if (type.IsInteger() || type.IsBit())
            {
                return type.ToString() + "#" + i_value.str();
            }
            return "_INVALID_";
        }

        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct VariableAccess : public Lvalue
    {
        std::string variable_name;
        VariableAccess(Position pos, std::string l) : Lvalue(pos), variable_name(l) {};
        std::string ToString() override
        {
            return variable_name;
        }
        Type GetType(LocalScope *ls) override;
        void LLVMSetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc, llvm::Value *) override;
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct GlobalMemoryAccess : public Lvalue
    {
    public:
        // I Q M
        enum class Location
        {
            Input = 0,
            Output = 1,
            Memory = 2,
        };

    private:
        Location location;

        // enum class Size
        // {
        //     BIT,     // X - 1 bit
        //     BYTE,    // B - 8 bit
        //     WORD,    // W - 16 bit
        //     DWORD,   // D - 32 bit
        //     LWORD,   // L - 64 bit
        // };
        uint64_t size;

        // %IX2.0.1
        // [2] - module nr 2
        // [0] - byte 0
        // [1] - bit 1
        std::vector<uint64_t> address;

    public:
        GlobalMemoryAccess(Position pos, Location loc, uint64_t _size, std::vector<uint64_t> _address)
            : Lvalue(pos),
              location(loc),
              size(_size),
              address(_address) {}

        std::string ToString() override
        {
            std::string loc;
            std::string s;
            switch (location)
            {
            case Location::Input:
                loc = "I";
                break;
            case Location::Output:
                loc = "Q";
                break;
            case Location::Memory:
                loc = "M";
                break;
            }

            switch (size)
            {
            case 1:
                s = "X";
                break;
            case 8:
                s = "B";
                break;
            case 16:
                s = "W";
                break;
            case 32:
                s = "D";
                break;
            case 64:
                s = "L";
                break;

            default:
                s = "(" + std::to_string(size) + ")";
                break;
            }

            std::string all = "%" + loc + s;
            for (int i = 0; i < address.size(); i++)
            {
                all += (i == 0) ? "" : ".";
                all += std::to_string(address[i]);
            }

            return all;
        }

        Type GetType(LocalScope *ls) override;
        void LLVMSetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc, llvm::Value *) override;
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    //********************************************************************************************

    struct Exponentiation : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Exponentiation, "**", BinaryArithmeticExpression);
    };

    struct Add : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Add, "+", BinaryArithmeticExpression);
    };

    struct Subtract : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Subtract, "-", BinaryArithmeticExpression);
    };

    struct Multiply : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Multiply, "*", BinaryArithmeticExpression);
    };

    struct Divide : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Divide, "/", BinaryArithmeticExpression);
    };

    struct Modulo : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Modulo, "MOD", BinaryArithmeticExpression);
    };

    struct Or : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Or, "OR", BinaryArithmeticExpression);
    };

    struct Xor : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(Xor, "XOR", BinaryArithmeticExpression);
    };

    struct And : public BinaryArithmeticExpression
    {
        BINARY_OPERATOR_METHODS(And, "AND", BinaryArithmeticExpression);
    };

    struct Gt : public BinaryComparisonExpression
    {
        BINARY_OPERATOR_METHODS(Gt, ">", BinaryComparisonExpression);
    };

    struct Lt : public BinaryComparisonExpression
    {
        BINARY_OPERATOR_METHODS(Lt, "<", BinaryComparisonExpression);
    };

    struct Geq : public BinaryComparisonExpression
    {
        BINARY_OPERATOR_METHODS(Geq, ">=", BinaryComparisonExpression);
    };

    struct Leq : public BinaryComparisonExpression
    {
        BINARY_OPERATOR_METHODS(Leq, "<=", BinaryComparisonExpression);
    };

    struct Eq : public BinaryComparisonExpression
    {
        BINARY_OPERATOR_METHODS(Eq, "=", BinaryComparisonExpression);
    };

    struct Neq : public BinaryComparisonExpression
    {
        BINARY_OPERATOR_METHODS(Neq, "<>", BinaryComparisonExpression);
    };

    /////

    struct UnaryPlus : public UnaryExpression
    {
        UNARY_CONSTRUCTOR(UnaryPlus);
        UNARY_TOSTRING("+");
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct UnaryMinus : public UnaryExpression
    {
        UNARY_CONSTRUCTOR(UnaryMinus);
        UNARY_TOSTRING("-");
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct Negation : public UnaryExpression
    {
        UNARY_CONSTRUCTOR(Negation);
        UNARY_TOSTRING("NOT");
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    //********************************************************************************************
    // CONTEXT CLASSES

    struct LLVMCompilerContext
    {
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::IRBuilder<>> ir_builder;
        std::unique_ptr<llvm::Module> module;

        llvm::Type *global_mem_type;

        llvm::Value *global_mem_ptr;
        std::map<std::string, llvm::Value *> local_variables;

        void CreateGlobalMemoryType()
        {
            // create global memory structure type
            constexpr int number_of_modules = 5;
            constexpr int bytes_per_module = 64;
            constexpr int memory_size = 1024;

            llvm::IntegerType *u8_type = llvm::IntegerType::getInt8Ty(*context);
            llvm::IntegerType *u16_type = llvm::IntegerType::getInt16Ty(*context);
            llvm::IntegerType *u32_type = llvm::IntegerType::getInt32Ty(*context);
            llvm::IntegerType *u64_type = llvm::IntegerType::getInt64Ty(*context);

            llvm::Type *input_mem_type = llvm::ArrayType::get(llvm::ArrayType::get(u8_type, bytes_per_module), number_of_modules);
            llvm::Type *output_mem_type = llvm::ArrayType::get(llvm::ArrayType::get(u8_type, bytes_per_module), number_of_modules);
            llvm::Type *memory_mem_type = llvm::ArrayType::get(u8_type, memory_size);

            std::initializer_list<llvm::Type *> mems = {input_mem_type, output_mem_type, memory_mem_type};
            global_mem_type = llvm::StructType::get(*context, mems, true);
        }

        LLVMCompilerContext()
        {
            context = std::make_unique<llvm::LLVMContext>();
            module = std::make_unique<llvm::Module>("my ST compiler", *context);
            ir_builder = std::make_unique<llvm::IRBuilder<>>(*context);
            CreateGlobalMemoryType();
        }

        std::string IR_ToString()
        {
            std::string ir_code;
            llvm::raw_string_ostream ostream(ir_code);
            ostream << *module;
            return ir_code;
        }
    };

    struct LocalScope
    {
        std::map<std::string, Variable *> local_variables;
        AST::PouList *global_scope;
    };

    //******************************************************************************************
    // llvm helper functions

    llvm::Type *TypeToLLVMType(Type t, LLVMCompilerContext *llvm_cc);
    llvm::AllocaInst *CreateEntryBlockAlloca(LLVMCompilerContext *llvm_cc, llvm::Function *function, Variable &var);

};
