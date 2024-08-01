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
        virtual Type GetType(LocalScope *ls) = 0;
        virtual std::string ToString() = 0;

        virtual llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) { return nullptr; };
        virtual llvm::Value *LLVMGetReference(LocalScope *ls, LLVMCompilerContext *llvm_cc) { return nullptr; };
    };

    typedef std::shared_ptr<Expression> ExprPtr;

    //********************************************************************************************

    struct Statement
    {
        virtual std::string ToString() = 0;
        virtual void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) = 0;
    };

    typedef std::shared_ptr<Statement> StmtPtr;
    typedef std::vector<StmtPtr> StmtList;

    //********************************************************************************************

    struct Pou
    {
        std::string name;
        virtual std::string ToString() = 0;
        virtual void LLVMGenerateDeclaration(LLVMCompilerContext *llvm_cc) = 0;
        virtual void LLVMGenerateDefinition(LLVMCompilerContext *llvm_cc) = 0;
    };

    typedef std::shared_ptr<Pou> PouPtr;
    typedef std::vector<PouPtr> PouList;

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

    //********************************************************************************************

    class BinaryExpression : public Expression
    {
    protected:
        ExprPtr left;
        ExprPtr right;
        BinaryExpression(ExprPtr l, ExprPtr r) : left(l), right(r) {}
    };

    class BinaryArithmeticExpression : public BinaryExpression
    {
    protected:
        BinaryArithmeticExpression(ExprPtr l, ExprPtr r) : BinaryExpression(l,r) {}
        Type GetType(LocalScope *ls) override
        {
            if (!left || !right)
                return Type::UNNOWN;

            Type type_left = left->GetType(ls);
            Type type_right = right->GetType(ls);

            if (type_left != type_right)
                return Type::UNNOWN;

            return type_left;
        }
    };

    class BinaryComparisonExpression : public BinaryExpression
    {
    protected:
        BinaryComparisonExpression(ExprPtr l, ExprPtr r) : BinaryExpression(l,r) {}
        Type GetType(LocalScope *ls) override
        {
            if (!left || !right)
                return Type::UNNOWN;

            Type type_left = left->GetType(ls);
            Type type_right = right->GetType(ls);

            if (type_left != type_right)
                return Type::UNNOWN;

            return Type::BOOL;
        }
    };

    //********************************************************************************************

    class UnaryExpression : public Expression
    {
    protected:
        ExprPtr expr;
        UnaryExpression(ExprPtr e) : expr(e) {}

    public:
        Type GetType(LocalScope *ls)
        {
            if (!expr)
                return Type::UNNOWN;

            return expr->GetType(ls);
        }
    };

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
        StmtList statement_list;
        std::shared_ptr<Variable> result;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString();

        void LLVMGenerateDeclaration(LLVMCompilerContext *llvm_cc) override;
        void LLVMGenerateDefinition(LLVMCompilerContext *llvm_cc) override;

    private:
        llvm::Function *LLVMBuildDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMGetDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMBuildBody(LLVMCompilerContext *llvm_cc);
    };

    struct FunctionBlock : public Pou
    {
        StmtList statement_list;
        std::shared_ptr<Variable> result;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString();

        void LLVMGenerateDeclaration(LLVMCompilerContext *llvm_cc) override;
        void LLVMGenerateDefinition(LLVMCompilerContext *llvm_cc) override;
    };

    struct Program : public Pou
    {
        StmtList statement_list;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString();

        void LLVMGenerateDeclaration(LLVMCompilerContext *llvm_cc) override;
        void LLVMGenerateDefinition(LLVMCompilerContext *llvm_cc) override;

    private:
        llvm::FunctionType *GetFunctionType(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMCreateInitDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMCreateBodyDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMGetInitDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::Function *LLVMGetBodyDeclaration(LLVMCompilerContext *llvm_cc);
        llvm::StructType *LLVMGetStructType(LLVMCompilerContext *llvm_cc);
        void LLVMCreateInit(LLVMCompilerContext *llvm_cc);
        void LLVMCreateBody(LLVMCompilerContext *llvm_cc);
    };

    //********************************************************************************************

    struct EmptyStatement : public Statement
    {
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

        AssignmentStatement(ExprPtr _var, ExprPtr _expr) : var(_var), expr(_expr) {}

        std::string ToString() override
        {
            std::string expr_str = expr ? expr->ToString() : "____";
            std::string var_str = var ? var->ToString() : "____";
            return "{" + var_str + " := " + expr_str + "}";
        }

        void CodeGenLLVM(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
    };

    struct IfStatement : public Statement
    {
        ExprPtr condition;
        StmtList statement_list;

        IfStatement(ExprPtr cond, StmtList stmt_list) : condition(cond), statement_list(stmt_list) {}

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

        WhileStatement(ExprPtr cond, StmtList stmt_list) : condition(cond), statement_list(stmt_list) {}

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

    struct Literal : public Expression
    {
        Type type;

        big_int i_value; // holds integer-like values
        double f_value;  // holds float-like values

        Literal(bool v) : i_value((int)v), f_value((int)v), type(Type::BOOL) {};
        Literal(big_int v, Type t) : i_value(v), f_value(v), type(t) {};
        Literal(double v, Type t) : i_value(v), f_value(v), type(t) {};

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

    struct VariableAccess : public Expression
    {
        std::string variable_name;
        VariableAccess(std::string l) : variable_name(l) {};
        std::string ToString() override
        {
            return variable_name;
        }
        Type GetType(LocalScope *ls) override;
        llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
        llvm::Value *LLVMGetReference(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;
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

        std::map<std::string, llvm::Value *> local_variables;

        LLVMCompilerContext()
        {
            context = std::make_unique<llvm::LLVMContext>();
            module = std::make_unique<llvm::Module>("my ST compiler", *context);
            ir_builder = std::make_unique<llvm::IRBuilder<>>(*context);
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
    };

    //******************************************************************************************
    // llvm helper functions

    llvm::Type *TypeToLLVMType(Type t, LLVMCompilerContext *llvm_cc);
    llvm::AllocaInst *CreateEntryBlockAlloca(LLVMCompilerContext *llvm_cc, llvm::Function *function, Variable &var);

};
