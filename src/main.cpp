#include <iostream>
#include <fstream>
#include "nfa.h"
#include "dfa.h"
#include "regex_parser.h"
#include "nfa_to_dfa.h"
#include "dfa_minimization.h"
#include "c_code_generator.h"
#include "graphviz_export.h"





int main() {
    RegexParser parser;
    GraphvizExport graphviz_exporter;
    
    // Lire l'expression r�guli�re � partir d'un fichier d'entr�e
    std::string regex;
    std::ifstream input_file("input.txt");
    if (input_file.is_open()) {
        std::getline(input_file, regex);
        input_file.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier d'entr�e.\n";
        return 1;
    }

    // Utilisez la classe RegexParser pour cr�er le NFA
    NFA nfa = parser.parse(regex);
    
    // Utilisez la classe NFAToDFA pour convertir le NFA en DFA
    NFAToDFA converter(nfa);
    DFA dfa = converter.convert();
    
    // Utilisez la classe DFAMinimization pour minimiser le DFA
    DFAMinimization minimizer;
    DFA minimized_dfa = minimizer.minimize(dfa);

    // Utilisez la classe CCodeGenerator pour g�n�rer le code C de l'analyseur lexical
    CCodeGenerator code_generator(minimized_dfa);
    std::string c_code = code_generator.generate();
    std::ofstream output_c_code("generated_lexical_analyzer.c");
    if (output_c_code.is_open()) {
        output_c_code << c_code;
        output_c_code.close();
    } else {
        std::cerr << "Erreur lors de l'�criture du fichier de code C g�n�r�.\n";
        return 1;
    }

    // Utilisez la classe GraphvizExport pour exporter T, N, D et D0 au format DOT
    std::string ast_dot = graphviz_exporter.export_ast(parser.get_ast());
    std::string nfa_dot = graphviz_exporter.export_nfa(nfa);
    std::string dfa_dot = graphviz_exporter.export_dfa(dfa);
    std::string minimized_dfa_dot = graphviz_exporter.export_dfa(minimized_dfa);

    // G�n�rer des repr�sentations graphiques avec Graphviz
    // Ici, vous pouvez �crire les repr�sentations DOT dans des fichiers et les convertir en images en utilisant Graphviz
    // ...
    
    return 0;
}


