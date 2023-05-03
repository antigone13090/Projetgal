#include "dfa_minimization.h"
#include <queue>

DFA DFAMinimization::minimize(const DFA &dfa) {
    DFA minimized_dfa;
    std::map<State, std::set<State>> partition = initial_partition(dfa);
    partition = refine_partition(dfa, partition);

    std::map<State, State> old_to_new_state;
    for (const auto &group : partition) {
        State new_state = minimized_dfa.create_state(dfa.is_final_state(group.first));
        old_to_new_state[group.first] = new_state;
        for (const auto &state : group.second) {
            old_to_new_state[state] = new_state;
        }
    }

    for (const auto &state : dfa.get_states()) {
        for (char symbol : get_alphabet(dfa)) {
            State target_state = dfa.get_target_state(state, symbol);
            if (target_state != State::INVALID) {
                minimized_dfa.add_transition(old_to_new_state[state], symbol, old_to_new_state[target_state]);
            }
        }
    }

    minimized_dfa.setInitialState(old_to_new_state[dfa.getInitialState()]);
    return minimized_dfa;
}

std::set<char> DFAMinimization::get_alphabet(const DFA &dfa) {
    std::set<char> alphabet;
    const auto& transitions = dfa.get_transitions();
    for (const auto &state_transitions : transitions) {
        for (const auto &symbol_to_state : state_transitions.second) {
            alphabet.insert(symbol_to_state.first);
        }
    }
    return alphabet;
}

std::set<State> DFAMinimization::get_reachable_states(const DFA &dfa) {
    std::set<State> reachable_states;
    std::queue<State> state_queue;
    state_queue.push(dfa.getInitialState());

    while (!state_queue.empty()) {
        State current_state = state_queue.front();
        state_queue.pop();

        if (reachable_states.find(current_state) == reachable_states.end()) {
            reachable_states.insert(current_state);
            for (char symbol : get_alphabet(dfa)) {
                State target_state = dfa.get_target_state(current_state, symbol);
                if (target_state != State::INVALID) {
                    state_queue.push(target_state);
                }
            }
        }
    }

    return reachable_states;
}

std::map<State, std::set<State>> DFAMinimization::initial_partition(const DFA &dfa) {
    std::map<State, std::set<State>> partition;

    std::set<State> final_states, non_final_states;
    for (const auto &state : get_reachable_states(dfa)) {
        if (dfa.is_final_state(state)) {
            final_states.insert(state);
        } else {
            non_final_states.insert(state);
        }
    }

    if (!final_states.empty()) {
        State representative_final_state = *final_states.begin();
        partition[representative_final_state] = final_states;
    }

    if (!non_final_states.empty()) {
        State representative_non_final_state = *non_final_states.begin();
        partition[representative_non_final_state] = non_final_states;
    }

    return partition;
}

std::map<State, std::set<State>> DFAMinimization::refine_partition(const DFA &dfa, const std::map<State, std::set<State>> &partition) {
    std::map<State, std::set<State>> new_partition;
    bool refined = false;

    for (const auto &group : partition) {
        std::map<State, std::set<State>> sub_partition;

        for (const auto    &state : group.second) {
        bool assigned = false;
        for (auto &sub_group : sub_partition) {
            State representative = sub_group.first;
            bool equivalent = true;

            for (char symbol : get_alphabet(dfa)) {
                State target_state1 = dfa.get_target_state(state, symbol);
                State target_state2 = dfa.get_target_state(representative, symbol);

                if (partition.find(target_state1)->first != partition.find(target_state2)->first) {
                    equivalent = false;
                    break;
                }
            }

            if (equivalent) {
                sub_group.second.insert(state);
                assigned = true;
                break;
            }
        }

        if (!assigned) {
            sub_partition[state] = {state};
        }
    }

    if (sub_partition.size() > 1) {
        refined = true;
    }

    for (const auto &sub_group : sub_partition) {
        new_partition[sub_group.first] = sub_group.second;
    }
}

if (refined) {
    return refine_partition(dfa, new_partition);
} else {
    return partition;
}
}
				


