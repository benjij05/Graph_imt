#include "../gestionGraphique.h"
#include "../lexical/lexical.h"
#include <stdio.h>
#include <string.h>

#define SIZEX 30
#define SIZEY 14
#define PAS 30

// use (Windows) "gcc test/lexical_test.c lexical/lexical.c gestionGraphique.c -o main -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf" to test
// use (Linux) "gcc test/lexical_test.c lexical/lexical.c gestionGraphique.c -o main  -Iinclude $(sdl2-config --cflags --libs) -lSDL2_ttf"  to test


void RelancerProgramme();
int ContientErreur(typejeton T[],SDL_Renderer *ren,SDL_Color red,TTF_Font *font2);
    int i = 0;

int main(int argc, char *argv[]) {
    RelancerProgramme();
    return 0;
}

void RelancerProgramme() {
    float scale = 0.25;
    char entry_f[256] = ""; 
    int compteur = 0;

    initSDL();
    initTTF();
    SDL_Window *win = createWindow("Grapheur", 1100, 700);
    SDL_Renderer *ren = createRenderer(win);
    SDL_Texture *background = loadTexture("graphimt_testlexical.bmp", ren);
    TTF_Font *font2 = createFont("DejaVuSans.ttf", 30);
    SDL_Color black = {0, 0, 0};
    SDL_Color red = {255, 0, 0};
    SDL_Event evt;
    int programrunning = 1;

    SDL_StartTextInput();
    SDL_Rect textZone = {30, 600, 1040, 60};
    typejeton T[50];

    while (programrunning) {
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                programrunning = 0;
            } else if (evt.type == SDL_TEXTINPUT) {
                if (compteur < sizeof(entry_f) - 2) { 
                    strcat(entry_f, evt.text.text);
                    compteur += strlen(evt.text.text);
                }
            } else if (evt.type == SDL_KEYDOWN) {
                if (evt.key.keysym.sym == SDLK_BACKSPACE && compteur > 0) {
                    entry_f[--compteur] = '\0';
                } else if (evt.key.keysym.sym == SDLK_RETURN) {
                    AnalyseLex(T, entry_f);
                    AfficherLexemes(T);
                    SDL_StopTextInput();
                    if (ContientErreur(T,ren,red,font2) == 0) {
                        // Sortie en cas de succès continuer la partie syntaxique ici
                        break; 
                    }
                    printText(40, 630, "veuillez reessayer", 400, 30, font2, red, ren);
                    updateDisplay(ren);
                    SDL_Delay(2000);
                    memset(entry_f, 0, sizeof(entry_f)); 
                    compteur = 0;
                }
            }
        }

        renderTexture(background, ren, 0, 0, 1100, 700);
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderFillRect(ren, &textZone);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderDrawRect(ren, &textZone);
        printText(125, 73, entry_f, strlen(entry_f) * 15, 30, font2, black, ren);
        updateDisplay(ren);
        SDL_StartTextInput();
    }
    
    
}

int ContientErreur(typejeton T[],SDL_Renderer *ren,SDL_Color red,TTF_Font *font2) {
    int i = 0;
    while (T[i].lexem != FIN) {
        if (T[i].lexem == ERREUR) {
            switch (T[i].valeur.erreur)
            {
            case 0:
            printText(40, 600, "Carractere Inconnu", 400, 30, font2, red, ren);                
            break;
            case 1:
            printText(40, 600, "Fonction Inconnue", 400, 30, font2, red, ren);                
            break;
            case 2:
            printText(40, 600, "Nombre Mal Forme", 400, 30, font2, red, ren);                
            break;
            }
            
            return 1;
        }
        i++;
    }
    return 0;
}