/*
 * file : users.h
 * In questo file vengono definite tutte le funzioni e le procedure
 * che permettono agli utenti di svolgere le operazioni offerte
 */
#ifndef PROGETTO_USERS_H
#define PROGETTO_USERS_H

#include <math.h>
#include "user_tree.h"
#include "city_graph.h"

#define LOGIN 1
#define REGISTRAZIONE 2

/*
 * Questa funzione permette di leggere il file degli utenti e di inserirli
 * in un albero binario di ricerca.
 * Restituisce l'albero degli utenti se l'apertura del file va a buon fine,
 * altrimenti esce con codice -1
 */
usersTree createUsersTree(const char file[]);

/*
 * Funzione che permette di selezionare modalita di accesso utente:
 * 1 -> Login
 * 2 -> registrazione
 *
 * Digitando 0 invece si esce dalla modalita' utente in questione
 */
int selectUsersAccessMode();

/*
 * Funzione che permette di acquisire da atstiera le credenziali utente
 * e le restituisce in una struttura "user"
 */
user insertCredentials();

/*
 * Funzione che permette di effettuare il login dell'utente
 * Restituisce il nodo contenente l'utente che ha effettuato il login
 * Restituisce nella variabile error: 1 se il login va a buon fine,
 * 0 se la password e' sbagliata, -1 se l'utente non e' presente nel sistema
 */
usersTree login(user , usersTree tree, int *error);

/*
 * Funzione che permette di effettuare il logout di un utente
 */
void logout(usersTree user);

/*
 * Funzione che permette di selezionare l'operazione che l'utente vuole svolgere:
 * 1 = Visualizza prenotazioni attive,
 * 2 = Effettua prenotazione,
 * 3 = Viuslizza meta piu' gettonata
 * 4 = Viusalizza voli disponibili
 * 5 = Visualizza punti accumulati
 * 0 = Effettua il logout
 *
 * L'opzione 4 si divide in:
 *  - Voli disponibili da una determinata citta
 *  - Tutti i voli disponibili
 */
int usersMenu();

/*
 * Funzione che esegue una determinata operazione scelta da un utente
 */
void usersOperation(int operation, usersTree user, cityGraph airport);

/*
 * Procedura che permette di registrare un nuovo utente nel sistema
 * Nella variabile error viene ritornato 1 se l'inserimento subisce errori
 * 0 altrimenti.
 * L'utente viene iserito sia nell'albero degli utenti sia nel file degli utenti
 */
usersTree registration(usersTree t, char file[], int *error);

/*
 * Funzione utilizzata per gestire un utente che effettua un accesso ma non � registrato al sistema
 * Le opzioni offerte sono 2:
 * 1 -> abbandonare il login
 * 2 -> effettuare la registrazione
 */
usersTree manageUnregisteredUser(usersTree t, char file[]);

/*
 * Funzione che permette ad un amministratore di effettuare un'operazione:
 * 1 -> inserire nuova citta
 * 2 -> inserire nuova tratta
 * 3 -> rimuovere citta
 * 4 -> rimuovere tratta
 * 5 -> visualizzare utenti registrati
 * 6 -> visualizzare voli disponibili
 * 7 -> rimuovere un utente
 * 0 -> logout
 */
int adminMenu();

/*
 * Funzione che esegue una determinata funzione scelta da un amministratore
 */
void adminOperation(int operation, usersTree admin, usersTree *users, cityGraph airport);

/*
 * Durante l'esecuzione dell'applicativo, un utente puo' accumulare
 * nuovi punti, puo spendere i punti che possiede, oppure puo' essere
 * eliminato dal sistema.
 * Questa procedura permette di aggiornare il file degli utenti, in modo
 * che, alla prossima esecuzione dell'applicativo, le informazioni sugli
 * utenti risultino aggiornate all'ultima esecuzione
 */
void saveUsersChangesOnFile(char file[], usersTree users);

/*
 * Assegna dei punti all'utente (1 punto ogni 10 euro) in base ad una spesa fatta
 * passata in input "cost".
 */
void obtainPoints (usersTree p_user, double cost);

/*
 * Permette all'utente di pagare una somma, passata in input, percependo uno sconto
 * in base ai punti che possiede. Lo sconto è pari ad 1% per ogni punto, lo sconto
 * massimo applicabile è del 25%. Se i punti posseduti dall'utente sono meno di 25
 * allora verranno utilizzati tutti e sottratti poi all'utente, se i punti
 * dell'utente sono più di 25, ne verranno utilizzati 25 e poi ne saranno sottratti
 * altrettanti all'utente.
 * Viene ritornato il prezzo scontato o, se i punti sono 0, il prezzo di partenza.
 */
double payWithPoints (usersTree p_user, double flight_price);

/*
 * Funzione utilizzata dall'utente per effettuare una prenotazione
 *
 * Verra' chiesto come prima cosa di selezionare la citta di partenza da un
 * elenco di tutte le citta' presenti nel sistema. La selezione della citta'
 * avverra' digitando l'ID corrispondente, cioe' l'indice dell'array.
 *
 * A questo punto, il sitema chiedera se:
 * - inseire una citta di destinazione (selezionando da un elenco in cui non apparira la citta gia' scelta per la partenza)
 * - scegliere come destinazione la citta' piu' visitata (cioe' quella verso cui piu' utenti hanno gia viaggiao)
 * - scegliere la meta' piu' economica da ragiungere partendo dalla citta designata di partenza
 *
 * Nei primi due casi viene richiamato Dijkstra e viene chiesto all'utente se scegliere il perocorso di durata piu' breve
 * oppure quello piu' economico.
 * Nell'utlimo caso, il percorso sara' sicuramente un volo diretto e quindi non viene richiamato Dijkstra.
 *
 * Scelto il perocrso, viene mostrato un riepilogo della prenotazione all'utente e gli viene chiesto
 * se accettare o meno la prenotazione. In caso di risposta affermativa, in base ai punti posseduti,
 * gli viene chiesto se pagare con lo sconto offerto o rifiutare.
 * A pagamento avvenuto, vengono mostrati a video i nuovi punti guadagnati dall'utente.
 */
void makeBooking(cityGraph airport, usersTree user);

#endif //PROGETTO_USERS_H
