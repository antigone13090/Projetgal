#include "state.h"

const State State::INVALID = State(-1, false);

State::State(int id, bool is_final) : id(id), final_state(is_final) {}

int State::getId() const {
    return id;
}

bool State::isFinal() const {
    return final_state;
}

void State::setId(int id) {
    this->id = id;
}

void State::setFinal(bool is_final) {
    final_state = is_final;
}

bool State::operator<(const State &other) const {
    if (id < other.id) {
        return true;
    } else if (id == other.id) {
        return final_state < other.final_state;
    }
    return false;
}

bool State::operator==(const State &other) const {
    return id == other.id && final_state == other.final_state;
}

bool State::operator!=(const State &other) const {
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const State &state) {
    os << "State(" << state.getId() << ", " << (state.isFinal() ? "final" : "not final") << ")";
    return os;
}

