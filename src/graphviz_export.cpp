#include "graphviz_export.h"
#include <sstream>
#include "regex_parser.h"

std::string GraphvizExport::export_ast(const RegexParser::ASTNode &ast) {
    std::stringstream output;
    output << "digraph AST {\n";
    int next_id = 0;
    export_ast_recursive(ast, output, next_id);
    output << "}\n";
    return output.str();
}

void GraphvizExport::export_ast_recursive(const RegexParser::ASTNode &ast, std::stringstream &output, int &next_id) {
    int current_id = next_id;
    next_id++;

    if (const auto *symbol_node = dynamic_cast<const RegexParser::SymbolNode *>(&ast)) {
        output << "  " << current_id << " [label=\"" << symbol_node->symbol << "\"];\n";
    }

    auto add_edge_and_recurse = [&](const RegexParser::ASTNode &child) {
        int child_id = next_id;
        output << "  " << current_id << " -> " << child_id << ";\n";
        export_ast_recursive(child, output, next_id);
    };

    if (const auto *concat_node = dynamic_cast<const RegexParser::ConcatNode *>(&ast)) {
        add_edge_and_recurse(*concat_node->left);
        add_edge_and_recurse(*concat_node->right);
    } else if (const auto *disjunction_node = dynamic_cast<const RegexParser::DisjunctionNode *>(&ast)) {
        add_edge_and_recurse(*disjunction_node->left);
        add_edge_and_recurse(*disjunction_node->right);
    } else if (const auto *kleene_star_node = dynamic_cast<const RegexParser::KleeneStarNode *>(&ast)) {
        add_edge_and_recurse(*kleene_star_node->child);
    }
}

std::string GraphvizExport::export_nfa(const NFA &nfa) {
    // Implémentez la fonctionnalité export_nfa ici.
    return "";
}

std::string GraphvizExport::export_dfa(const DFA &dfa) {
    // Implémentez la fonctionnalité export_dfa ici.
    return "";
}


