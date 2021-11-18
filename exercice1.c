#include "exercice1.h"


T creer(int n , unsigned int taille){
    T tab = malloc(sizeof(struct tableau));
    if (tab == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
    tab->nb_elements = n;
    tab->taille_memoire = taille;
    tab->elements = malloc(n*taille);
    if (tab->elements == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
    return tab;
}

void afficher(T tab,void (*afficher) (void* elt)) {
    puts("***********affichage tableau generique*************");
    for (int i = 0; i < tab->nb_elements; i++)
    {   
       (*afficher)((char*)tab->elements+(i*tab->taille_memoire));
    }
    puts("\n***********fin affichage tableau generique*************\n");
}




T aleatoire(int n ,unsigned int taille,void (*aleatoire) (void*)) {
    T tab = creer(n,taille);
    for (int i = 0; i < tab->nb_elements; i++)
    {
       (*aleatoire)((char*)tab->elements+(i*tab->taille_memoire));
    }
    return tab;
}



void detruire_tout(T tab,void (*detruire)(T)){
    (*detruire)(tab);
}


void trier(T tab , int (*comparateur)(const void* a ,const void* b)){
    qsort(tab->elements,tab->nb_elements,tab->taille_memoire,comparateur);
}
