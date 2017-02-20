#include "stdafx.h"



using namespace std;


int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

int* init_sans_doublons(int a, int b){
	int taille = b-a;
	int* resultat=(int*)malloc((taille)*sizeof (int));
	int i=0;
	// On remplit le tableau de mani�re � ce qu'il soit tri�
	for(i = 0; i< taille; i++){
		resultat[i]=i+a;
	}
	return resultat;
}

void melanger(int* tableau, int taille){
	int i=0;
	int nombre_tire=0;
	int temp=0;
	
	for(i = 0; i< taille;i++){
		nombre_tire=rand_a_b(0,taille);
		// On �change les contenus des cases i et nombre_tire
		temp = tableau[i];
		tableau[i] = tableau[nombre_tire];
		tableau[nombre_tire]=temp;
	}
}
