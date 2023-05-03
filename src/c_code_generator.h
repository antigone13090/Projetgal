#ifndef C_CODE_GENERATOR_H
#define C_CODE_GENERATOR_H

#include "dfa.h"
#include <string>
#include <set>

class CCodeGenerator {
public:
    CCodeGenerator(const DFA &dfa);

    std::string generate() const;

private:
    std::set<char> get_alphabet(const DFA &dfa) const;

    DFA minimized_dfa_;
};

#endif // C_CODE_GENERATOR_H

