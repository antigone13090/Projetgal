#ifndef DFA_HPP
#define DFA_HPP
#include "nfa.hpp"

void print_nfa_state_set(State *state_set);

struct DFAState;
struct DFATransition;

struct DFAState {
    int id;
    State *nfa_states;
    DFATransition *transitions;
    DFAState *next;
};

struct DFATransition {
    DFAState *from;
    DFAState *to;
    char symbol;
    DFATransition *next;
};

struct DFA {
    DFAState *start;
};

DFA convert_NFA_to_DFA(NFA nfa);

#endif // DFA_HPP
