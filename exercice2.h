#ifndef EXERCICE2_H
#define EXERCICE2_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


struct tableau_variable{
    int nb_elements;
    unsigned int taille_memoire;
    void* elements;
    int maximum;
};



typedef struct test* Test; 

typedef struct tableau_variable* T_var;

T_var creer(unsigned int taille,int maximum);

T_var aleatoire_var(int nb_elements,unsigned int taille,int maximum ,void (*aleatoire) (void*));
void aleatoire_int(void* emplacement);
void aleatoire_structure(void* emplacement);

void afficher_var(T_var tab,void (*afficher_) (void*));


void push(T_var tab,void* elt);
void* pop(T_var tab); 

void push_indice(T_var tab,  int indice,void* elt);
void* pop_indice(T_var tab,  int indice);

void detruire_tout(T_var tab,void (*detruire)(T_var)) ;
void detruire_structure(T_var tab) ;
void detruire_int(T_var tab) ;

void* maximum(T_var tab ,void* (*maximum)(T_var));
void* maximum_int(T_var tab);
void* maximum_structure(T_var tab);

T_var slice (T_var tab, int n, int m);

T_var filtrer(T_var tab ,bool (*predicat)(void* elt));
bool predicat_superieur_30_int(void * elt);  
bool predicat_pair_int(void* elt);
bool predicat_pair_structure(void* elt);
#endif