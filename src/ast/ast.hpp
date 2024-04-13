#pragma once

#include <memory>
#include <inttypes.h>
#include <string>
#include <vector>
#include <tuple>


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

    // abstract classes
    class Expr
    {
    public:
        //
        virtual void Evaluate() = 0;
        virtual DataType GetDataType() = 0;
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
    };

    class VariableDeclaration
    {
        std::string name;
        std::string type;
        ExprPtr initial_value;

    public:
        VariableDeclaration() : name(), type(), initial_value(nullptr) {}
        VariableDeclaration(std::string _name, std::string _type) : name(_name), type(_type), initial_value(nullptr) {}
        VariableDeclaration(std::string _name, std::string _type, ExprPtr _initial_value) : name(_name), type(_type), initial_value(_initial_value) {}
    };

    class Variable : public Expr
    {
        std::string name;

    public:
        Variable(std::string _name) : name(_name) {}
        static ExprPtr CreateVariable(std::string _name) { return std::make_shared<Variable>(_name); }

        void Evaluate() override {}
        DataType GetDataType() override { return DataType::UNNOWN; } // TODO: get variable data type
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
        virtual std::string GetC_Declaration() = 0;
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
        static POUPtr Make(Function fn) { return std::make_shared<Function>(fn); }
        void Evaluate() override {}
        std::string GetC_Declaration() override;
    };

    class UnaryPlus : public Unary
    {
    public:
        UnaryPlus(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<UnaryPlus>(expr); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class UnaryMinus : public Unary
    {
    public:
        UnaryMinus(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<UnaryMinus>(expr); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class BooleanNOT : public Unary
    {
    public:
        BooleanNOT(ExprPtr expr) : Unary(expr){};
        static ExprPtr Make(ExprPtr expr) { return std::make_shared<BooleanNOT>(expr); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Exponentiation : public Binary
    {
    public:
        Exponentiation(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Exponentiation>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Multiply : public Binary
    {
    public:
        Multiply(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Multiply>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Divide : public Binary
    {
    public:
        Divide(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Divide>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Modulo : public Binary
    {
    public:
        Modulo(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Modulo>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Add : public Binary
    {
    public:
        Add(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Add>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Subtract : public Binary
    {
    public:
        Subtract(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Subtract>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class GreaterThan : public Binary
    {
    public:
        GreaterThan(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<GreaterThan>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class LessThan : public Binary
    {
    public:
        LessThan(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<LessThan>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class GreaterOrEqual : public Binary
    {
    public:
        GreaterOrEqual(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<GreaterOrEqual>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class LessOrEqual : public Binary
    {
    public:
        LessOrEqual(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<LessOrEqual>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Equality : public Binary
    {
    public:
        Equality(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Equality>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class Inequality : public Binary
    {
    public:
        Inequality(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<Inequality>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class BooleanAND : public Binary
    {
    public:
        BooleanAND(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanAND>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class BooleanOR : public Binary
    {
    public:
        BooleanOR(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanOR>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

    class BooleanXOR : public Binary
    {
    public:
        BooleanXOR(ExprPtr expr_l, ExprPtr expr_r) : Binary(expr_l, expr_r){};
        static ExprPtr Make(ExprPtr expr_l, ExprPtr expr_r) { return std::make_shared<BooleanXOR>(expr_l, expr_r); }
        void Evaluate() override {}
        DataType GetDataType() override;
    };

};
