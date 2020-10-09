/*
 * file : ABR_city_tree.h
 * In questo file vengono definite tutte le strutture, le funzioni
 * e le procedure che permettono di creare e manipolare alberi
 * contenenti le citta' presenti nel grafo con i relativi indici
 */
#ifndef ABR_CITY_TREE_H
#define ABR_CITY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#define MAX 50

struct abr{
    char city_name[MAX];
    int index;
    struct abr* dx;
    struct abr* sx;
};
typedef struct abr ABRcitytree;
typedef ABRcitytree* city_tree;

/*
 * restituisce 1 se l' ABR e' vuoto, 0 altrimenti
 */
int emptyCityTree(city_tree T);

/*
 * utilizzata per inserire il numero di elementi che deve contenere l'albero
 */
int insertCityTreeNumberOfElement();

/*
 * visualizzo prima la radice, poi il sottoalbero sinistro, infine il sottoalbero destro
 */
void preOrderCityTreeView(city_tree T);

/*
 * visualizzo prima il sottoalbero sinistro, poi la radice, infine il sottoalbero destro
 */
void inOrderCityTreeView(city_tree T);

/*
 * visualizzo prima il sottoalbero sinistro, poi il sottoalbero destro, infine la radice
 */
void postOrderCityTreeView(city_tree T);

/*
 * Alloca un nuovo nodo cittÃ  all'interno dell'ABR dato un nome di cittÃ  in input
 * e un campo index
 */
city_tree allocateNewCity(char city_name[], int index);

/*
 * inserisce un nodo nell'albero con un nome di cittÃ  e un index dati in input
 */
city_tree insertNewCityInABR(city_tree T, char city_name[], int index);

/*
 * restituisce il sottoalbero radicato nel nodo avente valore chiave uguale a
 * quello cercato (passato come parametro) se presente, altrimenti restituisce NULL
 */
city_tree searchCityInABR(city_tree T, char city_name[]);

/*
 * restituisce il numero di nodi dell'albero
 */
int countNumberOfCitiesInABR(city_tree T);

/*
 * elimina il nodo dall'albero con campo city_name
 */
city_tree deleteNode(city_tree T, char city_name[]);

/*
 * Data una cittaÂ in input restituisce il suo indice,
 * se l'indice restituito e' -1 la cittaÂ  non e' presente nel grafo
 */
int findIndexCity (city_tree T, char city_name[]);

/*
 * Funzione utilizzata per deallocare un ABR
 */
void freeABR(city_tree t);

#endif //ABR_CITY_TREE_H