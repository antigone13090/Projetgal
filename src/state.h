#ifndef STATE_H
#define STATE_H

#include <iostream>

class State {
public:
    static const State INVALID;
    State(int id = -1, bool isFinal = false);
    int getId() const;
    bool isFinal() const;
    void setId(int id);
    void setFinal(bool isFinal);

    bool operator<(const State &other) const;
    bool operator==(const State &other) const;
    bool operator!=(const State &other) const;

private:
    int id;
    bool final_state;
};

std::ostream &operator<<(std::ostream &os, const State &state);

#endif // STATE_H


