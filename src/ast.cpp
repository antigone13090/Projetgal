#include "ast.h"
#include <cctype>
#include <memory>

namespace MyAst {

// Ajoutez cette fonction si vous utilisez une version de C++ inférieure à C++14
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

std::unique_ptr<TreeNode> parse_expression(std::istringstream& input);
std::unique_ptr<TreeNode> parse_number(std::istringstream& input);

std::unique_ptr<TreeNode> parse_expression(std::istringstream& input) {
    std::unique_ptr<TreeNode> left = MyAst::parse_number(input);
    // ...
    return left;
}

std::unique_ptr<TreeNode> parse_number(std::istringstream& input) {
    double number;
    input >> number;
    return MyAst::make_unique<NumberNode>(number);
}

double evaluate(const TreeNode* node) {
    // ...
    if (const NumberNode* num_node = dynamic_cast<const NumberNode*>(node)) {
        return num_node->value;
    }
    // Ajoutez d'autres cas pour gérer d'autres types de nœuds dans l'arbre AST
    return 0.0;
}

} // namespace MyAst

