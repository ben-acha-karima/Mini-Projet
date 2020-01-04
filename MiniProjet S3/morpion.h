#ifndef MORPION_H_INCLUDED
#define MORPION_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <sdl_image.h>

class GrilleMorpion
{
    public:
    GrilleMorpion();//constructeur
    void clear();//vide la grille
    void afficher(SDL_Surface *ecran);//affiche la grille
    void coupRandom(int joueur);//joue un coup aleatoire
    void coupSemiRandom(int joueur);//joue un coup aléatoire avec une préférence pour le centre et les coins
    bool coupMalin(int joueur);//joue un coup un peu malin
    bool coupSpecial(int premierCoup,int joueur);//joue un coup avec la meilleure IA possible (enfin, je crois...)
    int testGagnant();//teste le gagnant (ou l'absence de gagnant)
    bool jouerCoup(int caseChoisie,int joueur,bool humain);//joue un coup, si la case choisie est vide
    int changerCase(int caseChoisie);//change la case choisie en fonction des controles en cours
    GrilleMorpion tourneGrille(int *premierCoup,int rotation);//renvoie la grille après rotation de 90*rotation°,permet de varier le jeu de l'IA
    private:
    int m_grille[9];//la grille
    SDL_Surface *images[3];//les 3 images du jeu
    bool m_oxo;//true si O commence, false si X commence
};

void morpionHvsH(SDL_Surface *ecran);//demarre une partie 1vs1
void morpionIA(SDL_Surface *ecran,int niveau);//demarre une partie homme vs IA
int choixCase(int joueur);//demande au joueur de choisir une case
GrilleMorpion coupIa(GrilleMorpion laGrille,int niveau,int premierCoup,int joueur,int rotation);//fait jouer un coup à l'IA
void options();//configure les options TODO
SDL_Rect positionnerCoup(int h,int l);
#endif // MORPION_H_INCLUDED
