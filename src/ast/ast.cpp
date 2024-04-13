#include "ast.hpp"

namespace AST
{

    std::string Function::GetC_Declaration() {
        
    };


    DataType UnaryPlus::GetDataType()
    {
        if (expr == nullptr)
            return DataType::UNNOWN;

        return expr->GetDataType();
    }

    DataType UnaryMinus::GetDataType()
    {
        if (expr == nullptr)
            return DataType::UNNOWN;

        return expr->GetDataType();
    }

    DataType BooleanNOT::GetDataType()
    {
        if (expr == nullptr)
            return DataType::UNNOWN;

        return expr->GetDataType();
    }

    DataType Exponentiation::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Multiply::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Divide::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Modulo::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Add::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType Subtract::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType GreaterThan::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }
    
    DataType LessThan::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType GreaterOrEqual::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType LessOrEqual::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType Equality::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType Inequality::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return DataType::BOOL;
    }

    DataType BooleanAND::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

    DataType BooleanOR::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }
    
    DataType BooleanXOR::GetDataType()
    {
        if (expr_l == nullptr)
            return DataType::UNNOWN;

        if (expr_r == nullptr)
            return DataType::UNNOWN;

        DataType data_l = expr_l->GetDataType();
        DataType data_r = expr_r->GetDataType();

        if (data_l != data_r)
            return DataType::UNNOWN;

        return data_l;
    }

}
