#include "dfa.h"

DFA::DFA() {
}

State DFA::create_state(bool isFinal) {
    int id = states.size();
    State new_state(id, isFinal);
    states.push_back(new_state);
    return new_state;
}

void DFA::addState(const State &state) {
    states.push_back(state);
}

void DFA::setInitialState(const State &state) {
    initialState = state;
}

void DFA::add_transition(const State &from, char input, const State &to) {
    transitions[from][input] = to;
}

State DFA::getInitialState() const {
    return initialState;
}

State DFA::get_target_state(const State &from, char input) const {
    auto transition = transitions.find(from);
    if (transition != transitions.end()) {
        auto target_state = transition->second.find(input);
        if (target_state != transition->second.end()) {
            return target_state->second;
        }
    }
    return State(); // Returns a default state (-1, false) in case of error
}

bool DFA::accepts(const std::string &input) const {
    State current_state = initialState;
    for (const char &symbol : input) {
        current_state = get_target_state(current_state, symbol);
        if (current_state.getId() == -1) {
            return false;
        }
    }
    return current_state.isFinal();
}

// Added methods
const std::vector<State>& DFA::get_states() const {
    return states;
}

bool DFA::is_final_state(const State &state) const {
    return state.isFinal();
}

const std::map<State, std::map<char, State>>& DFA::get_transitions() const {
    return transitions;
}

// Adding implementations for the missing methods
State DFA::get_initial_state() const {
    return initialState;
}

std::set<State> DFA::get_final_states() const {
    std::set<State> final_states;
    for (const auto &state : states) {
        if (state.isFinal()) { // Corrected the method name here
            final_states.insert(state);
        }
    }
    return final_states;
}


