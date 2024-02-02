#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "option.h"
#include "menu.h"

int afficher_menu(SDL_Surface *screen)
{
int volume=get_volume();
    int hb = 100, //3olw boutton
        lb = 300, //3orth boutton
        bs = 30;  // espace bin les bouttons

    int f = 0;
    int tmp = 0, m = 0;

//init click souris music
    Mix_Chunk  *music1;
    Mix_AllocateChannels(1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    music1 = Mix_LoadWAV("music/pan.wav");

//init back music
Mix_Music *music;
music= Mix_LoadMUS("music/danger.mp3");
Mix_VolumeMusic(volume);
Mix_PlayMusic(music,-1);



    //creation background
    SDL_Surface *background = NULL;
    background = IMG_Load("images/background.png");
    // detreminerr pos de back
    SDL_Rect background_pos;
    background_pos.x = 0;
    background_pos.y = 0;


    //creation bouton start
    SDL_Surface *start[2];
    start[0] = IMG_Load("images/play1.png");
    start[1] = IMG_Load("images/play2.png");
    int ng = 0;
    //pos buton start
    SDL_Rect start_pos;
    start_pos.x = 480;
    start_pos.y = 250;



    //creation bouton option
    SDL_Surface *setting[2];
    setting[0] = IMG_Load("images/options1.png");
    setting[1] = IMG_Load("images/options2.png");
    int op = 0;
    //pos buton option
    SDL_Rect setting_pos;
    setting_pos.x = 480;
    setting_pos.y = start_pos.y + hb + bs;

    //creation bouton quit
    SDL_Surface *quit[2];
    quit[0] = IMG_Load("images/quit1.png");
    quit[1] = IMG_Load("images/quit2.png");
    int ex = 0;
    //pos buton quit
    SDL_Rect quit_pos;
    quit_pos.x =480;
    quit_pos.y = setting_pos.y + hb + bs;

    int xmouse=700,ymouse=500;
  //creation du curseur
  curseur c;
  initialiser(&c,xmouse,ymouse);

        int t1 = 0, t2 = 0, r = 0;



    int t = 0;
    SDL_Event event;
    int done = 1;
    while (done)
    {

        t = 0;
        if (SDL_PollEvent(&event)) // ki ninzel ala ay haja
        {
            switch (event.type) //tal9a type el 7aja
            {
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            case SDL_QUIT: //nenzel 3al (X) el 7amra
                done = 0;
                break;
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            //avec clavier
            case SDL_KEYDOWN:                 // ay haja fil clav
c.show=0;
                switch (event.key.keysym.sym) // taref type l haja l nzalt alaha fil clav
                {
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_q: //q
                    done = 0;
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_UP: //flech fou9ani
                    if (ng == 0 && op == 0 && ex == 0)
                    {
                        ng = 1;
                    }
                    else if (ng == 1 && t == 0)
                    {
                        ex = 1;
                        ng = 0;
                        op = 0;
                        t = 1;
                    }

                    else if (op == 1 && t == 0)
                    {
                        ng = 1;
                        op = 0;
                        ex = 0;
                        t = 1;
                    }
                    else if (ex == 1 && t == 0)
                    {
                        op = 1;
                        ex = 0;
                        ng = 0;
                        t = 1;
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_DOWN: //flech loutani
                    if (ng == 0 && op == 0 && ex == 0)
                    {
                        ng = 1;
                    }
                    else if (ng == 1 && t == 0)
                    {
                        ex = 0;
                        ng = 0;
                        op = 1;
                        t = 1;
                    }

                    else if (op == 1 && t == 0)
                    {
                        ng = 0;
                        op = 0;
                        ex = 1;
                        t = 1;
                    }
                    else if (ex == 1 && t == 0)
                    {
                        op = 0;
                        ex = 0;
                        ng = 1;
                        t = 1;
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_RETURN: //entree
                    if (ng == 1)
                    {

                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                        return 1;
                    }

                    else if (op == 1)
                    {

                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                        return 2;
                    }
                    else if (ex == 1)
                    {

                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                       return 0;
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F3: //t9awi music
                  if (volume < 99 )
                    {
                        volume += 33;

                       Mix_VolumeMusic(volume);
                        save_volume(volume);
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F2: //tna9s music
                    if (volume > 0 )
                    {
                        volume -= 33;
                       Mix_VolumeMusic(volume);
                        save_volume(volume);
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F1: //mute//
                    if (m == 0)
                    {
                        tmp = volume;
                        volume = 0;
                        m = 1;
                    }
                    else if (m == 1)
                    {
                        volume = tmp;
                        m = 0;
                    }
                   Mix_VolumeMusic(volume);
                    save_volume(volume);
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F8: //full screen
                    if (f == 0)
                    {
                        screen = SDL_SetVideoMode(1000, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                        f = 1;
                    }
                    else if (f == 1)
                    {
                        screen = SDL_SetVideoMode(1000, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        f = 0;
                    }
                    break;
                }
                break;
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            //avec souris
            case SDL_MOUSEMOTION:
            c.show=1;
                ex = 0;
                ng = 0;
                op = 0;
                SDL_GetMouseState(&xmouse,&ymouse);

                if (event.motion.x > start_pos.x && event.motion.y > start_pos.y && event.motion.x < start_pos.x + lb && event.motion.y < start_pos.y + hb)
                {
                    ng = 1;
                }
                else if (event.motion.x > setting_pos.x && event.motion.y > setting_pos.y && event.motion.x < setting_pos.x + lb && event.motion.y < setting_pos.y + hb)
                {
                    op = 1;
                }
                else if (event.motion.x > quit_pos.x && event.motion.y > quit_pos.y && event.motion.x < quit_pos.x + lb && event.motion.y < quit_pos.y + hb)
                {
                    ex = 1;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (ng == 1)
                    {

                        Mix_PlayChannel(1, music1,1);
                        SDL_Delay(500);
                        return 1;
                    }

                    else if (op == 1)
                    {

                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(500);
                        return 2;
                    }
                    else if (ex == 1)
                    {
                        SDL_Delay(600);
                        return 0;
                    }
                }
                break;

            } //fin switch event
        }     //fin pollevent

        //afficher back
        SDL_BlitSurface(background, NULL, screen, &background_pos);
        SDL_BlitSurface(quit[ex], NULL, screen, &quit_pos);
        SDL_BlitSurface(start[ng], NULL, screen, &start_pos);
        SDL_BlitSurface(setting[op], NULL, screen, &setting_pos);
//curseur
        mvt_curseur_x(&c,xmouse);
        mvt_curseur_y(&c,ymouse);
        if (c.show) afficher_curseur(&c,screen);

      SDL_Flip(screen);

    } //fin while

Mix_FreeChunk(music1);

    SDL_FreeSurface(background);

    SDL_FreeSurface(start[0]);
    SDL_FreeSurface(start[1]);
    SDL_FreeSurface(setting[0]);
    SDL_FreeSurface(setting[1]);

    SDL_FreeSurface(quit[0]);
    SDL_FreeSurface(quit[1]);

}


int nb_frames = 9;
void init_tab_anim(SDL_Rect *clip)
{

    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = 60;
    clip[0].h = 65;
    int i = 1;
    for (i = 1; i < nb_frames; i++)
    {
        clip[i].w = 60;
        clip[i].h = 65;
        clip[i].x = clip[i].w + clip[i - 1].x;
        clip[i].y = 0;
    }

}

void initialiser(curseur *p, int xmouse, int ymouse)
{
    p->crow = IMG_Load("graphic/crow.png");
    p->crow_pos.x = xmouse;
    p->crow_pos.y = ymouse;
    p->crow_pos.w = 60;
    p->crow_pos.h = 65;
    p->show=1;
    init_tab_anim(p->animation);
    p->frame=0;

}
void afficher_curseur(curseur * p , SDL_Surface *screen)
{
   SDL_BlitSurface(p->crow,&p->animation[p->frame], screen, &p->crow_pos);


}
void animation(curseur *p)
{    p->frame++; //avancer vers case suivante
//le domaine est de la case 0 -> 8
    if (p->frame <0 || p->frame > nb_frames-1 ) p->frame=0;

}



void mvt_curseur_x(curseur *p, int xmouse){

  animation(p);
  if (p->crow_pos.x+p->crow_pos.w < xmouse )
        p->crow_pos.x+=5;
  if (p->crow_pos.x > xmouse)
        p->crow_pos.x -= 5;

}

void mvt_curseur_y(curseur *p, int ymouse){

  animation(p);

    if (p->crow_pos.y > ymouse )
              p->crow_pos.y-=5;
    if (p->crow_pos.y+p->crow_pos.h < ymouse)
              p->crow_pos.y  += 5;

}
