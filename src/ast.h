#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <sstream>

namespace MyAst {

struct TreeNode {
    virtual ~TreeNode() = default;
};

struct NumberNode : public TreeNode {
    explicit NumberNode(double value) : value(value) {}

    double value;
};

std::unique_ptr<TreeNode> parse_expression(std::istringstream& input);
std::unique_ptr<TreeNode> parse_number(std::istringstream& input);
double evaluate(const TreeNode* node);

} // namespace MyAst

#endif // AST_H


