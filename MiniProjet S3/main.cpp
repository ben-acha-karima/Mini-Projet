#include "morpion.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Surface *ecran(0),*menu2(0),*menu1(0);
    SDL_Event event;
    SDL_Rect pos;
    menu1=IMG_Load("menu1.bmp");
    menu2=IMG_Load("menu2.bmp");
    int menu(1),niveau;
    bool continuer(true);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("icone.png"),0);
    ecran=SDL_SetVideoMode(552,541,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Morpion",0);
    pos.x=0;
    pos.y=0;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=false;
            break;
        case SDL_MOUSEBUTTONUP:
            switch(menu)
            {
            case 1:
                if(event.button.x>70&&event.button.x<210)
                {
                    if(event.button.y>100&&event.button.y<220)
                    {
                        morpionHvsH(ecran);
                    }
                    else if(event.button.y>320&&event.button.y<440)
                    {
                        //Lancer les options
                    }
                }
                else if(event.button.x>340&&event.button.x<480)
                {
                    if(event.button.y>100&&event.button.y<220)
                    {
                        menu=2;
                    }
                    else if(event.button.y>320&&event.button.y<440)
                    {
                        exit(0);
                    }
                }
                break;
            case 2:
                if(event.button.x>70&&event.button.x<210)
                {
                    if(event.button.y>100&&event.button.y<220)
                    {
                        niveau=1;
                    }
                    else if(event.button.y>320&&event.button.y<440)
                    {
                        niveau=3;
                    }
                    else
                    {
                        niveau=0;
                    }
                }
                else if(event.button.x>340&&event.button.x<480)
                {
                    if(event.button.y>100&&event.button.y<220)
                    {
                        niveau=2;
                    }
                    else if(event.button.y>320&&event.button.y<440)
                    {
                        niveau=4;
                    }
                    else
                    {
                        niveau=0;
                    }
                }
                else
                {
                    niveau=0;
                }
                if(niveau)
                {
                    morpionIA(ecran,niveau);
                }
                break;
            }
        default:
            break;
        }
        SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));
        switch(menu)
        {
        case 1:
            SDL_BlitSurface(menu1,0,ecran,&pos);
            break;
        case 2:
            SDL_BlitSurface(menu2,0,ecran,&pos);
            break;
        }

        SDL_Flip(ecran);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
