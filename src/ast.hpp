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

    class Unnary : public Expr
    {
    protected:
        ExprPtr expr;

    public:
        Unnary(ExprPtr ex) : expr(ex) {}
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
    };

    class Variable : public Expr
    {
    };

    class Function
    {
        std::string name;
        VariableDeclaration var_return;
        std::vector<VariableDeclaration> var_input;
        std::vector<VariableDeclaration> var_output;
        std::vector<VariableDeclaration> var_inout;
        std::vector<VariableDeclaration> var_temp;
        // StatementList statements;
    };

    class UnaryPlus : public Unnary
    {
    };
    class UnaryMinus : public Unnary
    {
    };
    class BooleanNOT : public Unnary
    {
    };
    class Exponentiation : public Binary
    {
    };
    class Multiply : public Binary
    {
    };
    class Divide : public Binary
    {
    };
    class Modulo : public Binary
    {
    };
    class Add : public Binary
    {
    };
    class Subtract : public Binary
    {
    };
    class GreaterThan : public Binary
    {
    };
    class LessThan : public Binary
    {
    };
    class GreaterOrEqual : public Binary
    {
    };
    class LessOrEqual : public Binary
    {
    };
    class Equality : public Binary
    {
    };
    class Inequality : public Binary
    {
    };
    class BooleanAND : public Binary
    {
    };
    class BooleanOR : public Binary
    {
    };
    class BooleanXOR : public Binary
    {
    };
    class Assignment : public Binary
    {
    };

};
