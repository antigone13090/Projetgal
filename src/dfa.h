#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "state.h"

class DFA {
public:
    DFA();
    void setInitialState(const State &state);
    State create_state(bool isFinal);
    void addState(const State &state);
    void add_transition(const State &from, char input, const State &to);

    State getInitialState() const;
    State get_target_state(const State &from, char input) const;
    bool accepts(const std::string &input) const;

    // Added methods
    const std::vector<State>& get_states() const;
    bool is_final_state(const State &state) const;
    const std::map<State, std::map<char, State>>& get_transitions() const;
    // Adding missing methods
    State get_initial_state() const;
    std::set<State> get_final_states() const;

private:
    std::vector<State> states;
    State initialState;
    std::map<State, std::map<char, State>> transitions;
};

#endif // DFA_H



