
#include <algorithm> // Ajoutez cette ligne
#include "nfa_to_dfa.h"

// ... Le reste du code reste inchangé ...





NFAToDFA::NFAToDFA(const NFA& nfa) : nfa(nfa) {}

NFAToDFA::~NFAToDFA() {}

DFA NFAToDFA::convert() {
    DFA dfa;

    std::set<State> start_nfa_state_set = nfa.epsilon_closure(nfa.get_start_state());
    State start_dfa_state = dfa.create_state(is_final(start_nfa_state_set));

    std::vector<std::set<State>> unprocessed_state_sets;
    unprocessed_state_sets.push_back(start_nfa_state_set);

    while (!unprocessed_state_sets.empty()) {
        std::set<State> current_state_set = unprocessed_state_sets.back();
        unprocessed_state_sets.pop_back();

        State current_dfa_state = dfa.create_state(false);

        for (char symbol : nfa.get_alphabet()) {
            std::set<State> next_nfa_state_set = get_next_nfa_state_set(current_state_set, symbol);
            State next_dfa_state = dfa.create_state(is_final(next_nfa_state_set));

// Modification ici
            
            dfa.add_transition(current_dfa_state, symbol, next_dfa_state);


            if (next_nfa_state_set.empty()) {
                continue;
            }

            // Modification ici
            auto it = std::find_if(unprocessed_state_sets.begin(), unprocessed_state_sets.end(), [&](const std::set<State>& s) { return s == next_nfa_state_set; });
            if (it == unprocessed_state_sets.end()) {
                unprocessed_state_sets.push_back(next_nfa_state_set);
            }
        }
    }
    
    

    return dfa;
}

bool NFAToDFA::is_final(const std::set<State>& state_set) {
    for (const State& state : state_set) {
        if (nfa.is_final_state(state)) {
            return true;
        }
    }
    return false;
}

std::set<State> NFAToDFA::get_next_nfa_state_set(const std::set<State>& state_set, char symbol) {
    std::set<State> next_state_set;
    for (const State& state : state_set) {
        std::set<State> reachable_states = nfa.get_reachable_states(state, symbol);
        next_state_set.insert(reachable_states.begin(), reachable_states.end());
    }
    return next_state_set;
}


