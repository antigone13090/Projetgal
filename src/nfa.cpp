#include "nfa.h"

NFAState::NFAState(int id, bool is_final) : State(id, is_final) {}

NFA::NFA() {}

NFA::~NFA() {}

void NFA::addState(int id, bool is_final) {
    states.emplace_back(id, is_final);
}

void NFA::addTransition(int from, char input, int to) {
    transitions[from][input].insert(to);
}

void NFA::addEpsilonTransition(int from, int to) {
    epsilon_transitions[from].insert(to);
}

int NFA::getTransition(int state_id, char input) {
    auto it = transitions.find(state_id);
    if (it != transitions.end()) {
        auto input_it = it->second.find(input);
        if (input_it != it->second.end()) {
            return *input_it->second.begin();
        }
    }
    return -1;
}

NFAState* NFA::getStateById(int id) {
    for (auto& state : states) {
        if (state.getId() == id) {
            return &state;
        }
    }
    return nullptr;
}

void NFA::printStates() const {
    for (const auto& state : states) {
        std::cout << "ID: " << state.getId() << ", Final: " << (state.isFinal() ? "Yes" : "No") << std::endl;
    }
}
NFA NFA::unionWith(const NFA& other) {
    NFA result;

    int offset = states.size();
    for (const auto& state : states) {
        result.addState(state.getId(), state.isFinal());
    }
    for (const auto& state : other.states) {
        result.addState(state.getId() + offset, state.isFinal());
    }

    for (const auto& t : transitions) {
        for (const auto& input_states : t.second) {
            for (int to_state : input_states.second) {
                result.addTransition(t.first, input_states.first, to_state);
            }
        }
    }

    for (const auto& t : other.transitions) {
        for (const auto& input_states : t.second) {
            for (int to_state : input_states.second) {
                result.addTransition(t.first + offset, input_states.first, to_state + offset);
            }
        }
    }

    return result;
}

NFA NFA::applyKleeneStar() {
    NFA result;
    int start_state = states.size();
    result.addState(start_state, true);

    for (const auto& state : states) {
        result.addState(state.getId(), state.isFinal());
    }

    for (const auto& t : transitions) {
        for (const auto& input_states : t.second) {
            for (int to_state : input_states.second) {
                result.addTransition(t.first, input_states.first, to_state);
            }
        }
    }

    for (const auto& state : states) {
        if (state.isFinal()) {
            result.addEpsilonTransition(state.getId(), start_state);
        }
    }

    result.addEpsilonTransition(start_state, 0);

    return result;
}

NFA NFA::createFromLiteral(char literal) {
    NFA result;
    result.addState(0, false);
    result.addState(1, true);
    result.addTransition(0, literal, 1);
    return result;
}



NFA NFA::concatenateWith(const NFA& other) {
    NFA result;

    int offset = states.size();
    for (const auto& state : states) {
        result.addState(state.getId(), state.isFinal() && other.states.empty());
    }
    for (const auto& state : other.states) {
        result.addState(state.getId() + offset, state.isFinal());
    }

    for (const auto& t : transitions) {
        for (const auto& input_states : t.second) {
            for (int to_state : input_states.second) {
                result.addTransition(t.first, input_states.first, to_state);
            }
        }
    }

    for (const auto& t : other.transitions) {
        for (const auto& input_states : t.second) {
            for (int to_state : input_states.second) {
                result.addTransition(t.first + offset, input_states.first, to_state + offset);
            }
        }
    }

    for (const auto& state : states) {
        if (state.isFinal()) {
            result.addEpsilonTransition(state.getId(), offset);
        }
    }

    return result;

}

