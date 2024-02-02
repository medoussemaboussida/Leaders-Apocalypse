/** 
* @file Personne.c 
*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "Personne.h"

/** 
* @brief initialiser le perso . 
* @param p le perso   
* @return Nothing 
*/ 
void initPerso(Personne *p){
	int i,j;
    char nom_image[30];
    p->acceleration=0;
    p->direction=0;
    p->nbr_frame=0;
    p->up=0;
    p->ground=0;
    p->position.x=300;
    p->position.y=0;
    p->position.w=115;
    p->position.h=105;

    p->vitesse=0;
    p->vitesse_saut=0;

 
    for ( i = 0; i < 2; i++)
    {
        for ( j = 0; j < 4; j++)
        {   
            sprintf(nom_image,"animation/%d/%d.png",i,j);
            p->images[i][j]=IMG_Load(nom_image);
        }
        
    }
    
}
/** 
* @brief initialiser le perso . 
* @param p le perso   
* @return Nothing 
*/ 
void initPerso2(Personne *p){
	int i,j;
    char nom_image[30];
    p->acceleration=0;
    p->direction=0;
    p->nbr_frame=0;
    p->up=0;
    p->ground=0;
    p->position.x=800;
    p->position.y=0;
    p->position.w=115;
    p->position.h=105;

    p->vitesse=0;
    p->vitesse_saut=0;

 
    for ( i = 0; i < 2; i++)
    {
        for ( j = 0; j < 4; j++)
        {   
            sprintf(nom_image,"animation1/%d/%d.png",i,j);
            p->images[i][j]=IMG_Load(nom_image);
        }
        
    }
    
}

/** 
* @brief afficher le personnage . 
* @param p le perso 
* @param screen le fentre  
* @return Nothing 
*/ 
void afficherPerso(Personne p, SDL_Surface * screen){
    SDL_BlitSurface(p.images[p.direction][p.nbr_frame],NULL,screen,&p.position);
}

/** 
* @brief animation du personnage . 
* @param p perso  
* @return Nothing 
*/ 


void animerPerso (Personne* p){
    
  p->nbr_frame++;
    if (p->nbr_frame >= 4)
 p->nbr_frame=0;
if ((p->vitesse==0) && ((p->direction == 0) || (p->direction == 1)))
{
p->nbr_frame= 0;
}
}
/** 
* @brief deplacer le personnage . 
* @param p perso 
* @param dt durée du temps entre le debut et la fin de boucle  
* @return Nothing 
*/ 
void deplacerPerso (Personne *p,int dt){

p->dx = 0.5 * p->acceleration * dt * dt + p->vitesse * dt ;
    if (p->direction==0)//mvt droite
    {
       if (p->position.x < 300) p->position.x = p->position.x + p->dx ;        
    }else if (p->direction==1)
    {
        if (p->position.x > 100) p->position.x = p->position.x - p->dx;
    }
    
}
/** 
* @brief deplacer le personnage . 
* @param p perso 
* @param dt durée du temps entre le debut el fin de boucle  
* @return Nothing 
*/ 
void deplacerPerso2 (Personne *p,int dt){

p->dx = 0.5 * p->acceleration * dt * dt + p->vitesse * dt ;
    if (p->direction==0)//mvt droite
    {
       if (p->position.x < 300) p->position.x = p->position.x + p->dx ;        
    }else if (p->direction==1)
    {
        if (p->position.x >100) p->position.x = p->position.x - p->dx;
    }
    
}
/** 
* @brief saut du personnage . 
* @param p perso 
* @return Nothing 
*/ 

void saut (Personne* p) {
    if (p->position.y == p->ground)
    {
       p->vitesse_saut=-50;
       p->up=1;
    }
    
}


/** 
* @brief To initialize vie v
* @param v vie
* @return nothing
*/

void initialiser_score(vie *v){
    v->vie=IMG_Load("images/health.png");
    v->valeur_vie=100;
    v->pos.x=0;
    v->pos.y=150;
    v->pos_spr.x=0;
    v->pos_spr.y=0;
    v->pos_spr.h=50;
    v->pos_spr.w=200;
}
/** 
* @brief To update vie v
* @param v vie
* @return nothing
*/

void update_score(vie *v){
    v->pos_spr.y=((100-v->valeur_vie)/25)*50;
}
/** 
* @brief To show vie v
* @param screen the screen
* @param v vie
* @return nothing
*/
void afficher_vie(vie *v,SDL_Surface *screen){
    SDL_BlitSurface(v->vie,&v->pos_spr,screen,&v->pos);
}


/** 
* @brief To initialize score sc
* @param sc score
* @return nothing
*/


void initialiser_score1(score *sc)
{
sc->texte_score= NULL;

sc->position_texte.x=250;
sc->position_texte.y=150;


sc->score_font = NULL;
sc->score_font = TTF_OpenFont("DS-DIGI.TTF",40);
if(sc->score_font==NULL)
printf("error police\n");

sc->valeur_score = 0; 
sc->tempsActuel=0;

}

/** 
* @brief To show score sc
* @param screen the screen
* @param sc score
* @return nothing
*/ 
void afficher_score(score sc,SDL_Surface *screen)
{
TTF_Font *police = NULL;

   // TTF_Init();

 

SDL_Color couleurNoire = {0, 0, 0};


int j ;

 sc.score_font = TTF_OpenFont("DS-DIGI.TTF",40);
 j = SDL_GetTicks();
sc.valeur_score=(sc.valeur_score+j)/1000;
 sprintf(sc.score_str, "score: %d",sc.valeur_score);


	sc.texte_score = TTF_RenderText_Blended(sc.score_font, sc.score_str, couleurNoire);

       sc.position_texte.x =250;
	sc.position_texte.y =150;
 		SDL_BlitSurface(sc.texte_score, NULL, screen, &sc.position_texte);
	        SDL_Flip(screen);
sauvegarder1(sc);
}

void sauvegarder1(score sc)
{



if (sc.valeur_score > 2) //Le cas ou le joueur commence a avoir un bon score.
    {
		printf("Bien Joué ton score finale est : %d\n", sc.valeur_score);  //On affiche sur la console son bon score.
	}
	else //sinon.
	{
		printf("Ton score finale est : %d\n", sc.valeur_score); //On affiche sur la console son score.
	}
	FILE *fp=fopen("Score.txt", "a+"); //On ouvre le fichier score en mode append.
	fprintf(fp, "%d\n", sc.valeur_score); //On enregistre dedans le socre de la partie.
	fclose(fp); //On ferme le fichier.

}

















