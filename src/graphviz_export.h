#pragma once

#include <string>
#include "nfa.h"
#include "dfa.h"
#include "regex_parser.h"

class GraphvizExport {
public:
    static std::string export_ast(const RegexParser::ASTNode &ast);
    static std::string export_nfa(const NFA &nfa);
    static std::string export_dfa(const DFA &dfa);

private:
    static void export_ast_recursive(const RegexParser::ASTNode &ast, std::stringstream &output, int &next_id);
};

