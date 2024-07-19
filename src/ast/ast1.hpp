#pragma once

#include <string>
#include <vector>
#include <memory>

namespace AST
{

    

    // interface
    class Expression
    {
    public:
        virtual std::string ToString() = 0;
    };

    typedef std::shared_ptr<Expression> ExprPtr;

    //********************************************************************************************

    struct Statement
    {
        virtual std::string ToString() = 0;
    };

    typedef std::shared_ptr<Statement> StmtPtr;
    typedef std::vector<StmtPtr> StmtList;

    //********************************************************************************************

    struct Pou
    {
        std::string name;
        virtual std::string ToString() = 0;
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

#define BINARY_CONSTRUCTOR(class_name) \
    class_name(ExprPtr l, ExprPtr r) : BinaryExpression(l, r){};

#define BINARY_TOSTRING(operator_str)                                             \
    std::string ToString() override                                               \
    {                                                                             \
        std::string l_str = (left != nullptr) ? left->ToString() : "____";        \
        std::string r_str = (right != nullptr) ? right->ToString() : "____";      \
        return "(" + l_str + " " + std::string(operator_str) + " " + r_str + ")"; \
    }

    //********************************************************************************************

    class UnaryExpression : public Expression
    {
    protected:
        ExprPtr expr;
        UnaryExpression(ExprPtr e) : expr(e) {}
    };

#define UNARY_CONSTRUCTOR(class_name) \
    class_name(ExprPtr e) : UnaryExpression(e){};

#define UNARY_TOSTRING(operator_str)                                          \
    std::string ToString() override                                           \
    {                                                                         \
        std::string expr_str = (expr != nullptr) ? expr->ToString() : "____"; \
        return "(" + std::string(operator_str) + " " + expr_str + ")";        \
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

        std::string ToString()
        {
            std::string vars_str;
            vars_str += "var:\n";
            for (auto v : var)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_input:\n";
            for (auto v : var_input)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_output:\n";
            for (auto v : var_output)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_in_out:\n";
            for (auto v : var_in_out)
                vars_str += "\t" + v.ToString() + "\n";

            return "{FUNCTION " + name + "\n" + vars_str + "\n" + StatementListToString(statement_list) + "\n}";
        }
    };

    struct FunctionBlock : public Pou
    {
        StmtList statement_list;
        std::shared_ptr<Variable> result;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString()
        {
            std::string vars_str;
            vars_str += "var:\n";
            for (auto v : var)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_input:\n";
            for (auto v : var_input)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_output:\n";
            for (auto v : var_output)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_in_out:\n";
            for (auto v : var_in_out)
                vars_str += "\t" + v.ToString() + "\n";

            return "{FUNCTION_BLOCK  " + name + "\n" + vars_str + "\n" + StatementListToString(statement_list) + "\n}";
        }
    };

    struct Program : public Pou
    {
        StmtList statement_list;

        std::vector<Variable> var;
        std::vector<Variable> var_input;
        std::vector<Variable> var_output;
        std::vector<Variable> var_in_out;

        std::string ToString()
        {
            std::string vars_str;
            vars_str += "var:\n";
            for (auto v : var)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_input:\n";
            for (auto v : var_input)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_output:\n";
            for (auto v : var_output)
                vars_str += "\t" + v.ToString() + "\n";

            vars_str += "var_in_out:\n";
            for (auto v : var_in_out)
                vars_str += "\t" + v.ToString() + "\n";

            return "{PROGRAM  " + name + "\n" + vars_str + "\n" + StatementListToString(statement_list) + "\n}";
        }
    };

    //********************************************************************************************

    struct EmptyStatement : public Statement
    {
        std::string ToString()
        {
            return "{}";
        }
    };

    struct AssignmentStatement : public Statement
    {
        ExprPtr var;
        ExprPtr expr;

        AssignmentStatement(ExprPtr _var, ExprPtr _expr) : var(_var), expr(_expr) {}

        std::string ToString()
        {
            std::string expr_str = expr ? expr->ToString() : "____";
            std::string var_str = var ? var->ToString() : "____";
            return "{" + var_str + " := " + expr_str + "}";
        }
    };

    struct IfStatement : public Statement
    {
        ExprPtr condition;
        StmtList statement_list;

        IfStatement(ExprPtr cond, StmtList stmt_list) : condition(cond), statement_list(stmt_list) {}

        std::string ToString()
        {
            std::string expr_str = condition ? condition->ToString() : "____";
            return "{IF " + expr_str + " THEN\n" + StatementListToString(statement_list) + "\n}";
        }
    };

    struct WhileStatement : public Statement
    {
        ExprPtr condition;
        StmtList statement_list;

        WhileStatement(ExprPtr cond, StmtList stmt_list) : condition(cond), statement_list(stmt_list) {}

        std::string ToString()
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
    };

    //********************************************************************************************

    struct Literal : public Expression
    {
        std::string literal;
        Literal(std::string l) : literal(l){};
        std::string ToString()
        {
            return literal;
        }
    };

    struct VariableAccess : public Expression
    {
        std::string variable_name;
        VariableAccess(std::string l) : variable_name(l){};
        std::string ToString()
        {
            return variable_name;
        }
    };

    //********************************************************************************************

    struct Exponentiation : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Exponentiation);
        BINARY_TOSTRING("+");
    };

    struct Add : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Add);
        BINARY_TOSTRING("+");
    };

    struct Subtract : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Subtract);
        BINARY_TOSTRING("-");
    };

    struct Multiply : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Multiply);
        BINARY_TOSTRING("*");
    };

    struct Divide : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Divide);
        BINARY_TOSTRING("/");
    };

    struct Modulo : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Modulo);
        BINARY_TOSTRING("MOD");
    };

    struct Or : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Or);
        BINARY_TOSTRING("OR");
    };

    struct Xor : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Xor);
        BINARY_TOSTRING("XOR");
    };

    struct And : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(And);
        BINARY_TOSTRING("AND");
    };

    struct Gt : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Gt);
        BINARY_TOSTRING(">");
    };

    struct Lt : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Lt);
        BINARY_TOSTRING("<");
    };

    struct Geq : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Geq);
        BINARY_TOSTRING(">=");
    };

    struct Leq : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Leq);
        BINARY_TOSTRING("<=");
    };

    struct Eq : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Eq);
        BINARY_TOSTRING("=");
    };

    struct Neq : public BinaryExpression
    {
        BINARY_CONSTRUCTOR(Neq);
        BINARY_TOSTRING("<>");
    };

    /////

    struct UnaryPlus : public UnaryExpression
    {
        UNARY_CONSTRUCTOR(UnaryPlus);
        UNARY_TOSTRING("+");
    };
    struct UnaryMinus : public UnaryExpression
    {
        UNARY_CONSTRUCTOR(UnaryMinus);
        UNARY_TOSTRING("-");
    };
    struct Negation : public UnaryExpression
    {
        UNARY_CONSTRUCTOR(Negation);
        UNARY_TOSTRING("NOT");
    };

};
