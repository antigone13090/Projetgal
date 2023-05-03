#ifndef REGEX_PARSER_H
#define REGEX_PARSER_H

#include <string>
#include <memory>
#include "nfa.h"

class RegexParser {
public:
    struct ASTNode {
        virtual ~ASTNode() = default;
    };

    struct SymbolNode : public ASTNode {
        explicit SymbolNode(char symbol) : symbol(symbol) {}
        char symbol;
    };

    struct ConcatNode : public ASTNode {
        ConcatNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
            : left(std::move(left)), right(std::move(right)) {}
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;
    };

    struct DisjunctionNode : public ASTNode {
        DisjunctionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
            : left(std::move(left)), right(std::move(right)) {}
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;
    };

    struct KleeneStarNode : public ASTNode {
        explicit KleeneStarNode(std::unique_ptr<ASTNode> child) : child(std::move(child)) {}
        std::unique_ptr<ASTNode> child;
    };

    RegexParser();
    ~RegexParser();
    NFA parse(const std::string &regex);
    const ASTNode &get_ast() const;

private:
    std::unique_ptr<ASTNode> ast_root_;
};

#endif // REGEX_PARSER_H

