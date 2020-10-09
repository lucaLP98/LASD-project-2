/*
 *  file : user_tree.h
 *  In questo file vengono definite tutte le strutture dati, le funzioni e le procedure
 *  che permettono di manipolare utentu e alberi binari di ricerca di uteni
 */
#ifndef PROGETTO_USER_TREE_H
#define PROGETTO_USER_TREE_H

#include "booking_list.h"

#define ONLINE 1
#define OFFLINE 0

//DEFINIZIONE STRUTTURA UTENTE
struct T_user{
    char username[50];
    char password[50];
    int points;
    int status;
    bookingsList Bookings;
};
typedef struct T_user user;

//DEFINIZIONE STRUTTURA PER ABR DI UTENTI
struct T_abrUsers{
    user User;

    struct T_abrUsers* dx;
    struct T_abrUsers* sx;
};
typedef struct T_abrUsers ABRusers;
typedef ABRusers* usersTree;

//DEFINIZIONE DI FUNZIONI E PROCEDURE PER LA MANIPOLAZIONE DI UN ABR DI UTENTI

/*
 * Inizializza un albero di studenti
 */
usersTree initUsersTree();

/*
 * Funzione che restituisce 1 se l'albero degli studenti e' vuoto, 0 altrimenti
 */
int emptyUsersTree(usersTree t);

/*
 * Procedura che stampa un utente nella forma:
 * nome utente  punti accumulati
 * prenotazioni attive
 */
void printUsers(user utente);

/*
 * stampa l'albnero degli utenti mediante un algoritmo del tipo inOrder
 * (stampando quindi in ordine alfabetico)
 */
void inOrderViewUsers(usersTree t);

/*
 * Crea un nuovo nodo Utente specificando username e password e
 * lo restituisce al chiamante
 */
usersTree allocateNewNodeUsers(char newUser[], char newPassword[], int points);

/*
 * Inserisce un nuovo utente nell'albero e restituisce l'albero modificato
 */
usersTree insertNewUser(usersTree t, char newUsername[], char newPassword[], int points);

/*
 * cerca un utente nell'albero tramite il campo username
 * e restituisce il sottoalbero avente come radice il nodo del utente cercato.
 * Restituisce NULL se non c'e' nessun utente associato al username data in input
 */
usersTree searchUsers(usersTree t, char username[]);

/*
 * Funzione utilizzata da un amministratore per eliminare un utente dal sisetma.
 * Viene restituito nella variabile error 1 se la cancellazione e' andata a buon fine,
 * 0 altrimenti
 */
usersTree deleteUser(usersTree T, char username[], int* err);

#endif //PROGETTO_USER_TREE_H
