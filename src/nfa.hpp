#ifndef NFA_HPP
#define NFA_HPP

#include "ast.hpp"

struct State;
struct Transition;

struct State {
    int id;
    Transition *transitions;
    State *next;
};

struct Transition {
    State *from;
    State *to;
    char symbol;
    Transition *next;
};

struct NFA {
    State *start;
    State *accept;
};

NFA generate_NFA(TreeNode *root);

#endif // NFA_HPP
