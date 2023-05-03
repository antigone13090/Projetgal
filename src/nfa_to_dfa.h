#ifndef NFA_TO_DFA_H
#define NFA_TO_DFA_H

#include "nfa.h"
#include "dfa.h"

class NFAToDFA {
public:
    NFAToDFA(const NFA& nfa);
    ~NFAToDFA();
    DFA convert();

private:
    const NFA& nfa;

    bool is_final(const std::set<State>& state_set);
    std::set<State> get_next_nfa_state_set(const std::set<State>& state_set, char symbol);
};

#endif // NFA_TO_DFA_H

