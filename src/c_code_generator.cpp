#include "c_code_generator.h"
#include <sstream>
#include <set>

CCodeGenerator::CCodeGenerator(const DFA& dfa) : minimized_dfa_(dfa) {}

std::string CCodeGenerator::generate() const {
    std::stringstream code;

    code << "#include <stdbool.h>\n";
    code << "#include <stdio.h>\n\n";

    code << "typedef enum {\n";
    for (const auto &state : minimized_dfa_.get_states()) {
        code << "    STATE_" << state.getId() << ",\n";
    }
    code << "} State;\n\n";

    code << "bool recognize(const char *input) {\n";
    code << "    State state = STATE_" << minimized_dfa_.getInitialState().getId() << ";\n\n";
    code << "    while (*input) {\n";
    code << "        switch (state) {\n";

    for (const auto &state : minimized_dfa_.get_states()) {
        code << "            case STATE_" << state.getId() << ":\n";
        for (char symbol : get_alphabet(minimized_dfa_)) {
            State target_state = minimized_dfa_.get_target_state(state, symbol);
            if (target_state.getId() != State::INVALID.getId()) {
                code << "                if (*input == '" << symbol << "') state = STATE_" << target_state.getId() << ";\n";
            }
        }
        code << "                break;\n";
    }

    code << "        }\n";
    code << "        ++input;\n";
    code << "    }\n\n";

    code << "    return ";
    bool first_final_state = true;
    for (const auto &state : minimized_dfa_.get_states()) {
        if (state.isFinal()) {
            if (!first_final_state) {
                code << " || ";
            }
            first_final_state = false;
            code << "state == STATE_" << state.getId();
        }
    }
    code << ";\n";
    code << "}\n\n";

    code << "int main() {\n";
    code << "    char input[1024];\n";
    code << "    printf(\"Enter input string: \");\n";
    code << "    scanf(\"%1023s\", input);\n\n";
    code << "    if (recognize(input)) {\n";
    code << "        printf(\"Input is recognized by the DFA.\\n\");\n";
    code << "    } else {\n";
    code << "        printf(\"Input is not recognized by the DFA.\\n\");\n";
    code << "    }\n\n";
    code << "    return 0;\n";
    code << "}\n";

    return code.str();
}

std::set<char> CCodeGenerator::get_alphabet(const DFA &dfa) const {
    std::set<char> alphabet;
    for (const auto & transition_entry : dfa.get_transitions()) {
        for (const auto &symbol_entry : transition_entry.second) {
            alphabet.insert(symbol_entry.first);
        }
    }
    return alphabet;
}



