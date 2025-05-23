#include "lexical.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void AfficherLexemes(typejeton T[]) {
    int i = 0;
    while (T[i].lexem != FIN) {
        printf("Lexeme %d : ", i);
        switch (T[i].lexem) {
            case REEL:
                printf("REEL (%f)\n", T[i].valeur.reel);
                break;
            case OPERATEUR:
                printf("OPERATEUR ");
                switch (T[i].valeur.operateur) {
                    case PLUS: printf("(+)\n"); break;
                    case MOINS: printf("(-)\n"); break;
                    case FOIS: printf("(*)\n"); break;
                    case DIV: printf("(/)\n"); break;
                    case PUIS: printf("(^)\n"); break;
                }
                break;
            case VARIABLE:
                printf("VARIABLE (x)\n");
                break;
            case FONCTION:
                printf("FONCTION ");
                switch (T[i].valeur.fonction) {
                    case SIN: printf("(SIN)\n"); break;
                    case COS: printf("(COS)\n"); break;
                    case TAN: printf("(TAN)\n"); break;
                    case LOG: printf("(LOG)\n"); break;
                    case SQRT: printf("(SQRT)\n"); break;
                    case EXP: printf("(EXP)\n"); break;
                    case ABS: printf("(ABS)\n"); break;
                }
                break;
            case PAR_OUV:
                printf("PAR_OUV (()\n");
                break;
            case PAR_FERM:
                printf("PAR_FERM ())\n");
                break;
            case ERREUR:
                printf("ERREUR ");
                switch (T[i].valeur.erreur) {
                    case 0:
                    printf("Caractere inconnu\n");
                    break;

                    case 1:
                    printf("Fonction inconnue\n");
                    break;

                    case 2:
                    printf("Nombre mal forme\n");
                    break;    
                }
                break;
            default:
                printf("Autre\n");
        }
        i++;
    }
}


void AnalyseLex(typejeton T[], char str[]) {
    int i = 0, j = 0;
    
    while (str[i] != '\0') {
        if (isspace(str[i])) { 
            i++;
            continue;
        }

        switch (str[i]) {
            case '(':
                T[j].lexem = PAR_OUV;
                break;
            case ')':
                T[j].lexem = PAR_FERM;
                break;
            case '+':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = PLUS;
                break;
            case '-':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = MOINS;
                break;
            case '*':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = FOIS;
                break;
            case '/':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = DIV;
                break;
            case '^':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = PUIS;
                break;
            case 'x':
            case 'X':
                T[j].lexem = VARIABLE;
                break;
                default:
    if (isdigit(str[i]) || str[i] == '.') {
        int start = i;
        int pointCount = 0;

        while (isdigit(str[i]) || str[i] == '.') {
            if (str[i] == '.') pointCount++;
            i++;
        }

        if (pointCount > 1) {
            T[j].lexem = ERREUR;
            T[j].valeur.erreur = erreur102; // Nombre mal formé
        } else {
            char buffer[32];
            int len = i - start;
            strncpy(buffer, &str[start], len);
            buffer[len] = '\0';
            T[j].lexem = REEL;
            T[j].valeur.reel = strtof(buffer, NULL);
        }

        j++;
        continue;
            }
                if (isalpha(str[i])) {
                    char buffer[10];
                    int k = 0;
                    while (isalpha(str[i]) && k < 9) { 
                        buffer[k++] = str[i++];
                    }
                    buffer[k] = '\0';
                    
                    if ((strcmp(buffer, "SIN")) == 0|(strcmp(buffer, "sin"))== 0){
                        T[j].lexem = FONCTION;
                        T[j].valeur.fonction = SIN;
                    }
                    else if (strcmp(buffer, "COS") == 0|(strcmp(buffer, "cos"))== 0){
                        T[j].lexem = FONCTION;
                        T[j].valeur.fonction = COS;
                    }
                    else if (strcmp(buffer, "TAN") == 0|(strcmp(buffer, "tan"))== 0){
                        T[j].lexem = FONCTION;
                        T[j].valeur.fonction = TAN;
                    }
                    else if (strcmp(buffer, "EXP") == 0|(strcmp(buffer, "exp"))== 0){
                        T[j].lexem = FONCTION;
                        T[j].valeur.fonction = EXP;
                    }
                    else if (strcmp(buffer, "LOG") == 0|(strcmp(buffer, "log"))== 0){
                        T[j].lexem = FONCTION;
                        T[j].valeur.fonction = LOG;
                    }
                    else if (strcmp(buffer, "SQRT") == 0|(strcmp(buffer, "sqrt"))== 0){
                        T[j].lexem = FONCTION;
                        T[j].valeur.fonction = SQRT;
                    }
                    else if (strcmp(buffer, "ABS") == 0|(strcmp(buffer, "abs"))== 0){
                        T[j].lexem = FONCTION;
                        T[j].valeur.fonction = ABS;
                    }
                    else {
                        T[j].lexem = ERREUR;
                        T[j].valeur.erreur = erreur101;
                    }
                    j++;
                    continue;
                }
                
                T[j].lexem = ERREUR;
                T[j].valeur.erreur = erreur100;
        }
        i++;
        j++;
    }

    T[j].lexem = FIN; 
}
