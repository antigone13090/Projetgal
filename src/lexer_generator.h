#ifndef LEXER_GENERATOR_H
#define LEXER_GENERATOR_H

#include "dfa.h"

void generate_lexer_code(DFA dfa_minimal, const char *output_filename);

#endif
