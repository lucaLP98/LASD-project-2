/*
 * file ABR_city_tree.c
 */
#include "ABR_city_tree.h"

#include "ABR_city_tree.h"
#include <string.h>

int emptyCityTree(city_tree T){
    return (T == NULL);
}

int insertCityTreeNumberOfElement(){
    int height;

    printf("\n Inserire il numero di elementi dell' ABR");
    do{
        printf(" >>> ");
        scanf("%d", &height);
        if(height < 0)
            printf("\n ERRORE ! Non inserire in valore negativo\n\n Riprova");
    }while(height < 0);

    return height;
}

void preOrderCityTreeView(city_tree T){
    if( T != NULL ){
        printf(" %s %d\t", T->city_name, T->index);
        preOrderCityTreeView(T->sx);
        preOrderCityTreeView(T->dx);
    }
}

void inOrderCityTreeView(city_tree T){
    if( T != NULL ){
        inOrderCityTreeView(T->sx);
        printf("\nCitta'  : %s\tIndice : %d\n", T->city_name, T->index);
        inOrderCityTreeView(T->dx);
    }
}

void postOrderCityTreeView(city_tree T){
    if( T != NULL ){
        postOrderCityTreeView(T->sx);
        postOrderCityTreeView(T->dx);
        printf(" %s %d\t", T->city_name, T->index);
    }
}

city_tree allocateNewCity(char city_name[], int index){
    city_tree tmp;

    tmp = (city_tree)malloc(sizeof(ABRcitytree));
    strcpy (tmp->city_name, city_name);
    tmp->index = index;
    tmp->sx = NULL;
    tmp->dx = NULL;

    return tmp;
}

city_tree insertNewCityInABR(city_tree T, char city_name[], int index){

    if( T != NULL){
        if( strcoll(T->city_name, city_name) > 0)
            T->sx = insertNewCityInABR(T->sx, city_name, index);
        else if( strcoll(T->city_name, city_name) < 0 )
            T->dx = insertNewCityInABR(T->dx, city_name, index);
    }else{
        T = allocateNewCity(city_name, index);
    }

    return T;
}

city_tree searchCityInABR(city_tree T, char city_name[]){
    if(!emptyCityTree(T)){
        if(strcmp(city_name, T->city_name) < 0)
            return searchCityInABR(T->sx, city_name);

        if(strcmp(city_name, T->city_name) > 0)
            return searchCityInABR(T->dx, city_name);
    }

    return T;
}

int countNumberOfCitiesInABR(city_tree T){
    int numberOfNode = 0;

    if( T != NULL ){
        numberOfNode = 1;
        numberOfNode += countNumberOfCitiesInABR( T->dx );
        numberOfNode += countNumberOfCitiesInABR( T->sx );
    }

    return numberOfNode;
}

city_tree detachMinimum(city_tree T, city_tree P){
    if( T != NULL ){
        if( T->sx != NULL )
            return detachMinimum( T->sx, T );

        if( P->sx == T )
            P->sx = T->dx;
        else
            P->dx = T->dx;
    }

    return T;
}

city_tree deleteRoot(city_tree T){
    city_tree tmp = NULL;

    if(T != NULL){
        if( T->sx == NULL  || T->dx == NULL ){
            tmp = T;
            if(T->sx != NULL)
                T = T->sx;
            else
                T = T->dx;
        }
        else {
            tmp = detachMinimum( T->dx, T );
            strcpy(T->city_name, tmp->city_name);
        }

        free(tmp);
    }

    return T;
}

city_tree deleteNode(city_tree T, char city_name[]) {
    if( T != NULL){
        if( strcmp (T->city_name, city_name) == 0 )
            T = deleteRoot( T );
        else if( strcoll(T->city_name, city_name) < 0 )
            T->dx = deleteNode( T->dx, city_name );
        else
            T->sx = deleteNode( T->sx, city_name );
    }

    return T;
}

int findIndexCity (city_tree T, char city_name[]) {
    city_tree tmp;
    int result;

    if ((tmp = searchCityInABR(T, city_name)) != NULL)
        result = tmp->index;
    else    result = -1;

    return result;
}

void freeABR(city_tree t){
    if(!emptyCityTree(t)){
        freeABR(t->sx);
        freeABR(t->dx);
        free(t);
    }
}
