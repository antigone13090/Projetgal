#ifndef DFA_MINIMIZATION_H
#define DFA_MINIMIZATION_H

#include "dfa.h"
#include <map>
#include <set>


class DFAMinimization {
public:
    DFA minimize(const DFA &dfa);

private:
    std::set<char> get_alphabet(const DFA &dfa);
    std::set<State> get_reachable_states(const DFA &dfa);
    std::map<State, std::set<State>> initial_partition(const DFA &dfa);
    std::map<State, std::set<State>> refine_partition(const DFA &dfa, const std::map<State, std::set<State>> &partition);
};

#endif // DFA_MINIMIZATION_H

