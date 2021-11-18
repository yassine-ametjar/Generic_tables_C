#include "exercice2.h"

struct test {
    long long int a;
    long long int b;
    long long int c;
};

static void afficher_structure(void* elt) {
    Test elt_struct = (Test) elt;
    printf("%lld\t" ,elt_struct->a);
    printf("%lld\t" ,elt_struct->b);
    printf("%lld\n" ,elt_struct->c);
}

void aleatoire_structure(void* emplacement) {
   Test tableau_structure = malloc(sizeof(struct test));
   if (tableau_structure == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
   tableau_structure->a = rand() % 101;
   tableau_structure->b = rand() % 101;
   tableau_structure->c = rand() % 101;
   memcpy(emplacement,(void*)tableau_structure,sizeof(struct test));
   free(tableau_structure);
}
void aleatoire_int(void* emplacement) {
   int* tableau_int = malloc(sizeof(int));
   if (tableau_int == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
   tableau_int[0] = rand() % 101;
   memcpy(emplacement,(void*)tableau_int,sizeof(int));
   free(tableau_int);
}

void detruire_structure(T_var tab) {
    free(tab->elements);
    free(tab);
}

static void afficher_int(void* elt) {
    int* elt_int = (int*)elt;
    printf("%d\t",*elt_int);
}


void detruire_int(T_var tab) {
    free(tab->elements);
    free(tab);
}

void* maximum_int(T_var tab) {
    int* tableau_int = malloc(tab->maximum * tab->taille_memoire );
    if (tableau_int == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
    memcpy((void*)tableau_int,tab->elements,(tab->nb_elements * tab->taille_memoire));
    int max = tableau_int[0];
    int indice = 0;

    for (int i = 1; i < tab->nb_elements; i++)
    {
        if (max < tableau_int[i]){
          max = tableau_int[i] ;
          indice = i;
        } 
    }
    void* x = malloc(tab->taille_memoire);
    if (x == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
    memcpy(x,(void*)(tableau_int + indice),tab->taille_memoire);
    free(tableau_int);
    return x;
}

void* maximum_structure(T_var tab) {
    Test tableau_structure = malloc(tab->maximum * tab->taille_memoire );
    if (tableau_structure == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
    memcpy((void*)tableau_structure,tab->elements,(tab->nb_elements * tab->taille_memoire));
    long long int max = tableau_structure[0].a;
    int indice = 0;

    for (int i = 1; i < tab->nb_elements; i++)
    {
        if (max < tableau_structure[i].a){
          max = tableau_structure[i].a ;
          indice = i;
        } 
    }
    void* x = malloc(tab->taille_memoire);
    if (x == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
    memcpy(x,(void*)(tableau_structure + indice),tab->taille_memoire);
    free(tableau_structure);
    return x;
}        
bool predicat_superieur_30_int(void* elt){
    int* x = (int*)elt;
    return *x >= 30;
}
bool predicat_pair_int(void* elt){
    int*x = (int*)elt;
    return *x%2 == 0;
}
bool predicat_pair_structure(void* elt){
    Test x = (Test) elt;
    return (int)x->a%2 == 0;
}

int main() {
    
    srand(time(NULL));

    T_var tableau = aleatoire_var(5,sizeof(int),7,aleatoire_int);
    T_var tableau_1 = aleatoire_var(5,sizeof(struct test),7,aleatoire_structure);

    afficher_var(tableau,&afficher_int); // affichage de tableau
    afficher_var(tableau_1,&afficher_structure);

    int a = 8473843;
    struct test b ;
    b.a = 1;
    b.b = 2;
    b.c = 3 ; 

    push(tableau,&a);
    push(tableau_1,&b);
    afficher_var(tableau,&afficher_int); // affichage de tableau
    afficher_var(tableau_1,&afficher_structure);

    
    void *popped = pop(tableau); // suppression du dernier élément de tableau
    free(popped);
    popped = pop(tableau); // suppression du dernier élément de tableau
    free(popped);
    afficher_var(tableau,&afficher_int); // affichage de tableau

    popped = pop(tableau_1); // suppression du dernier élément de tableau_1
    free(popped);
    popped = pop(tableau_1); // suppression du dernier élément de tableau_1
    free(popped);
    afficher_var(tableau_1,&afficher_structure); 

    
    push_indice(tableau,0,&a); 
    push_indice(tableau_1,2,&b); 
    afficher_var(tableau,&afficher_int); // affichage de tableau
    afficher_var(tableau_1,&afficher_structure); // affichage de tableau 
    
    popped = pop_indice(tableau,0);
    free(popped);
    afficher_var(tableau,&afficher_int); // affichage de tableau
    // affichage de tableau
    popped = pop_indice(tableau_1,2);
    free(popped);
    afficher_var(tableau_1,&afficher_structure); // affichage de tableau */ 

    T_var sous_partie_tableau = slice(tableau,0,3);
    T_var sous_partie_tableau_1 = slice(tableau_1,1,2);
    afficher_var(sous_partie_tableau,&afficher_int); // affichage de tableau
    afficher_var(sous_partie_tableau_1,&afficher_structure); // affichage de tableau 


    int* max = (int*)maximum(tableau,&maximum_int);
    printf(" \nmaximum : %d\n",*max); 
    free(max);
    Test max1 = (Test)maximum(tableau_1,&maximum_structure);
    printf(" \n maximum : %lld\t %lld\t %lld\n",max1->a,max1->b,max1->c); 
    free(max1);

    T_var tableauF = filtrer(tableau,predicat_superieur_30_int);
    afficher_var(tableauF,&afficher_int); // affichage de tableau */

    T_var tableauP = filtrer(tableau,predicat_pair_int);
    afficher_var(tableauP,&afficher_int); // affichage de tableau

    T_var tableauPS = filtrer(tableau_1,predicat_pair_structure);
    afficher_var(tableauPS,&afficher_structure); // affichage de tableau 


    detruire_tout(sous_partie_tableau,&detruire_int);
    detruire_tout(sous_partie_tableau_1,&detruire_structure);
    detruire_tout(tableauF,&detruire_int); 
    detruire_tout(tableauP,&detruire_int);
    detruire_tout(tableauPS,&detruire_int);     
    detruire_tout(tableau,&detruire_int);
    detruire_tout(tableau_1,&detruire_structure);  

    
   
     


    return EXIT_SUCCESS;
}

