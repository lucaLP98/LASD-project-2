/*
 * file : priority_queue.h
 * Definizione di strutture dati, funzioni e procedure per
 * creare e manipolare code di priorita implementate con heap
 * alloro volta implementati con array.
 *
 * E' una coda di priorita' di tipo MIN, ovvero, l'elemento con maggiore
 * priorita' all'interno della coda e' quello con valore di "priority"
 * più basso.
 *
 * Nota bene:
 * Ogni elemento della coda di priorita deve essere in un caso
 * reale una coppia (chiave, valore), dove chiave è la priorita'
 * assegnata all'elemento valore.
 * In questa libreria, le chiavi sono valori interi.
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct T_item{
    double priority;
    int value;
};
typedef struct T_item item;

struct T_priority_queue{
    int size;
    item *heap;
};
typedef struct T_priority_queue *priorityQueue;

/*
 * Funzione utilizzata per restituire l'indice del figlio
 * sinistro dell'elemento di indice "index"
 */
int left(int index);

/*
 * Funzione utilizzata per restituire l'indice del figlio
 * destro dell'elemento di indice "index"
 */
int right(int index);

/*
 * Funzione che restituisce il nodo padre del nodo di indice index
 */
int father(int index);

/*
 * Ripristina la proprietà di Heap al sottoalbero radicto nella posizione
 * i assumendo che i suoi sottoalberi destro e sinistro siano già degli Heap
 */
void heapify(priorityQueue A, int index);

/*
 * Funzione utilizzata per creare un albero heap partendo da un generico
 * array A
 */
void buildHeap(priorityQueue A);

/*
 * Funzione che restituisce 1 se la coda è vuota, 0 altrimenti
 */
int isEmptyPriorityQueue(priorityQueue q);

/*
 * Funzione utilizzata per inizializzare una coda di
 * priorita' di "size" elementi
 */
priorityQueue initPriorityQueue(int heapSize);

/*
 * Proicedura utilizzata per stampare gli elementi
 * presenti in una coda di priorita'
 */
void printPriorityQueue(priorityQueue q);

/*
 * Funzione che ritorna il minimo elemento della coda
 * (quello a priorita' maggiore), senza pero estrarlo
 * dalla coda
 */
int minPriorityQueue(priorityQueue q);

/*
 * Funzione che ritorna il massimo elemento della coda
 * (quello a priorita' maggiore), estraendolo dalla stessa
 */
int exstractMinPriorityQueue(priorityQueue q);

/*
 * Funzione che permette di decrementare il valore di
 * priorita' dell'elemento di indice "index" al valore
 * "value"
 *
 * Ritorna 0 se il decremento va a buon fine, -1 altrimenti
 */
int decreaseKey(priorityQueue q, int index, double newPriority);

/*
 * Funzione che permette di incrementare il valore di
 * priorita' dell'elemento di indice "index" al valore
 * "value"
 *
 * Ritorna 0 se l'incremento va a buon fine, -1 altrimenti
 */
int increaseKey(priorityQueue q, int index, double newPriority);

/*
 * Funzione che permette di inserire un nuovo elemento
 * all'interno della coda di priorita'
 */
void insertNewElementInPriorityQueueu(priorityQueue q, int newValue , int priority);

/*
 * Funzione che dealloca una priorityQueue
 */
void freePriorityQueue(priorityQueue Q);

/*
 * Funzione che data una chiave key restituisce la sua posizione all'interno
 * della coda se l'elemento è presente, altrimenti -1.
 */
int getPositionOfKey(priorityQueue q, int key);

#endif //PRIORITY_QUEUE_H
