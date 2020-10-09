/*
 * file . path_list.h
 *
 * In questo file vengono definite le strutture e le funzioni che
 * permettono di modificare e creare un percorso aereo relativo ad
 * una prenotazione.
 * Il percorso da una citta' di partenza ad una cita' destinazione e'
 * rappresentato da una lista concatenata semplice, in cui:
 * - il primo nodo e' la citta di partenza;
 * - l'ultimo nodo e' la citta di destinazione
 * - i nodi intermedi rappresentano gli scali del volo
 */
#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "city_graph.h"

struct T_path_list{
    char city[50];
    struct T_path_list *next;
};
typedef struct T_path_list pathList;
typedef pathList* path;

/*
 * Inizializza un percorso a NULL (percorso vuoto)
 */
path initPath();

/*
 * Funzione che permette di inserire una nuova citta' in nel percorso.
 * L'inserimentro avviene in testa alla lista che rappresenta il percorso.
 */
path insertHeadInPath(path p, char newCity[]);

/*
 * Questa funzione pernde in input il grafo delle citta e delle tratte,
 * un array "pred" generato da un algoritmo per il calcolo dei percorsi
 * brevi (tipo dijkstra) a partire da un determinato vertice,
 * la citta di partenza "departureCity" e quella di destinazione "destinationCity".
 * Il suo compito e' quella di interpretrare l'array pred generato da dijkstra per
 * generare un percorso dalla citta di partenza alla destinazione.
 * In pratica, genera una lista in cui ogni nodo rappresenta una citta' in cui fare
 * scalo durante il volo da departureCity a destinationCity
 */
path createPath(cityGraph g, int *pred, int indexDepartureCity, int indexDestinationCity);

/*
 * Stampa il percorso che connette due citta'
 */
void printPath(path path);

/*
 * Calcola e restituisce il numero di scali che si hannp durante il percorso.
 * Restituisce -1 se il perocorso e' vuoto.
 */
int numberOfStopovers(path p);

/*
 * Dealloca un perorso.
 */
void freePath(path p);

#endif //PATH_LIST_H
