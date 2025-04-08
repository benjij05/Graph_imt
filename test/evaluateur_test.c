// Mathias KALISZ PEREIRA

// use "gcc test/evaluateur_test.c evaluation/evaluateur.c lexical/lexical.c syntax/syntax.c -o main -lm"  to test

#include <stdio.h>
#include <stdlib.h>
#include "../evaluation/evaluateur.h"
#include "../lexical/lexical.h"
#include "../syntax/syntax.h"


int main() {
    char input[256];
    printf("Entrez une expression mathematique : ");
    fgets(input, sizeof(input), stdin);

    // Analyse lexicale
    typejeton T[100];
    AnalyseLex(T, input);

    // Analyse syntaxique
    Node *arbre = analyserSyntaxe(T);
    if (!arbre) {
        fprintf(stderr, "Erreur de syntaxe\n");
        return EXIT_FAILURE;
    }

    // Evaluation simple
    for (double x = -5.0; x <= 5.0; x += 1) {    //a modifier avec les bornes de la partie graphique et leur pas
        double res = evaluate_expression(arbre, x);
        printf("f(%.1f)=%.5f\n", x, res);
    }

    libererArbre(arbre);
    return 0;
}