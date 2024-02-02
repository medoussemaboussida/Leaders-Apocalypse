all: main.o menu.o option.o test.o sauvegarde.o Personne.o minimap.o enigme.o enigme_IA.o enig_fichier.o enemie.o pc.o
	gcc main.o menu.o option.o test.o sauvegarde.o Personne.o minimap.o enigme.o enigme_IA.o enig_fichier.o enemie.o pc.o -o Game -lSDL -lSDL_image  -lSDL_ttf -lSDL_mixer 


clean:
	rm -rf *.o

mrproper:
	rm -rf Jeu
