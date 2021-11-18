
 #include "exercice1.h"
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

void aleatoire_structure(void* emplacement){
   Test elt_structure = malloc(sizeof(struct test));
   if (elt_structure == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
   elt_structure->a = rand() % 101;
   elt_structure->b = rand() % 101;
   elt_structure->c = rand() % 101;
   memcpy(emplacement,(void*)elt_structure,sizeof(struct test));
   free(elt_structure);
}
static void afficher_int(void* elt) {
    int* elt_int = (int*)elt;
    printf("%d\t",*elt_int);
}
void aleatoire_int(void * emplacement) {
   int* elt_int = malloc(sizeof(int));
   if (elt_int == NULL){
        fprintf(stderr, "Échec de l'allocation\n");
        exit(EXIT_FAILURE);
   } 
   elt_int[0] = rand() % 101;
   memcpy(emplacement,(void*)elt_int,sizeof(int));
   free(elt_int);
}

void detruire_int(T tab) {
    free(tab->elements);
    free(tab);
}
void detruire_structure(T tab) {
    free(tab->elements);
    free(tab);
}
int comparateur_int(const void* a,const void* b){
    return(*(int*)a - *(int*)b);
}

int comparateur_structure_premier_elt(const void* a,const void* b){
    const Test x = (Test) a;
    const Test y = (Test) b;
    return((int)x->a - (int)y->a);
} 
int comparateur_structure_moyenne(const void* a,const void* b){
    const Test x = (Test) a;
    const Test y = (Test) b;
    return((int)(x->a + x->b + x->c) - (int)(y->a + y->b + y->c));
} 

int comparateur_structure_tt_elt(const void* a,const void* b){
    const Test x = (Test) a;
    const Test y = (Test) b;
    if ((int)x->a - (int)y->a == 0){
        return((int)x->b - (int)y->b);
        if ((int)x->b - (int)y->b == 0){
            return((int)x->c - (int)y->c);
        }
    }
    return((int)x->a - (int)y->a);
}

int main() {
    
    
    srand(time(NULL));
    T array = aleatoire(5,sizeof(int), &aleatoire_int);
    T array1 = aleatoire(5,sizeof(struct test),&aleatoire_structure) ;

    afficher(array,&afficher_int); // affichage de array
    afficher(array1,&afficher_structure);

    
    trier(array,&comparateur_int);
    afficher(array,&afficher_int);
    trier(array1,&comparateur_structure_moyenne);
    afficher(array1,&afficher_structure);   
/*  trier(array1,&comparateur_structure_premier_elt);
    afficher(array1,&afficher_structure);   
    trier(array1,&comparateur_structure_tt_elt);
    afficher(array1,&afficher_structure); */ 

    detruire_tout(array,&detruire_int);
    detruire_tout(array1,&detruire_structure);
     
    return EXIT_SUCCESS;
}
