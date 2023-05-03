#ifndef MY_AST_H
#define MY_AST_H

#include <memory>

namespace MyAst {

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class CharNode : public ASTNode {
public:
    explicit CharNode(char c) : c(c) {}
    char c;
};

class ConcatNode : public ASTNode {
public:
    ConcatNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
        : left(std::move(left)), right(std::move(right)) {}
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
};

class DisjunctionNode : public ASTNode {
public:
    DisjunctionNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right)
        : left(std::move(left)), right(std::move(right)) {}
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
};

class KleeneStarNode : public ASTNode {
public:
    explicit KleeneStarNode(std::shared_ptr<ASTNode> child) : child(std::move(child)) {}
    std::shared_ptr<ASTNode> child;
};

} // namespace MyAst

#endif // MY_AST_H
