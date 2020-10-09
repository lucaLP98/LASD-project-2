/*
 * file : cityGraph_list.h
 *
 * In questo file vengono definite tutte le strutture dati, le funzioni e le
 * procedure per creare e manipolare liste di tratte aeree.
 */
#ifndef CITYGRAPH_LIST_H
#define CITYGRAPH_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct T_arch_city_list{
    char cityName[50];
    double travelCost;
    double flighTime;
    struct T_arch_city_list *next;
};
typedef struct T_arch_city_list cityArch;
typedef cityArch *cityList;

/*
 * Restituisce 1 se la lista e' vuota, 0 altrimenti
 */
int emptyRoutesList(cityList top);

/*
 * Inizializza la lista a NULL
 */
cityList initList();

/*
 * Funzione che restituisce 1 se la lista delle tratte e' vuota,
 * cioe' se non ci sono tratte da una determonata citta
 */
int noFlight(cityList top);

/*
 * Inserisce una nuova tratta in testa alla lista delle tratte
 */
cityList insertNewRoutesInHead(cityList t, char *cityName, double price, double flighTime);

/*
 * Inserisce una nuova Tratta in coda.
 * Restituisce in error 1 se la tratta gia e' presente, 0 altrimenti
 */
cityList insertNewRoutesInTail(cityList top, char *cityName, double price, double flighTime, int *error);

/*
 * Inserisce una nuova tratta preservando l'ordine alfabetico delle citta di destinazione
 * Restituisce in error 1 se la tratta gia e' presente, 0 altrimenti
 */
cityList insertNewRoutesInOrder(cityList top, char *cityName, double price, double flighTime, int *error);

/*
 * Stampa le tartte presenti nella lista
 */
void printList(cityList top);

/*
 * Dealloca la lista
 */
void freeList(cityList top);

/*
 * Elimina la prima tratta della lista
 */
cityList deleteHead(cityList top);

/*
 * Elimina l'ultima tratta della lista
 */
cityList deleteTail(cityList top);

/*
 * Elimina la tratta che ha come destinazione la citta "cityName"
 * In error viene restituito 0 se la tratta viene trovata e cancellata
 * correttamente, altrimenti -1 se la tratta non e' presente o se la
 * lista e' vuota
 */
cityList deleteRoutesToList(cityList top, char* cityName, int *error);

/*
 * Restituisce il nodo contenete il valore cercato se questo e' presente
 * nella lista, NULL altrimenti
 */
cityList searchRoute(cityList top, char* cityName);


#endif //CITYGRAPH_LIST_H
