#include "regex_parser.h"
#include <stack>


#include "regex_parser.h"
#include <stack>
#include <stdexcept>

RegexParser::RegexParser() {}
RegexParser::~RegexParser() {}

NFA RegexParser::parse(const std::string &regex) {
    std::stack<NFA> nfa_stack;
    std::stack<char> operator_stack;

    for (size_t i = 0; i < regex.size(); i++) {
        char c = regex[i];

        if (c == '(') {
            operator_stack.push(c);
        } else if (c == ')') {
            while (!operator_stack.empty() && operator_stack.top() != '(') {
                char op = operator_stack.top();
                operator_stack.pop();

                if (op == '|') {
                    NFA right_nfa = nfa_stack.top(); nfa_stack.pop();
                    NFA left_nfa = nfa_stack.top(); nfa_stack.pop();
                    NFA union_nfa = left_nfa.unionWith(right_nfa);
                    nfa_stack.push(union_nfa);
                }
            }
            if (!operator_stack.empty() && operator_stack.top() == '(') {
                operator_stack.pop();
            }
        } else if (c == '*') {
            NFA kleene_nfa = nfa_stack.top().applyKleeneStar();
            nfa_stack.pop();
            nfa_stack.push(kleene_nfa);
        } else if (c == '|') {
            operator_stack.push(c);
        } else {
            NFA literal_nfa = NFA::createFromLiteral(c);
            if (!nfa_stack.empty() && (operator_stack.empty() || operator_stack.top() != '|')) {
                NFA top_nfa = nfa_stack.top();
                nfa_stack.pop();
                NFA concat_nfa = top_nfa.concatenateWith(literal_nfa);
                nfa_stack.push(concat_nfa);
            } else {
                nfa_stack.push(literal_nfa);
            }
        }
    }

    while (!operator_stack.empty()) {
        char op = operator_stack.top();
        operator_stack.pop();

        if (op == '|') {
            NFA right_nfa = nfa_stack.top(); nfa_stack.pop();
            NFA left_nfa = nfa_stack.top(); nfa_stack.pop();
            NFA union_nfa = left_nfa.unionWith(right_nfa);
            nfa_stack.push(union_nfa);
        }
    }

    if (nfa_stack.size() != 1) {
        throw std::runtime_error("Erreur de syntaxe: expression mal formée");
    }

    return nfa_stack.top();
}

const RegexParser::ASTNode &RegexParser::get_ast() const {
    // You should return the root of your AST here.
    // Since your current implementation does not build an AST, 
    // we will throw an exception if someone tries to call this function.
    throw std::runtime_error("get_ast() function is not implemented");
}

