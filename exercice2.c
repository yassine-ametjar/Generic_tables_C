#include "exercice2.h"


T_var creer_var(unsigned int taille,int maximum){
    T_var tab = malloc(sizeof(struct tableau_variable));
    if (tab == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
    }
    tab->nb_elements = 0;
    tab->taille_memoire = taille;
    tab->maximum = maximum;
    tab->elements = calloc(maximum,taille);
    if (tab->elements == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
    }
    return tab;
}

T_var aleatoire_var(int nb_elements,unsigned int taille,int maximum ,void (*aleatoire) (void*)) {
    assert( nb_elements <= maximum );
    T_var tab = creer_var(taille,maximum);
    tab->nb_elements = nb_elements;
    for (int i = 0; i < tab->nb_elements; i++)
    {
       (*aleatoire)((char*)tab->elements+(i*tab->taille_memoire));
    }
    return tab;
}

 void afficher_var(T_var tab,void (*afficher)(void*)) {
    puts("***********affichage tableau generique*************");
    for (int i = 0; i < tab->nb_elements; i++)
    {   
       (*afficher)((char*)tab->elements+(i*tab->taille_memoire));
    }
    puts("\n***********fin affichage tableau generique*********\n");
}



void push(T_var tab,void* elt){
    if (tab->nb_elements==tab->maximum){
        void *tmp = realloc(tab->elements, tab->taille_memoire * (tab->maximum * 2));
        if (tmp == NULL){
            fprintf(stderr, "Échec de l'allocation\n");
            exit(EXIT_FAILURE);
        }
        tab->maximum *= 2;
        tab->elements = tmp;
    }
    memcpy((char*)(tab->elements) + tab->nb_elements * tab->taille_memoire ,elt,tab->taille_memoire);
    tab->nb_elements++;
} 
void* pop(T_var tab){
    assert(tab->nb_elements > 0 && "Vous faites un Pop alors que le tableau est vide");
    tab->nb_elements--;
 
    if(tab->nb_elements < (tab->maximum)/2 ){
        void *tmp = realloc(tab->elements, tab->taille_memoire * (tab->maximum / 2));
        if (tmp == NULL){
            fprintf(stderr, "Échec de l'allocation\n");
            exit(EXIT_FAILURE);
        }
        tab->maximum /= 2;
        tab->elements = tmp;
    }
    void* x = malloc(tab->taille_memoire);
    if(x == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
    }
    memcpy(x,(char *)tab->elements + tab->nb_elements * tab->taille_memoire,tab->taille_memoire);
    return x;


}
void push_indice(T_var tab,  int indice,void* elt){
    assert(indice >= 0);
    assert(indice<=tab->nb_elements && "L'indice est supérieur au nombre d'élément");

    if (tab->nb_elements==tab->maximum-1 ){
        void *tmp = realloc(tab->elements, tab->taille_memoire * (tab->maximum * 2));
        if (tmp == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
        }
        tab->maximum *= 2;
        tab->elements = tmp;
    }
    for (int i = (tab->nb_elements)+1; i > indice; i--){
       //element precedent recoit l'suivant à l'indice
       memmove((char*)tab->elements+(i*tab->taille_memoire),(char*)tab->elements+((i-1)*tab->taille_memoire),tab->taille_memoire);
    }
    memcpy((char*)tab->elements + (indice * tab->taille_memoire),elt,tab->taille_memoire);
    tab->nb_elements++;
    }
void* pop_indice(T_var tab , int indice){
    assert(indice >= 0);
    assert(indice < tab->nb_elements && "L'élément à retirer n'est pas dans le tableau");
    assert(tab->nb_elements > 0);
    //chaque element recoit element suivant à partir de l'indice
    for (int i = indice; i < tab->nb_elements-1; i++){
       memmove((char*)tab->elements+(i*tab->taille_memoire),(char*)tab->elements+((i+1)*tab->taille_memoire),tab->taille_memoire);
    }
    tab->nb_elements--;
    if(tab->nb_elements < (tab->maximum)/2 ){
        void *tmp = realloc(tab->elements, tab->taille_memoire * (tab->maximum / 2));
        if (tmp == NULL){
            fprintf(stderr, "Échec de l'allocation\n");
            exit(EXIT_FAILURE);
        }
        tab->maximum /= 2;
        tab->elements = tmp;
    }
    void* x = malloc(tab->taille_memoire);
    if (x==NULL)
    {
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
    }
    memcpy(x,(char*)tab->elements +( tab->nb_elements * tab->taille_memoire),tab->taille_memoire);
    return x;
    

}



void detruire_tout(T_var tab,void (*detruire)(T_var)){
    (*detruire)(tab);
}

                                 
void* maximum(T_var tab ,void* (*maximum)(T_var)){
    return (*maximum)(tab);
}

T_var slice (T_var tab,  int n, int m){
    assert(n>=0 && "votre indice est negatif");
    assert(m>n && "m doit être supérieur à n");
    assert(m <= tab->nb_elements && "m doit être inférieur au nombre d'éléments du tableau");
    T_var nv = creer_var(tab->taille_memoire,tab->maximum);
    nv->nb_elements = m-n;
    memcpy(nv->elements,(char*)(tab->elements) + (tab->taille_memoire * n) ,((m-n)* tab->taille_memoire));
    return nv;
}

T_var filtrer(T_var tab ,bool (*predicat)(void* elt)){
    void * tmp = malloc(tab->taille_memoire * tab->nb_elements);
    if (tmp == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
    }
    int j = 0;
    for (int i = 0; i < tab->nb_elements; i++)
    {   
        if((*predicat)((char*)(tab->elements)+(tab->taille_memoire*i))){
            memcpy((char*)(tmp)+(j*tab->taille_memoire),(char*)(tab->elements)+(tab->taille_memoire*i),tab->taille_memoire);
            j++;
        }
    }
    T_var tab_final = creer_var(tab->taille_memoire,tab->maximum);
    tab_final->nb_elements = j;
    memcpy(tab_final->elements,tmp,tab->nb_elements*tab->taille_memoire);
    free(tmp);
    return tab_final;
}
