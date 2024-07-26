#pragma once

//****************************************************************************************/
// BinaryOperator


#define BINARY_CONSTRUCTOR(class_name) \
    class_name(ExprPtr l, ExprPtr r) : BinaryExpression(l, r){};

#define BINARY_TOSTRING(operator_str)                                             \
    std::string ToString() override                                               \
    {                                                                             \
        std::string l_str = (left != nullptr) ? left->ToString() : "____";        \
        std::string r_str = (right != nullptr) ? right->ToString() : "____";      \
        return "(" + l_str + " " + std::string(operator_str) + " " + r_str + ")"; \
    }

#define BINARY_OPERATOR_METHODS(class_name, operator_str) \
    BINARY_CONSTRUCTOR(class_name);                       \
    BINARY_TOSTRING(operator_str);                        \
    llvm::Value *LLVMGetValue(LocalScope *ls, LLVMCompilerContext *llvm_cc) override;


//****************************************************************************************/
// UnaryOperator


#define UNARY_CONSTRUCTOR(class_name) \
    class_name(ExprPtr e) : UnaryExpression(e){};

#define UNARY_TOSTRING(operator_str)                                          \
    std::string ToString() override                                           \
    {                                                                         \
        std::string expr_str = (expr != nullptr) ? expr->ToString() : "____"; \
        return "(" + std::string(operator_str) + " " + expr_str + ")";        \
    }
