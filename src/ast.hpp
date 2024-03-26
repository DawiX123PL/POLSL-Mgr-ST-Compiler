#pragma once

#include <memory>
#include <inttypes.h>
#include <string>
#include <vector>

namespace AST
{

    enum class Type
    {
        NONE, //

        BOOL,
        INT,
        REAL,
    };

    // abstract classes
    class Expr
    {
    protected:
        Type return_type;

        Expr(Type _return_type) : return_type(_return_type) {}

    public:
        virtual void Evaluate() = 0;
    };

    typedef std::shared_ptr<AST::Expr> ExprPtr;

    class Unnary : public Expr
    {
    protected:
        ExprPtr expr;
    };

    class Binary : public Expr
    {
    protected:
        ExprPtr r_expr;
        ExprPtr l_expr;
    };

    //
    class Literal : public Expr
    {
        double d_value;
        int64_t i_value;

    public:
        Literal(double value) : Expr(Type::REAL), d_value(value), i_value(value) {}
        Literal(int64_t value) : Expr(Type::INT), d_value(value), i_value(value) {}

        void Evaluate(){};
    };

    class Variable
    {
        std::string name;
        std::string type;
        ExprPtr initial_value;

    public:
        const std::string &GetName() { return name; }

        Variable()
            : name(),
              type(),
              initial_value(nullptr) {}

        Variable(std::string _name, std::string _type)
            : name(_name),
              type(_type),
              initial_value(nullptr) {}

        Variable(std::string _name, std::string _type, ExprPtr _initial)
            : name(_name),
              type(_type),
              initial_value(_initial) {}
    };

    class Function : public Expr
    {
        // 1. declaration
        //    1. identifier
        //    2. return type
        //    3. VAR_INPUT VAR_OUTPUT VAR_IN_OUT VAR_TEMP
        // 2. definition
        //    1. statement list

        std::string name;
        Variable var_return;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_inout;
        std::vector<Variable> var_temp;
        std::vector<Expr> statements;
    };

    // operators
    class FunctionCall : public Expr
    {
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
