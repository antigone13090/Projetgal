#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>

class State {
public:
    static const int INVALID_ID = -1;

    State(int id = INVALID_ID, bool isFinal = false) : id_(id), isFinal_(isFinal) {}

    int getId() const {
        return id_;
    }

    bool isFinal() const {
        return isFinal_;
    }

    bool operator<(const State &rhs) const {
        return id_ < rhs.id_;
    }

    bool operator==(const State &rhs) const {
        return id_ == rhs.id_;
    }

    friend std::ostream &operator<<(std::ostream &os, const State &state) {
        os << state.id_;
        return os;
    }

private:
    int id_;
    bool isFinal_;
};

#endif // STATE_HPP

