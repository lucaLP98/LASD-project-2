/*
 * File : path_list.c
 */
#include "path_list.h"

path initPath(){
    return NULL;
}

path insertHeadInPath(path p, char newCity[]){
    path tmp = (path)malloc(sizeof(pathList));
    strcpy(tmp->city, newCity);
    tmp->next = p;

    return tmp;
}

path createPath(cityGraph g, int *pred, int indexDepartureCity, int indexDestinationCity){
    path P;
    int i;

    if(indexDepartureCity != indexDestinationCity) {
        P = initPath();
        i = indexDestinationCity;
        while (i != -1) {
            P = insertHeadInPath(P, g->cities[i].cityName);
            i = pred[i];
        }
        insertHeadInPath(P, g->cities[indexDepartureCity].cityName);
    }

    return P;
}

void printPath(path P){
    path cur = P;

    printf("\n - La rotta aerea e' la seguente : \n\n");
    while(cur != NULL){
        printf(" %s ---> ", cur->city);
        cur = cur->next;
    }
    printf(" ARRIVO !\n\n");
}

int numberOfStopovers(path p){
    path cur;
    int count;

    if(p != NULL){
        count = 0;
        cur = p->next;
        while(cur->next != NULL){
            count++;
            cur = cur->next;
        }
    }else   count = -1;

    return count;
}

void freePath(path p){
    path tmp;

    while(p != NULL){
        tmp = p;
        p = p->next;
        free(tmp);
    }
    free(p);
}
