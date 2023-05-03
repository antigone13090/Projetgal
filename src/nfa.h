#ifndef NFA_H
#define NFA_H

#include "state.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

class NFAState : public State {
public:
    NFAState(int id, bool is_final);
};

class NFA {
public:
    NFA();
    ~NFA();

    void addState(int id, bool is_final);
    void addTransition(int from, char input, int to);
    void addEpsilonTransition(int from, int to);
    int getTransition(int state_id, char input);
    NFAState* getStateById(int id);
    void printStates() const;

    NFA unionWith(const NFA& other);
    NFA applyKleeneStar();
    static NFA createFromLiteral(char literal);
    NFA concatenateWith(const NFA& other);

    std::set<State> epsilon_closure(const State& state) const;
    std::set<State> get_reachable_states(const State& state, char symbol) const;
    const std::set<char>& get_alphabet() const;
    bool is_final_state(const State& state) const;
    const State& get_start_state() const;

private:
    std::vector<NFAState> states;
    std::unordered_map<int, std::unordered_map<char, std::set<int>>> transitions;
    std::unordered_map<int, std::set<int>> epsilon_transitions;
};

#endif


