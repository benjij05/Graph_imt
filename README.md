# Graph_imt

Ce projet a pour but de créer un grapheur en langage C permettant à l'utilisateur :
- d'entrer une fonction mathématique sous forme textuelle,
- de définir les bornes d'affichage (xmin, xmax),
- et de visualiser graphiquement la courbe correspondante dans un repère orthonormé.

Fonctionnalités :
- Lecture d'une fonction depuis le terminal (ex : sin(x), x^2 + 3*x - 5)
- Choix des bornes du repère pour l’affichage (zoom possible)
- Calcul des points de la fonction sur un intervalle discret
- Affichage graphique de la courbe sur une fenêtre SDL
- Gestion des erreurs : 2 virgules, fonction inconnue, etc.

## Structure du projet
- main.c
- gestiongraphique.c/.h
- lexical/
- syntax/
- evaluation/

### Développeurs syntax : Benjamin JACQUOT - Arthur KINDELBERGER
développeurs :

### Développeurs lexical : Jean TRELCAT - Nicolai DROBYSHEVSKI

### Développeurs evaluation : Mathias KALISZ PEREIRA

### Développeurs graphics : Léandre BONTINCK BOUCQUEY - Lucien PETIT MALTAVERNE - Rémi BERNARD

## Compilation
### Sous Windows
gcc main.c syntax/syntax.c gestionGraphique.c evaluation/evaluateur.c lexical/lexical.c -o main -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
### Sous Linux
gcc main.c syntax/syntax.c gestionGraphique.c evaluation/evaluateur.c lexical/lexical.c -o main  -Iinclude $(sdl2-config --cflags --libs) -lSDL2_ttf -lm

## Execution
./main

## Exemple d'entrée
sin(5.56*x+cos(x/2))