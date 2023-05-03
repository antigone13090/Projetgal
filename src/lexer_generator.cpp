#include <stdio.h>
#include "lexer_generator.h"

void generate_lexer_code(DFA dfa_minimal, const char *output_filename) {
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        printf("Erreur lors de la création du fichier %s\n", output_filename);
        return;
    }

    // Écrire le code C pour implémenter l'analyseur lexical basé sur le DFA minimal
    // Vous devrez adapter le code ci-dessous en fonction de la représentation de votre DFA

    fprintf(output_file, "#include <stdio.h>\n\n");
    fprintf(output_file, "int main() {\n");
    fprintf(output_file, "    // Écrire le code pour utiliser le DFA minimal\n");
    fprintf(output_file, "    // (états, transitions, etc.) pour analyser une chaîne de caractères donnée\n");
    fprintf(output_file, "    return 0;\n");
    fprintf(output_file, "}\n");

    fclose(output_file);
}
