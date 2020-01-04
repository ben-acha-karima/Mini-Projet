#include "morpion.h"

using namespace std;
void morpionIA(SDL_Surface *ecran,int niveau)
{
    GrilleMorpion laGrille;
    int gagnant,caseChoisie,premierCoup(0),numeroOrdi(1),rotation;
    bool recommencer(true),continuer(true),premierCoupHumainJoue(false),premierCoupOrdiJoue(false);
    string recom;
    rotation=rand()%4;
    switch(rotation)
    {
    case 1:
        premierCoup=2;
        break;
    case 2:
        premierCoup=8;
        break;
    case 3:
        premierCoup=6;
        break;
    }
    numeroOrdi=1;
    while(recommencer)
    {
        continuer=true;
        if(numeroOrdi==2||premierCoupOrdiJoue)
        {
            laGrille.afficher(ecran);
            do
            {
                caseChoisie=choixCase(1);
            }
            while(!laGrille.jouerCoup(caseChoisie,3-numeroOrdi,true));
            if(!premierCoupHumainJoue)
            {
                premierCoupHumainJoue=true;
                premierCoup=caseChoisie;
            }
            gagnant=laGrille.testGagnant();
            if(gagnant)
            {
                numeroOrdi=3-numeroOrdi;
                laGrille.afficher(ecran);
                if(gagnant==3)
                {

                }
                else
                {
                    if(niveau==4)
                    {
                        TTF_Init();
                        TTF_Font *comic;
                        comic=TTF_OpenFont("comic.ttf",40);
                        SDL_Color a={0,0,0};
                        SDL_Rect pos;
                        SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));
                        pos.x=30;
                        pos.y=150;
                        SDL_BlitSurface(TTF_RenderText_Solid(comic,"Vous avez gagné contre le ",a),0,ecran,&pos);
                        pos.x=0;
                        pos.y=200;
                        SDL_BlitSurface(TTF_RenderText_Solid(comic,"niveau 4,c'est un bug, veuillez",a),0,ecran,&pos);
                        pos.x=20;
                        pos.y=350;
                        SDL_BlitSurface(TTF_RenderText_Solid(comic,"en informer le développeur!",a),0,ecran,&pos);
                        SDL_Flip(ecran);
                        SDL_Delay(4028);
                        TTF_Quit();
                    }
                }
                laGrille.clear();

                continuer=false;
                premierCoupHumainJoue=false;
                premierCoupOrdiJoue=false;
                rotation=rand()%4;
                switch(rotation)
                {
                case 0:
                    premierCoup=0;
                    break;
                case 1:
                    premierCoup=2;
                    break;
                case 2:
                    premierCoup=8;
                    break;
                case 3:
                    premierCoup=6;
                    break;
                }
                if(recom=="n"||recom=="N"||recom=="non"||recom=="Non"||recom=="NON")
                {
                    recommencer=false;
                }
            }
        }
        if(continuer)
        {
            laGrille=coupIa(laGrille,niveau,premierCoup,numeroOrdi,rotation);
            if(!premierCoupOrdiJoue)
            {
                premierCoupOrdiJoue=true;
            }
        }
        gagnant=laGrille.testGagnant();
        if(gagnant)
        {
            numeroOrdi=3-numeroOrdi;
            laGrille.afficher(ecran);
            if(gagnant==3)
            {

            }
            else
            {

            }
            laGrille.clear();
            premierCoupOrdiJoue=false;
            premierCoupHumainJoue=false;
            rotation=rand()%4;
            switch(rotation)
            {
            case 0:
                premierCoup=0;
                break;
            case 1:
                premierCoup=2;
                break;
            case 2:
                premierCoup=8;
                break;
            case 3:
                premierCoup=6;
                break;
            }
            if(recom=="n"||recom=="N"||recom=="non"||recom=="Non"||recom=="NON")
            {
                recommencer=false;
            }
        }
    }
}

GrilleMorpion GrilleMorpion::tourneGrille(int *premierCoup,int rotation)
{
    GrilleMorpion retour(*this);
    bool coupPasse(false);
    int i,j;
    switch(rotation)
    {
    case 1:
        for(i=0; i<=2; i++)
        {
            for(j=0; j<=2; j++)
            {
                if(*premierCoup==3*j+2-i&&!coupPasse)
                {
                    *premierCoup=3*i+j;
                    coupPasse=true;
                }
                retour.m_grille[3*i+j]=m_grille[3*j+2-i];
            }
        }
        break;
    case 2:
        *premierCoup=8-*premierCoup;
        for(i=0; i<=8; i++)
        {
            retour.m_grille[i]=m_grille[8-i];
        }
        break;
    case 3:
        for(i=0; i<=2; i++)
        {
            for(j=0; j<=2; j++)
            {
                if(*premierCoup==6-(3*j-i)&&!coupPasse)
                {
                    *premierCoup=3*i+j;
                    coupPasse=true;
                }
                retour.m_grille[3*i+j]=m_grille[6-(3*j-i)];
            }
        }
        break;
    }
    return retour;
}

bool GrilleMorpion::coupSpecial(int premierCoup,int joueur)
{
    int coupAJouer[3];
    int i;
    switch(premierCoup+9*joueur)
    {
    case 9:
        coupAJouer[0]=0;
        coupAJouer[1]=0;
        coupAJouer[2]=0;
        break;
    case 10:
        coupAJouer[0]=4;
        coupAJouer[1]=6;
        coupAJouer[2]=6;
        break;
    case 11:
        coupAJouer[0]=8;
        coupAJouer[1]=8;
        coupAJouer[2]=8;
        break;
    case 12:
        coupAJouer[0]=4;
        coupAJouer[1]=2;
        coupAJouer[2]=2;
        break;
    case 13:
        coupAJouer[0]=8;
        coupAJouer[1]=8;
        coupAJouer[2]=8;
        break;
    case 14:
        coupAJouer[0]=4;
        coupAJouer[1]=4;
        coupAJouer[2]=4;
        break;
    case 15:
        coupAJouer[0]=8;
        coupAJouer[1]=8;
        coupAJouer[2]=8;
        break;
    case 16:
        coupAJouer[0]=4;
        coupAJouer[1]=4;
        coupAJouer[2]=4;
        break;
    case 17:
        coupAJouer[0]=2;
        coupAJouer[1]=6;
        coupAJouer[2]=6;
        break;
    case 18:
        coupAJouer[0]=4;
        coupAJouer[1]=8;
        coupAJouer[2]=1;
        break;
    case 19:
        coupAJouer[0]=4;
        coupAJouer[1]=2;
        coupAJouer[2]=2;
        break;
    case 20:
        coupAJouer[0]=4;
        coupAJouer[1]=6;
        coupAJouer[2]=1;
        break;
    case 21:
        coupAJouer[0]=4;
        coupAJouer[1]=6;
        coupAJouer[2]=6;
        break;
    case 22:
        coupAJouer[0]=0;
        coupAJouer[1]=8;
        coupAJouer[2]=2;
        break;
    case 23:
        coupAJouer[0]=4;
        coupAJouer[1]=2;
        coupAJouer[2]=2;
        break;
    case 24:
        coupAJouer[0]=4;
        coupAJouer[1]=2;
        coupAJouer[2]=1;
        break;
    case 25:
        coupAJouer[0]=4;
        coupAJouer[1]=6;
        coupAJouer[2]=6;
        break;
    case 26:
        coupAJouer[0]=4;
        coupAJouer[1]=0;
        coupAJouer[2]=1;
        break;
    }
    for(i=0; i<=2; i++)
    {
        if(jouerCoup(coupAJouer[i],joueur,false))
        {
            return true;
        }
    }
    return false;
}

void GrilleMorpion::coupSemiRandom(int joueur)
{
    int caseChoisie;
    do
    {
        caseChoisie=rand()%4;
        if(caseChoisie>0)
        {
            caseChoisie=(rand()%5)*2;
        }
        else
        {
            caseChoisie=(rand()%4)*2+1;
        }
    }
    while(!jouerCoup(caseChoisie,joueur,false));
}

GrilleMorpion coupIa(GrilleMorpion laGrille,int niveau,int premierCoup,int joueur,int rotation)
{

    laGrille=laGrille.tourneGrille(&premierCoup,rotation);
    switch(niveau)
    {
    case 1:
        laGrille.coupRandom(joueur);
        break;
    case 2:
        if(!laGrille.coupMalin(joueur))
        {
            laGrille.coupRandom(joueur);
        }
        break;
    case 3:
        if(!laGrille.coupMalin(joueur))
        {
            laGrille.coupSemiRandom(joueur);
        }
        break;
    case 4:
        if(!laGrille.coupMalin(joueur))
        {
            if(!laGrille.coupSpecial(premierCoup,joueur))
            {
                laGrille.coupRandom(joueur);
            }
        }
    }
    laGrille=laGrille.tourneGrille(&premierCoup,4-rotation);
    return laGrille;
}

bool GrilleMorpion::coupMalin(int joueur)
{
    int i;
    GrilleMorpion grilleTest;
    for(i=0; i<=8; i++)
    {
        grilleTest=*this;
        grilleTest.jouerCoup(i,joueur,false);
        if(grilleTest.testGagnant()==joueur)
        {
            jouerCoup(i,joueur,false);
            return true;
        }
    }
    for(i=0; i<=8; i++)
    {
        grilleTest=*this;
        grilleTest.jouerCoup(i,3-joueur,false);
        if(grilleTest.testGagnant()==3-joueur)
        {
            jouerCoup(i,joueur,false);
            return true;
        }
    }
    return false;
}

void GrilleMorpion::coupRandom(int joueur)
{
    int caseChoisie;
    do
    {
        caseChoisie=rand()%9;
    }
    while(!jouerCoup(caseChoisie,joueur,false));
}

void morpionHvsH(SDL_Surface *ecran)
{
    GrilleMorpion laGrille;
    int gagnant,caseChoisie,joueur(2);
    bool recommencer(true);
    while(recommencer)
    {
        laGrille.afficher(ecran);
        joueur=3-joueur;
        do
        {
            caseChoisie=choixCase(joueur);
        }
        while(!laGrille.jouerCoup(caseChoisie,joueur,true));
        gagnant=laGrille.testGagnant();
        if(gagnant)
        {
            laGrille.afficher(ecran);
            if(gagnant==3)
            {
                recommencer=false;
            }
            else
            {
                recommencer=false;
            }
            laGrille.clear();
        }
    }
}

int choixCase(int joueur)
{
    SDL_Event event;
    bool continuer(true);
    int choix,a,b;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONUP:
            a=event.button.x/190;
            b=event.button.y/190;
            choix=3*a+b;
            continuer=false;
            break;
        default:
            break;
        }
    }
    return choix;
}

bool GrilleMorpion::jouerCoup(int caseChoisie,int joueur,bool humain)
{
    if(m_grille[caseChoisie]==0)
    {
        m_grille[caseChoisie]=joueur;
        return true;
    }
    else
    {
        return false;
    }
}

GrilleMorpion::GrilleMorpion()
{
    int i;
    for(i=0; i<=8; i++)
    {
        m_grille[i]=0;
    }
    ifstream flux("options.opt");
    if(flux)
    {
        int i,j,k;
        m_oxo=true;
        string vide;
        flux>>i>>j>>k>>k;
        if(k==2)
        {
            m_oxo=false;
        }
    }
    else
    {
        m_oxo=true;
    }
    images[0]=SDL_LoadBMP("fond.bmp");
    images[1]=SDL_LoadBMP("rond.bmp");
    images[2]=SDL_LoadBMP("croix.bmp");
}

void GrilleMorpion::clear()
{
    int i;
    for(i=0; i<=8; i++)
    {
        m_grille[i]=0;
    }
}

void GrilleMorpion::afficher(SDL_Surface *ecran)
{
    int ligne,colonne;
    SDL_Rect pos;
    pos=positionnerCoup(0,0);
    SDL_FillRect(ecran,&pos,SDL_MapRGB(ecran->format,255,255,255));
    SDL_BlitSurface(images[0],0,ecran,&pos);
    for(ligne=0; ligne<3; ligne++)
    {
        for(colonne=0; colonne<3; colonne++)
        {
            pos=positionnerCoup(ligne,colonne);
            switch(m_grille[3*ligne+colonne])
            {
            case 1:
                SDL_BlitSurface(images[1],0,ecran,&pos);
                break;
            case 2:
                SDL_BlitSurface(images[2],0,ecran,&pos);
                break;
            }
        }
    }
    SDL_Flip(ecran);
}

int GrilleMorpion::testGagnant()
{
    bool matchNul(true);
    int ligne,premiereCase,i;
    for(ligne=0; ligne<3; ligne++)
    {
        premiereCase=m_grille[ligne];
        if(premiereCase)
        {
            if(m_grille[ligne+3]==m_grille[ligne+6])
            {
                if(premiereCase==m_grille[ligne+3])
                {
                    return premiereCase;
                }
            }
        }
    }
    for(ligne=0; ligne<9; ligne+=3)
    {
        premiereCase=m_grille[ligne];
        if(premiereCase)
        {
            if(m_grille[ligne+1]==m_grille[ligne+2])
            {
                if(premiereCase==m_grille[ligne+1])
                {
                    return premiereCase;
                }
            }
        }
    }
    if(m_grille[0]==m_grille[4])
    {
        if(m_grille[0]==m_grille[8])
        {
            return m_grille[0];
        }
    }
    if(m_grille[2]==m_grille[4])
    {
        if(m_grille[2]==m_grille[6])
        {
            return m_grille[2];
        }
    }
    for(i=0; i<9; i++)
    {
        if(!m_grille[i])
        {
            matchNul=false;
        }
    }
    if(matchNul)
    {
        return 3;
    }
    return 0;
}

SDL_Rect positionnerCoup(int h,int l)
{
    SDL_Rect retour;
    retour.x=190*h;
    retour.y=190*l;
    return retour;
}
