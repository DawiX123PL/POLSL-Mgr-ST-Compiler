#pragma once

#include <memory>
#include <inttypes.h>
#include <string>
#include <vector>
#include <tuple>

namespace AST
{

    enum class NumberSignes
    {
        SIGNED,
        UNSIGNED,
    };

    enum class NumberType
    {
        SPECIFIC,
        INTEGER_LIKE,
        FLOATING_LIKE,
    };

    // std::string build_in_types[] = {
    //     {"BOOL"},
    //     {"SINT"},
    //     {"INT"},
    //     {"DINT"},
    //     {"LINT"},
    //     {"USINT"},
    //     {"UINT"},
    //     {"UDINT"},
    //     {"ULINT"},
    //     {"REAL"},
    //     {"LREAL"},
    // };

    // abstract classes
    class Expr
    {
    public:
        virtual void Evaluate() = 0;
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
        ExprPtr l_expr;
        ExprPtr r_expr;

    public:
        Binary(ExprPtr l_ex, ExprPtr r_ex) : l_expr(l_ex), r_expr(r_ex) {}
    };

    class FunctionCall : public Expr
    {
    };

    class LiteralAmbiguous : public Expr
    {
    };

    class LiteralSpecific : public Expr
    {
        std::string type;

        int64_t value_i;
        uint64_t value_ui;
        double value_d;

    public:
        LiteralSpecific(std::string _type, int64_t val) : type(_type), value_i(val), value_ui(val), value_d(val) {}
        LiteralSpecific(std::string _type, uint64_t val) : type(_type), value_i(val), value_ui(val), value_d(val) {}
        LiteralSpecific(std::string _type, double val) : type(_type), value_i(val), value_ui(val), value_d(val) {}

        static ExprPtr Create_BOOL(bool val) { return std::make_shared<LiteralSpecific>("BOOL", (uint64_t)val); }
        static ExprPtr Create_SINT(int8_t val) { return std::make_shared<LiteralSpecific>("SINT", (int64_t)val); }
        static ExprPtr Create_INT(int16_t val) { return std::make_shared<LiteralSpecific>("INT", (int64_t)val); }
        static ExprPtr Create_DINT(int32_t val) { return std::make_shared<LiteralSpecific>("DINT", (int64_t)val); }
        static ExprPtr Create_LINT(int64_t val) { return std::make_shared<LiteralSpecific>("LINT", (int64_t)val); }
        static ExprPtr Create_USINT(uint8_t val) { return std::make_shared<LiteralSpecific>("USINT", (uint64_t)val); }
        static ExprPtr Create_UINT(uint16_t val) { return std::make_shared<LiteralSpecific>("UINT", (uint64_t)val); }
        static ExprPtr Create_UDINT(uint32_t val) { return std::make_shared<LiteralSpecific>("UDINT", (uint64_t)val); }
        static ExprPtr Create_ULINT(uint64_t val) { return std::make_shared<LiteralSpecific>("ULINT", (uint64_t)val); }
        static ExprPtr Create_REAL(float val) { return std::make_shared<LiteralSpecific>("REAL", (double)val); }
        static ExprPtr Create_LREAL(double val) { return std::make_shared<LiteralSpecific>("LREAL", (double)val); }

        void Evaluate() override {}
    };

    class VariableDeclaration
    {
        std::string name;
        std::string type;

    public:
        VariableDeclaration() : name(), type() {}
        VariableDeclaration(std::string _name, std::string _type) : name(_name), type(_type) {}
    };

    class Variable : public Expr
    {
        std::string name;

    public:
        Variable(std::string _name) : name(_name) {}

        static ExprPtr CreateVariable(std::string _name) { return std::make_shared<Variable>(_name); }

        void Evaluate() {}
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
        void Evaluate() {}
    };

    class ExprStatement : public Statement
    {
        // expr;
        ExprPtr expr;

    public:
        ExprStatement(ExprPtr _expr){};
        static StatementPtr Make(ExprPtr _expr) { return std::make_shared<ExprStatement>(_expr); }
        void Evaluate() {}
    };

    class EmptyStatement : public Statement
    {
        // ;
    public:
        EmptyStatement(){};
        static StatementPtr Make() { return std::make_shared<EmptyStatement>(); }
        void Evaluate() {}
    };

    class POU{
            public:
        virtual void Evaluate() = 0;
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
        std::vector<VariableDeclaration> var_inout;
        std::vector<VariableDeclaration> var_temp;
        StatementList statement_list;
        
        Function(){};
        static POUPtr Make(Function fn){ return std::make_shared<Function>(fn);}
        void Evaluate() {}
    };

    class UnaryPlus : public Unary
    {
    public:
        UnaryPlus(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<UnaryPlus>(expr); }
        void Evaluate() {}
    };

    class UnaryMinus : public Unary
    {
    public:
        UnaryMinus(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<UnaryMinus>(expr); }
        void Evaluate() {}
    };

    class BooleanNOT : public Unary
    {
    public:
        BooleanNOT(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<BooleanNOT>(expr); }
        void Evaluate() {}
    };

    class Exponentiation : public Binary
    {
    public:
        Exponentiation(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Exponentiation>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class Multiply : public Binary
    {
    public:
        Multiply(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Multiply>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class Divide : public Binary
    {
    public:
        Divide(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Divide>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class Modulo : public Binary
    {
    public:
        Modulo(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Modulo>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class Add : public Binary
    {
    public:
        Add(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Add>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class Subtract : public Binary
    {
    public:
        Subtract(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Subtract>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class GreaterThan : public Binary
    {
    public:
        GreaterThan(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<GreaterThan>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class LessThan : public Binary
    {
    public:
        LessThan(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<LessThan>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class GreaterOrEqual : public Binary
    {
    public:
        GreaterOrEqual(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<GreaterOrEqual>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class LessOrEqual : public Binary
    {
    public:
        LessOrEqual(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<LessOrEqual>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class Equality : public Binary
    {
    public:
        Equality(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Equality>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class Inequality : public Binary
    {
    public:
        Inequality(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Inequality>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class BooleanAND : public Binary
    {
    public:
        BooleanAND(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanAND>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class BooleanOR : public Binary
    {
    public:
        BooleanOR(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanOR>(expr_l, expr_r); }
        void Evaluate() {}
    };

    class BooleanXOR : public Binary
    {
    public:
        BooleanXOR(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanXOR>(expr_l, expr_r); }
        void Evaluate() {}
    };

};
