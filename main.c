#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <ctype.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "Personne.h"
#include "test.h"
#include "enemie.h"
#include "minimap.h"
#include "enigme_IA.h"
#include "enigme.h"//aleatoire sans fichier
#include "menu.h"
#include "option.h"
#include "enig_fichier.h"
#include "sauvegarde.h"
#include "entete.h"
#define mono_joueur 1
#define multijoueur 2
#define new_game 0
#define save_game 3

/** 
* @file main.c 
* @brief tache personne. 
* @author Boussida Mohamed Oussema 
* @version 0.1 
* @date Apr 26, 2022 
* 
* Testing program for perso * 
*/



int main()
{
vie  v;    
minimap m;
enemie e;
Background b;  
Personne p,p1;
SDL_Surface *screen;
SDL_Surface *back;
int continuer=1,up=0;
SDL_Event event;
int acceleration=0;
int deceleration=0;
int up1=0;
int acceleration1=0;
int deceleration1=0;
TTF_Font *police=NULL;
Uint32 t_prev,t_fin , dt ,temps;
SDL_Surface *mask,*mask2;
int resultat_ia,resultat_alea,stage=1,stage1=1;
SDL_Color Color={255,255,255};
enig_fichier en;
int resultat_fichier;
SDL_Surface *sous_menu_1[2],*menu[2];
int mode=new_game;
score sc;
SDL_Init(SDL_INIT_VIDEO);
TTF_Init();
screen=SDL_SetVideoMode (1230,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
initPerso(&p);
initPerso2(&p1);
initBack(&b);
initennemi(&e);
initmap(&m);
initialiser_score(&v);
initialiser_score1(&sc);
back=IMG_Load("stage1.png");
police=TTF_OpenFont("DS-DIGI.TTF",70);
mask=IMG_Load("mask1.png");

init_enig_fichier(&en,Color);
int choix=1;
sous_menu_1[0]=IMG_Load("images/jouer.png");
sous_menu_1[1]=IMG_Load("images/jouer1.png");
int s=0;
menu[0]=IMG_Load("im12.png");
menu[1]=IMG_Load("im11.png");
tic t; int coup;
int joueur; 
    int a,c;
Mix_Music *music;
Mix_Chunk  *music1;
    Mix_AllocateChannels(1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    music1 = Mix_LoadWAV("music/pan.wav");
int hb = 100, //3olw boutton
        lb = 300, //3orth boutton
        bs = 30; 
//////////menu 
    int Menu=-1;

    do
    {
Menu=afficher_menu(screen);
if (Menu==2) afficher_option( screen);

}
while (Menu==2);

if (Menu ==0) return 0;
while (continuer)
{
t_prev = SDL_GetTicks();

while(SDL_PollEvent(&event))
{
    if (mode==new_game)
    {    
music= Mix_LoadMUS("music/action.mp3");

Mix_PlayMusic(music,-1);
        switch (event.type)
      		 {
   		    case SDL_QUIT://pour quitter le program
        	   continuer=0;
          	 break;
       
     		  case SDL_KEYDOWN:
    			   if (event.key.keysym.sym== SDLK_RETURN) 
   			    {                        Mix_PlayChannel(-1, music1, 0);
                        printf("%d",choix);
          		 switch (choix)
        	   {
           			case 0:
				mode=multijoueur;
              		 break;
           			 case 1:
           		     mode=mono_joueur;
          			  break;              
         			  }

         			  SDL_Delay(1000);
          	
    			   }
       else
       choix=(choix+1)%2;//si choix =1 , devient 0 ,,, si choix =0 ,, devient 1
       break;
      
       }

    }   

    if (mode==mono_joueur){

switch (event.type)
{
case SDL_QUIT:
    continuer=0;
    break;

case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    case  SDLK_RIGHT:
        p.direction=0;
        p.vitesse=5;
        break;
case  SDLK_s:
        p.direction=0;
        p.vitesse=12;
        break;
    case  SDLK_LEFT:
        p.direction=1;
        p.vitesse=5;
        break; 
case  SDLK_d:
        p.direction=1;
        p.vitesse=12;
break;
    case SDLK_UP:
        up=1;
        break;  
    case SDLK_p:
        acceleration=1;
    break;
    case SDLK_o:
        deceleration=1;
        break;
    case SDLK_ESCAPE:
    mode=save_game;
    break;    

        
    
    
    }
break;

case SDL_KEYUP:
switch (event.key.keysym.sym)//lbouton appuyé?
    {
    case  SDLK_RIGHT:
              p.vitesse=0;
        break;

    case  SDLK_LEFT:        
        p.vitesse=0;
        break; 
case  SDLK_s:
        p.vitesse=0;
case  SDLK_d:
        p.vitesse=0;
    case SDLK_UP:
        up=0;
        break; 

    case SDLK_p:
        acceleration=0;
    break;

    case SDLK_o:
        deceleration=0;
        break; 


      
    
    }

break;
}

}
    if (mode==multijoueur)
    {
       switch (event.type)
{
case SDL_QUIT:
    continuer=0;
    break;

case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    case  SDLK_RIGHT:
        p.direction=0;
        p.vitesse=5;
        break;

    case  SDLK_LEFT:
        p.direction=1;
        p.vitesse=5;
        break; 
    case SDLK_UP:
        up=1;
        break;  
    case SDLK_p:
        acceleration=1;
    break;
    case SDLK_o:
        deceleration=1;
        break;

        
    case  SDLK_d:
        p1.direction=0;
        p1.vitesse=5;
        break;
    case  SDLK_q:
        p1.direction=1;
        p1.vitesse=5;
        break; 
    case SDLK_z:
        up1=1;
        break;  
    case SDLK_f:
        acceleration1=1;
    break;
    case SDLK_g:
        deceleration1=1;
        break;
case SDLK_ESCAPE:
mode=save_game;
        break;        

    }
break;

case SDL_KEYUP:
switch (event.key.keysym.sym)//lbouton appuyé?
    {
    case  SDLK_RIGHT:
              p.vitesse=0;
        break;

    case  SDLK_LEFT:        
        p.vitesse=0;
        break; 

    case SDLK_UP:
        up=0;
        break; 

    case SDLK_p:
        acceleration=0;
    break;

    case SDLK_o:
        deceleration=0;
        break; 



        case  SDLK_d:
              p1.vitesse=0;
        break;

    case  SDLK_q:        
        p1.vitesse=0;
        break; 

    case SDLK_z:
        up1=0;
        break; 

    case SDLK_f:
        acceleration1=0;
    break;

    case SDLK_g:
        deceleration1=0;
        break;             
    
    }

break;
}
    }
    if (mode==save_game)
			{

				switch (event.type)
      		 {
   		    case SDL_QUIT://pour quitter le program
        	   continuer=0;
          	 break;
       
     		  case SDL_KEYDOWN:
    			   if (event.key.keysym.sym== SDLK_RETURN) 
   			    {
           
          		 switch (choix)
        	   {
           			case 0:
						sauvegarder(p,b);
              		 break;
           			 case 1:
           		     charger(&p,&b);
           			     printf("\nperso %d -- %d\n",p.position.x,p.position.y);
            			printf("\nback %d -- %d\n",b.camera.x,b.camera.y);
          			  break;              
         			  }
         			  SDL_Delay(1000);
					   mode=mono_joueur;
          	
    			   }
       else
       choix=(choix+1)%2;//si choix =1 , devient 0 ,,, si choix =0 ,, devient 1
       break;
      
       }
			}

}

//partie update
if (mode==mono_joueur){

if (acceleration==1) p.acceleration = p.acceleration + 0.005 ;
if (deceleration==1) p.acceleration = p.acceleration - 0.01;

p.acceleration = p.acceleration - 0.001;
if (p.acceleration<0) p.acceleration =0;


SDL_Delay(3);
t_fin=SDL_GetTicks();
dt=t_fin - t_prev ;
switch (p.direction)
{
case 0:
    if (collisionPP_droite(p.position,mask,b.camera)==0){
    scrolling(&b.camera,p.direction,p.dx);
    scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    }
    break;

case 1:
    if (collisionPP_gauche(p.position,mask,b.camera)==0){
    scrolling(&b.camera,p.direction,p.dx);
    scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    }
    break;
}
update_score(&v);
deplacerIA(&e,p.position);
m.pos_joueur=MAJMinimap(p.position,20,b.camera);
animerennemi(&e);
animerPerso(&p);
if (p.up==0 && collisionPP_down(p.position,mask,b.camera)==0)
{
   // p.vitesse_saut+=15;
    p.ground+=15;
}
if (collisionPP_down(p.position,mask,b.camera)==1){
    p.ground=p.position.y;
  //  printf("co\n");
} 


if (up==1) saut(&p);
//printf("%f\n",p.vitesse_saut);
p.position.y = p.position.y   + p.vitesse_saut ;
p.vitesse_saut = p.vitesse_saut + 10 ;
if (p.position.y>=p.ground)
{   
    p.position.y=p.ground;
    p.vitesse_saut=0;
    p.up=0;
}

//jeu puissance quand le perso atteint la fin
if (b.camera.x>b.backgroundImg->w - screen->w)

{switch (stage)
{
case 1:
resultat_ia=quiz1(&en,screen );

    if (resultat_ia==1)
    {

music= Mix_LoadMUS("music/level2.mp3");

Mix_PlayMusic(music,1);

mask=IMG_Load("mask.png");
        initPerso(&p);
        initBack2(&b);

initennemi(&e);
initialiser_score(&v);
initialiser_score1(&sc);
initmap2(&m);

        //continuer=0;
        printf("you winn \n");

        stage=2;
    }else
    {
        printf("you lostt \n");
        continuer=0;
    }
    break;
case 2:
if(stage==2)
{
    resultat_fichier=jouer(screen);
   }
    
break;

}

}


//cas de collision bb
if (collision(e.pos,p.position)==1)
{
    if (v.valeur_vie>0)
{ v.valeur_vie--;
music1 = Mix_LoadWAV("music/death.wav");
Mix_PlayChannel(-1, music1,0);
}	                        
    else if (v.valeur_vie==0)
    {
        resultat_alea=enigme_alea();
        if (resultat_alea==1)
        { music1 = Mix_LoadWAV("music/back.wav");
Mix_PlayChannel(-1, music1,0);
            printf("revived\n");
            p.position.x+=500;
            p.dx=0;
            b.backgroundPos.x+=500;
            v.valeur_vie=100;
        }else
        {
music1 = Mix_LoadWAV("music/lose.wav");
Mix_PlayChannel(-1, music1,0);
            printf("dead\n");
            continuer=0;
        }
        
        
    }
    
}
}
if (mode==multijoueur)
{
    if (acceleration==1) p.acceleration = p.acceleration + 0.005 ;
if (deceleration==1) p.acceleration = p.acceleration - 0.01;

if (acceleration1==1) p1.acceleration = p1.acceleration + 0.005 ;
if (deceleration1==1) p1.acceleration = p1.acceleration - 0.01;

p.acceleration = p.acceleration - 0.001;
if (p.acceleration<0) p.acceleration =0;


p1.acceleration = p1.acceleration - 0.001;
if (p1.acceleration<0) p1.acceleration =0;


SDL_Delay(3);
t_fin=SDL_GetTicks();
dt=t_fin - t_prev ;
switch (p.direction)
{
case 0:
   if (collisionPP_droite(p.position,mask,b.backgroundPos)==0){
    scrolling(&b.backgroundPos,p.direction,p.dx);
    scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    
    }
    break;

case 1:
    if (collisionPP_gauche(p.position,mask,b.backgroundPos)==0){
    scrolling(&b.backgroundPos,p.direction,p.dx);
    scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    
    }
    break;
}


switch (p1.direction)
{
case 0:
    if (collisionPP_droite(p1.position,mask,b.backgroundPos2)==0){
    scrolling(&b.backgroundPos2,p1.direction,p1.dx);
    //scrolling_enemie(&e,p.direction,p.dx);

    deplacerPerso2(&p1,dt);
    }
    break;

case 1:
    if (collisionPP_gauche(p1.position,mask,b.backgroundPos2)==0){
    scrolling(&b.backgroundPos2,p1.direction,p1.dx);
  // scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso2(&p1,dt);
    }
    break;
}

update_score(&v);
//deplacerIA(&e,p.position);
//m.pos_joueur=MAJMinimap(p.position,20,b.backgroundPos);
//animerennemi(&e);
animerPerso(&p);
animerPerso(&p1);

if (p.up==0 && collisionPP_down(p.position,mask,b.backgroundPos)==0)
{
    //p.vitesse_saut+=15;
    p.ground+=15;
}
if (collisionPP_down(p.position,mask,b.backgroundPos)==1){
    p.ground=p.position.y;
  //  printf("co\n");
} 

if (p1.up==0 && collisionPP_down(p1.position,mask,b.backgroundPos2)==0)
{
    //p1.vitesse_saut+=15;
    p1.ground+=15;
}
if (collisionPP_down(p1.position,mask,b.backgroundPos2)==1){
    p1.ground=p1.position.y;
    //printf("co\n");
} 

if (up1==1) saut(&p1);

if (up==1) saut(&p);
//printf("%f\n",p.vitesse_saut);
p.position.y = p.position.y   + p.vitesse_saut ;
p.vitesse_saut = p.vitesse_saut + 10 ;
if (p.position.y>=p.ground)
{   
    p.position.y=p.ground;
    p.vitesse_saut=0;
    p.up=0;
}

p1.position.y = p1.position.y   + p1.vitesse_saut ;
p1.vitesse_saut = p1.vitesse_saut + 10 ;
if (p1.position.y>=p1.ground)
{   
    p1.position.y=p1.ground;
    p1.vitesse_saut=0;
    p1.up=0;
}

if ((b.backgroundPos2.x>b.backgroundImg->w - screen->w)&&(b.backgroundPos.x>b.backgroundImg->w - screen->w))
{switch (stage)
{
case 1:
resultat_ia=quiz1(&en,screen );
    if (resultat_ia==1)
    {
mask=IMG_Load("mask.png");
        initPerso(&p);
        initPerso2(&p1);
        initBack2(&b);

initialiser_score1(&sc);


        //continuer=0;
        printf("you winn \n");
        stage=2;
    }else
    {
        printf("you lostt \n");
        continuer=0;
    }
    break;
case 2:
if(stage==2)
{
    resultat_fichier=jouer(screen);
   }
    
break;

}

}

}



/*----------partie affichage---------*/
//SDL_BlitSurface(back,NULL,screen,NULL);
if (mode==mono_joueur)
{
    afficherBack(b,screen);
    afficherPerso(p,screen);
    afficherennemi(&e,screen);
    affichertemp(&temps,screen,police);
    afficherminimap(m,screen);
afficher_vie(&v,screen);
afficher_score(sc,screen);
affichage(t,screen); 
}
if (mode==new_game){
		SDL_BlitSurface(sous_menu_1[choix],NULL,screen,NULL);
	}	
if (mode==multijoueur)
{
    afficherBack_partage(b,screen);
    afficherPerso(p,screen);
    afficherPerso(p1,screen);
    affichertemp(&temps,screen,police);

affichage(t,screen); 
}
if (mode==save_game)
	{
		SDL_BlitSurface(menu[choix],NULL,screen,NULL);
	}

SDL_Flip(screen);

SDL_Delay(30);
}


    return 0;
}



