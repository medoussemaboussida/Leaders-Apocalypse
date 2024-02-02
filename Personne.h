#ifndef perso_H_INCLUDED
#define perso_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

/** 
* @struct Personne 
* @brief struct pour personne 
*/ 


typedef struct Personne
{
	SDL_Surface *images[2][4]; /*!< matrices contenant les 24 frames*/
	SDL_Rect position;/*!< position de perso*/
	int direction;/*!< direction du perso*/
	int nbr_frame;/*!< nombre de frame a afficher*/
	/*
		0:droite
		1:gauche
	*/
	double vitesse,acceleration,vitesse_saut;
	double dx;
	int ground,up;

}Personne;


/** 
* @struct vie 
* @brief struct pour vie 
*/ 
typedef struct  vie
{
	SDL_Surface *vie; /*!<surface */
	int valeur_vie;/*!<variable*/
	SDL_Rect pos_spr,pos;/*!< rectangle*/
}vie;

/** 
* @struct score
* @brief struct pour score 
*/ 
typedef struct Score
{
    SDL_Surface *texte_score;/*!<surface */
    SDL_Rect position_texte;/*!< rectangle*/
    TTF_Font *score_font;/*!< texte*/
char score_str[10] ;/*!<chaine de caracteres*/
int tempsActuel,tempsPrecedent;/*!< variables*/
int min,cmp;/*!< variables*/
    SDL_Color couleurNoire;/*!<couleur*/
    int valeur_score;/*!< variable*/
} score;

/** 
* @brief initialiser le perso . 
* @param p le perso   
* @return Nothing 
*/ 
void initPerso2(Personne *p);

void initPerso(Personne *p);
/** 
* @brief afficher le personnage . 
* @param p le perso 
* @param screen le fentre  
* @return Nothing 
*/ 

void afficherPerso(Personne p, SDL_Surface * screen);
/** 
* @brief deplacer le personnage . 
* @param p perso 
* @param dt durée du temps entre le debut el fin de boucle  
* @return Nothing 
*/ 

void deplacerPerso (Personne *p,int dt);
void deplacerPerso2 (Personne *p,int dt);
/** 
* @brief animation du personnage . 
* @param p perso  
* @return Nothing 
*/ 

void animerPerso (Personne* p);

/** 
* @brief saut du personnage . 
* @param p perso 
* @return Nothing 
*/ 

void saut (Personne* p) ;

/** 
* @brief To initialize vie v
* @param v vie
* @return nothing
*/

void initialiser_score(vie *v);
/** 
* @brief To update vie v
* @param v vie
* @return nothing
*/
void update_score(vie *v);
/** 
* @brief To show vie v
* @param screen the screen
* @param v vie
* @return nothing
*/
void afficher_vie(vie *v,SDL_Surface *screen);
/** 
* @brief To initialize score sc
* @param sc score
* @return nothing
*/

void initialiser_score1(score *sc);
/** 
* @brief To show score sc
* @param screen the screen
* @param sc score
* @return nothing
*/
void afficher_score(score sc,SDL_Surface *screen);

void sauvegarder1(score sc);
 #endif
