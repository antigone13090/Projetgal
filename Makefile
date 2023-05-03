# Project: Project1
# Makefile created by Dev-C++ 5.11

CC      = g++
OBJ     = main_project.o src/ast.o src/dfa.o src/lexer_generator.o src/main.o src/nfa.o src/regex_parser.o src/state.o src/nfa_to_dfa.o src/dfa_minimization.o src/c_code_generator.o src/graphviz_export.o
LINKOBJ = $(OBJ)
BIN     = Projet1.exe
CXXFLAGS = -std=c++11
RM      = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN)

main_project.o: main_project.cpp
	$(CC) -c main_project.cpp -o main_project.o $(CXXFLAGS)

src/ast.o: src/ast.cpp
	$(CC) -c src/ast.cpp -o src/ast.o $(CXXFLAGS)

src/dfa.o: src/dfa.cpp
	$(CC) -c src/dfa.cpp -o src/dfa.o $(CXXFLAGS)

src/lexer_generator.o: src/lexer_generator.c
	$(CC) -c src/lexer_generator.c -o src/lexer_generator.o $(CXXFLAGS)

src/main.o: src/main.cpp
	$(CC) -c src/main.cpp -o src/main.o $(CXXFLAGS)

src/nfa.o: src/nfa.cpp
	$(CC) -c src/nfa.cpp -o src/nfa.o $(CXXFLAGS)

src/regex_parser.o: src/regex_parser.cpp
	$(CC) -c src/regex_parser.cpp -o src/regex_parser.o $(CXXFLAGS)

src/state.o: src/state.cpp
	$(CC) -c src/state.cpp -o src/state.o $(CXXFLAGS)

src/nfa_to_dfa.o: src/nfa_to_dfa.cpp
	$(CC) -c src/nfa_to_dfa.cpp -o src/nfa_to_dfa.o $(CXXFLAGS)

src/dfa_minimization.o: src/dfa_minimization.cpp
	$(CC) -c src/dfa_minimization.cpp -o src/dfa_minimization.o $(CXXFLAGS)

src/c_code_generator.o: src/c_code_generator.cpp
	$(CC) -c src/c_code_generator.cpp -o src/c_code_generator.o $(CXXFLAGS)

src/graphviz_export.o: src/graphviz_export.cpp
	$(CC) -c src/graphviz_export.cpp -o src/graphviz_export.o $(CXXFLAGS)

