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

    enum class Operation
    {
        UNARY_PLUS,
        UNARY_MINUS,
        BOOLEAN_NOT,
        EXPONENTIATION,
        MULTIPLY,
        DIVIDE,
        MODULO,
        ADD,
        SUBTRACT,
        GREATER_THAN,
        LESS_THAN,
        GREATER_OR_EQUAL,
        LESS_OR_EQUAL,
        EQUALITY,
        INEQUALITY,
        BOOLEAN_AND,
        BOOLEAN_OR,
        BOOLEAN_XOR,
        ASSIGNMENT,
        DEREFERENCE,
    };

    // abstract classes
    class Expr
    {
    protected:
        Type return_type;

        Expr() : return_type(Type::NONE) {}
        Expr(Type _return_type) : return_type(_return_type) {}

    public:
        virtual void Evaluate() = 0;
    };

    typedef std::shared_ptr<AST::Expr> ExprPtr;

    class Unary : public Expr
    {
    protected:
        Operation operation;
        ExprPtr expr;

    public:
        Unary(Operation op, ExprPtr ex) : operation(op), expr(ex) {}
        void Evaluate()
        {
        }
    };

    class Binary : public Expr
    {
    protected:
        Operation operation;
        ExprPtr l_expr;
        ExprPtr r_expr;

    public:
        Binary(Operation op, ExprPtr l_ex, ExprPtr r_ex) : operation(op), l_expr(l_ex), r_expr(r_ex) {}
        void Evaluate()
        {
        }
    };

    class FunctionCall : public Expr
    {
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

    class VariableDefinition
    {
        std::string name;
        std::string type;
        ExprPtr initial_value;

    public:
        const std::string &GetName() { return name; }

        VariableDefinition()
            : name(),
              type(),
              initial_value(nullptr) {}

        VariableDefinition(std::string _name, std::string _type)
            : name(_name),
              type(_type),
              initial_value(nullptr) {}

        VariableDefinition(std::string _name, std::string _type, ExprPtr _initial)
            : name(_name),
              type(_type),
              initial_value(_initial) {}
    };

    class Variable : public Expr
    {
        std::string name;

        void Evaluate(){};

    public:
        Variable(std::string _name)
            : name(_name) {}
    };

    class Statement
    {
        void Evaluate(){};
    };

    typedef std::shared_ptr<Statement> StatementPtr;
    typedef std::vector<StatementPtr> StatementList;

    class IfStatement : public Statement
    {
    };

    class AssignStatement : public Statement
    {
        ExprPtr variable;
        ExprPtr expression;

    public:
        AssignStatement(ExprPtr var, ExprPtr expr): variable(var), expression(expr){}
    };

    class Function
    {
        // 1. declaration
        //    1. identifier
        //    2. return type
        //    3. VAR_INPUT VAR_OUTPUT VAR_IN_OUT VAR_TEMP
        // 2. definition
        //    1. statement list
    public:
        std::string name;
        VariableDefinition var_return;
        std::vector<VariableDefinition> var_input;
        std::vector<VariableDefinition> var_output;
        std::vector<VariableDefinition> var_in_out;
        std::vector<VariableDefinition> var_temp;
        StatementList statements;

        void Evaluate(){
            
        };
    };

    // class UnaryPlus : public Unnary
    // {
    // };
    // class UnaryMinus : public Unnary
    // {
    // };
    // class BooleanNOT : public Unnary
    // {
    // };
    // class Exponentiation : public Binary
    // {
    // };
    // class Multiply : public Binary
    // {
    // };
    // class Divide : public Binary
    // {
    // };
    // class Modulo : public Binary
    // {
    // };
    // class Add : public Binary
    // {
    // };
    // class Subtract : public Binary
    // {
    // };
    // class GreaterThan : public Binary
    // {
    // };
    // class LessThan : public Binary
    // {
    // };
    // class GreaterOrEqual : public Binary
    // {
    // };
    // class LessOrEqual : public Binary
    // {
    // };
    // class Equality : public Binary
    // {
    // };
    // class Inequality : public Binary
    // {
    // };
    // class BooleanAND : public Binary
    // {
    // };
    // class BooleanOR : public Binary
    // {
    // };
    // class BooleanXOR : public Binary
    // {
    // };
    // class Assignment : public Binary
    // {
    // };

};
