#ifndef EXERCICE1_H
#define EXERCICE1_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tableau{
    int nb_elements;
    unsigned int taille_memoire;
    void* elements;
};


typedef struct test* Test; 

typedef struct tableau* T;

T creer(int n , unsigned int taille);

void afficher(T tab,void (*afficher_) (void*));


T  aleatoire(int n ,unsigned int taille,void (*aleatoire) (void*));
void aleatoire_structure(void* emplacement);
void aleatoire_int(void*);

void detruire_tout(T tab,void (*detruire)(T)) ;
void detruire_structure(T tab) ;
void detruire_int(T tab) ;

void trier(T tab , int (*comparateur)(const void* a ,const void* b));
int comparateur_int(const void* a,const void* b);
int comparateur_structure_premier_elt(const void* a,const void* b);
int comparateur_structure_moyenne(const void* a,const void* b);
int comparateur_structure_tt_elt(const void* a,const void* b);

#endif