#include <stdio.h>
#include <stdlib.h>
#include "entete.h"

void initialisation(tic * t)
{
    int i;
    for(i=0;i<9;i++)
       t-> tabsuivi[i]=0;
    t->image1=IMG_Load("fond1.png");
    t->image2=IMG_Load("khomsa.png");
    t->image3=IMG_Load("head.png");
    t->joueur=1;
    t->tour=0;
    t->comic=TTF_OpenFont("comic.ttf",40);
    t->couleur.r=0;
    t->couleur.g=0;
    t->couleur.b=0;
  t->posMSG.x=660;
    t->posMSG.y=180;
}

void affichage(tic t,SDL_Surface *ecran ) 
{
    int i;

    SDL_BlitSurface(t.image1,NULL,ecran,NULL);
    for(i=0;i<9;i++)
   {
		t.pos.x=190*(i%3); //calculer la position d'affichgage de chaque petit carreau exemple
		t.pos.y=190*(i/3);
        	switch(t.tabsuivi[i])// selon 
        	{
            		case -1:
                		SDL_BlitSurface(t.image2,NULL,ecran,&t.pos);	
            		break;
            		case 1:
                		SDL_BlitSurface(t.image3,NULL,ecran,&t.pos);
            		break;
        	}
	
    }
    
}
//////////////////////////////////////////////////////////////////////////////////////////////

 

void Resultat (tic t,SDL_Surface* ecran)
{
SDL_Rect pos;
char msg[20];

    SDL_FillRect(ecran,0,SDL_MapRGB(ecran->format,255,255,255));
    pos.x=0;
    pos.y=0;
affichage(t,ecran);
    switch(atilganer(t.tabsuivi))
    {
        case 0:
            strcpy(msg, "Better luck next time !");
        break;
        case 1:
            strcpy(msg, "Better luck next time !");
        break;
        case -1:
  
            strcpy(msg,"Congratulations you win !");
    }

 SDL_BlitSurface(TTF_RenderText_Solid(t.comic,msg,t.couleur),NULL,ecran,&t.posMSG);
 SDL_Flip(ecran);
    SDL_Delay(4028);
    
}

void liberationmemoire(tic t)
{
    SDL_FreeSurface(t.image1);
    SDL_FreeSurface(t.image2);
    SDL_FreeSurface(t.image3);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int atilganer(int tabsuivi[])
{
//remplir cette matrice avec les combinaisons de succÃ©s
    int lignes_gagnantes[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i=0;i<8;++i)
        if(tabsuivi[lignes_gagnantes[i][0]]!=0&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][1]]&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][2]])
                return tabsuivi[lignes_gagnantes[i][2]];
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int minimax(int tabsuivi[],int joueur)
{
    int gagnant=atilganer(tabsuivi);
    if(gagnant!=0)
        return gagnant*joueur;
    int coup=-1;
    int score=-2;
    int i;
    for(i=0;i<9;++i)
    {
        if(tabsuivi[i]==0)
        {
            tabsuivi[i]=joueur;
            int mmscore=-minimax(tabsuivi,joueur*-1);
            if(mmscore>score)
            {
                score=mmscore;
                coup=i;
            }
            tabsuivi[i]=0;
        }
    }
    if(coup==-1)
        return 0;
    return score;
}
//////////////////////////////////////////////////////////////////////////////////
void calcul_coup(int tabsuivi[])
{
    int coup=-1;
    int score=-2;
    int i;
    for(i=0;i<9;++i)
    {
        if(tabsuivi[i]==0)
        {
            tabsuivi[i]=1;
            int mmscore=-minimax(tabsuivi,-1);
            tabsuivi[i]=0;
            if(mmscore>score)
            {
                score=mmscore;
                coup=i;
            }
        }
    }
    tabsuivi[coup]=1;
}
/////////////////////////////////////////////////////////////////////////////////
int jouer(SDL_Surface * screen)
{
tic t; int coup;
TTF_Init();
SDL_Event event;
    int continuer=1;

    int joueur; 
    initialisation(&t);
    int a,b;
    while(continuer)
    {
affichage(t,screen); 
SDL_Flip(screen);
if( t.tour<9 &&atilganer(t.tabsuivi)==0)
{if((t.tour+joueur)%2==0)//tour du PC
            {calcul_coup(t.tabsuivi);
 t.tour++;}
        else
        {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;
            break;
        case SDL_MOUSEBUTTONUP:
            a=event.button.x/190;
            b=event.button.y/190;
            coup=3*b+a;
            t.tour++;
            break;
        }

    t.tabsuivi[coup]=-1;
}

}
else
{ Resultat(t,screen);
 continuer=0;   
printf("%d", t.tour);
}
}
   SDL_Quit();
   TTF_Quit();
    liberationmemoire(t);
    return 0;
}

