/*
 * file : cityGraph_list.c
 *
 * In questo file vengono implementate le funzioni e procedure che permettono
 * di manipolare liste di tratte aeree
 */
#include "cityGraph_list.h"

int emptyRoutesList(cityList top){
    return top ==  NULL;
}

cityList initList(){
    return NULL;
}

int noFlight(cityList top){
    return top == NULL;
}

cityList insertNewRoutesInHead(cityList t, char *cityName, double price, double flighTime){
    cityList tmp = (cityList)malloc(sizeof(cityArch));

    tmp->flighTime = flighTime;
    tmp->travelCost = price;
    strcpy(tmp->cityName, cityName);
    tmp->next = t;

    return tmp;
}

cityList insertNewRoutesInTail(cityList top, char *cityName, double price, double flighTime, int *error){
    cityList tmp, ptr;
    int alreadyExisting = 0;

    if(!emptyRoutesList(top)){
        ptr = top;

        while(ptr->next != NULL && alreadyExisting == 0) {
            if(strcmp(ptr->cityName, cityName) == 0)
                alreadyExisting = 1;
            else
                ptr = ptr->next;
        }

        if(alreadyExisting == 0){
            tmp = (cityList)malloc(sizeof(cityArch));

            strcpy(tmp->cityName, cityName);
            tmp->travelCost = price;
            tmp->flighTime = flighTime;
            tmp->next = NULL;

            ptr->next = tmp;
        }
    }else{
        top = insertNewRoutesInHead(top, cityName, price, flighTime);
    }
    *error = alreadyExisting;

    return top;
}

cityList insertNewRoutesInOrder(cityList top, char *cityName, double price, double flighTime, int *error){
    cityList tmp, ptr;
    int alreadyExisting = 0;

    if(emptyRoutesList(top) || strcmp(top->cityName, cityName) > 0){
        top = insertNewRoutesInHead(top, cityName, price, flighTime);
    }else{
        ptr = top;

        while(ptr->next != NULL && strcmp(ptr->next->cityName, cityName) < 0 && alreadyExisting == 0)
            if(strcmp(ptr->cityName, cityName) == 0)
                alreadyExisting = 1;
            else
                ptr = ptr->next;

        if(alreadyExisting == 0) {
            tmp = (cityList)malloc(sizeof(cityArch));

            strcpy(top->cityName, cityName);
            tmp->travelCost = price;
            tmp->flighTime = flighTime;
            tmp->next = ptr->next;

            ptr->next = tmp;
        }
    }
    *error = alreadyExisting;

    return top;
}

void printList(cityList top){
    cityList ptr = top;

    if(emptyRoutesList(top))
        printf(" nessun volo disponibile da qusta localita'");
    else {
        printf(" voli diretti verso le seguenti citta':\n\n");
        while (ptr != NULL) {
            printf("%20s\t\t Costo : %.2lf €,\t Durata %.0lf minuti\n", ptr->cityName, ptr->travelCost, ptr->flighTime);
            ptr = ptr->next;
        }
    }
    printf("\n\n");
}

void freeList(cityList top){
    if(!emptyRoutesList(top)){
        freeList(top->next);
        free(top);
    }
}

cityList deleteHead(cityList top){
    cityList tmp;

    if(!emptyRoutesList(top)){
        tmp = top;
        top = top->next;
        free(tmp);
    }

    return top;
}

cityList deleteTail(cityList top){
    cityList ptr, ptrPrew;

    if(!emptyRoutesList(top)){
        if(top->next == NULL){
            deleteHead(top);
        }else{
            ptr = top->next;
            ptrPrew = top;

            while(ptr->next != NULL){
                ptrPrew = ptr;
                ptr = ptr->next;
            }

            ptrPrew->next = NULL;
            free(ptr);
        }
    }

    return top;
}

cityList deleteRoutesToList(cityList top, char* cityName, int *error){
    cityList ptr, prev;
    int found = -1;

    if(!emptyRoutesList(top)){
        if(!(strcmp(top->cityName, cityName)))
            top = deleteHead(top);
        else{
            ptr = top->next;
            prev = top;

            while(ptr != NULL && found == -1)
                if(!(strcmp(ptr->cityName, cityName))){
                    found = 0;
                    prev->next = ptr->next;
                    free(ptr);
                }else{
                    prev = ptr;
                    ptr = ptr->next;
                }
        }
    }
    *error = found;

    return top;
}

cityList searchValue(cityList top, char* cityName){
    if(top == NULL || !(strcmp(top->cityName, cityName)))
        return top;

    return searchValue(top->next, cityName);
}
