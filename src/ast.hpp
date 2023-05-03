#ifndef AST_H
#define AST_H

typedef struct TreeNode TreeNode;

enum NodeType {
    NODE_SYMBOL,
    NODE_KLEENE_STAR,
    NODE_CONCATENATION,
    NODE_ALTERNATION
};

struct TreeNode {
    NodeType type;
    char symbol;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *create_symbol_node(char symbol);
TreeNode *create_kleene_star_node(TreeNode *left);
TreeNode *create_concatenation_node(TreeNode *left, TreeNode *right);
TreeNode *create_alternation_node(TreeNode *left, TreeNode *right);

void free_ast(TreeNode *root);

#endif // AST_H
