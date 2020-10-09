/*
 * File : city_graph.h
 *
 * In questo file vengono definite le strutture dati e le funzioni
 * per creare grafi di citta per rappresentare una mappa di tratte
 * aeree.
 *
 * In un grafo cosi definito, ogni vertice corrisponde ad una citta,
 * gli archi rappresentano una tratta aerea tra due citta, i pesi sugli
 * archi rappresentano il costo del viaggio e la relativa durata
 */
#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include "cityGraph_list.h"
#include "ABR_city_tree.h"
#include "utilities.h"
#include "priority_queue.h"

#define MINIMUM_DURATION 1
#define MINIMUM_COST 2

struct T_dist{
    double v;
    double v2;
};
typedef struct T_dist dijkstra_val;

struct city_vertex{
    char cityName[50];
    int popularity;
    cityList routes;
};
typedef struct city_vertex city;

struct T_city_graph{
    int numberOfCities;
    city* cities;
    city_tree cities_abr;
};
typedef struct T_city_graph city_graph;
typedef city_graph* cityGraph;

/*
 * Restituisce 1 se il grafo e' NULL, 0 altrimenti
 */
int isNullCityGraph(cityGraph g);

/*
 * Restituisce 1 se il grafo e' vuoto, 0 altrimenti.
 * Per vuoto si intende se e' NULL o se ha 0 vertici.
 */
int emptyCityGraph(cityGraph g);

/*
 * Crea ed inizializza un grafo, impostando il numero di citta a 0
 * e tutti gli elementi dell'array di adiacenza cities a NULL
 */
cityGraph initCityGraph();

/*
 * Funzione che restituisce il numero di citta attualmente presenti
 * nel grafo. Restituisce 0 se il grafo e' vuoto.
 */
int getNumbersOfCity(cityGraph g);

/*
 * Crea un grafo delle citta', prelevando le citta con la relativa
 * popolarita' da file.
 * Restituisce il grafo.
 */
cityGraph createCityGraphFromFile(char file[]);

/*
 * Inserisce all'interno del grafo g le tratte aeree salvate nel file
 * "file" relative a ciascun vertice (citta) di g
 */
void crerateAirRoutesFromFile(cityGraph g, char file[]);

/*
 * Funzione che crea il grafo, aggiungendo sia le citta che le
 * tratte dai relativi file
 */
cityGraph createAirport(char citiesFile[], char routesFile[]);

/*
 * stampa il grafo. Ogni arco sara' stampato nel formato (nomeCitta | costo / durataViaggio)
 * */
void printCityGraph(cityGraph g);

/*
 * Funzione utilizzata per deallocare il grafo
 *
 * Restituisce 1 se il grafo e' stato deallocato con successo
 * 0 altrimenti
 */
int freeCityGraph(cityGraph g);

/*
 * Funzione utilizzata per rimuovere una tratta dal grafo, specificando la prima
 * citta (departureCity) e la seconda(destinationCity).
 *
 * Restituisce 1 se la cancellazione va a buon fine, 0 altrimenti.
 */
int removeRoute(cityGraph g, char* departureCity, char* destinationCity);

/*
 * Funzione utilizzata per aggiungere una nuova tratta aerea all'interno del grafo,
 * specificando la coppia di citta' del grafo (citta di partenza, citta di destinazione).
 *
 * Restituisce 1 se l'inserimento va a buon fine, 0 altrimenti.
 */
int addRoute(cityGraph g, char* departureCity , char* destinationCity, double travelCost, double flighTime);

/*
 * Restituisce tutti i vertici adiacenti ad un vertice "departureCity" passato in input.
 * Questa funzione equivale a
 *
 * Nella variabile error viene restituito 0 se il vertice appartiene al grafo,
 * 1 se invece il vertice non appartiene al grafo (in questo caso, viene restituito NULL),
 * -1 se il grafo e' vuoto
 */
cityList flightRouteFromCity(cityGraph g, char* departureCity, int *error);

/*
 * Funzione utilizzata per verificare se esiste una tratta diretta da departureCity a
 * destinationCity.
 * Restituisce la tratta con prezzo e durata volo se e' presente, altrimenti NULL se:
 * - il grafo e' vuoto,
 * - almeno una delle due citta' non appartiene al grafo,
 * - non c'e' un volo diretto
 */
cityList thereIsDirectRoute(cityGraph g, char departureCity[], char destinationCity[]);

/*
 * Funzione che restituisce l'indice della tratta più economica partendo da una città.
 * Nella variabile price viene ritornato il prezzo della tratta.
 * Nella variabile duration viene restituito la durata della tratta.
 * Se da startCity non parte alcuna tratta o se il grafo e' vuoto, viene restituito -1.
 */
int findCheapest(cityGraph G,  int indexStartCity, double *price, double *duration);

/*
 * Funzione utilizzata per cercare la meta piu' gettonata.
 * Restituisce l'indice della meta piu' gettonata se il grafo non e' vuoto
 * altrimenti restituisce -1
 */
int mostPopular(cityGraph g);

/*
 * Funzione da utilizzare a fine esecuzione utilizzata per aggiornare
 * i file delle tratte e delle citta.
 * Questa funzione e' resa necessaria dal fatto che una citta', durante
 * l'esecuzione del programma, puo' amuentare la sua popolarit', oppure si
 * possonoa ggiungere e cancellare tratte e aggiungere e cancellare citta
 */
void updateFiles(cityGraph g, char citiesFile[], char routesFile[]);

/*
 * Funzione utilizzata per aggiungere una nuova citta (cioe' un nuovo vertice)
 * al grafo.
 * Restituisce 1 se l'inserimento va a buon fine, 0 se la citt'a e' gia presente nel grafo
 * e -1 se il grafo non e' stato inizializzato
 */
int insertNewCity(cityGraph g, char newCity[]);

/*
 * Funzione che pemrette di eliminare una citta (cioe' un vertice)
 * dal grafo.
 * Restituisce 1 se la rimozione va a buon fine, 0 altrimenti
 */
int removeCity(cityGraph g, char cityToRemove[]);

/*
 * Algoritmo di DIJKSTRA per il calcolo dei percorsi minimi a partire da un vertice
 * con valore "departureCity".
 * Viene restituito nell'array dist, le distanze del vertice departureCity verso
 * ogni altra citta' del grafo. Ogni citta' avra' un ID associato, cioe' l'indice
 * dell'array corrispondente. (ad esempio, il valore dist[2].v rappresenta la distanza
 * dalla citta departureCity alla citta' in posizione 2 dell'array del grafo).
 * Per distanza si intende: il costo minimo tra due citta se searchType = MINIMUM_COST,
 * oppure la durata di viaggio minima tra le due se searchType = MINIMUM_DURATION.
 * dist ha due campi:
 * v = il peso dell'arco su cui si sta richiamando Dijkstra
 * v = il secondo peso dell'arco.
 * In base al valore di searchType, dist.v conterra' il tempo minimo o il costo minimo,
 * dist.v2 conterra' invece la durata del viaggio, se il calcolo del percorso è fatto in
 * base al prezzo minimo, oppure il costo del viaggio se il calcolo del percorso è
 * fatto in base alla durata minima
 * Nell'array pred, con lo stesso meccanismo di dist, vengono restituiti i predecessori
 * di ogni vertice; a partire da departureCity quindi, in pred sara' descritto un albero
 * di vertici ragiungibili da departureCity (la componente conessa di departureCity),
 * departureCity sara' il vertice dell'albero.
 *
 * Gli array dist e pred vanno inizializzat prima di richiamare l'algoritmo, la loro
 * dimensione dovra' essere il numero di vertici presenti effettivamente nel grafo.
 *
 * Le distanze possono essere interpretrate in due modi, indicati dal parametro
 * searchType:
 *  - searchType = MINIMUM_DURATION, la distanza tra due vertici rappresenta la
 *                 durata del volo;
 *  - searchType = MINIMUM_COST, la distanza tra due vertici rappresenta il
 *                 costo del viaggio.
 *
 * Restituisce 0 se la ricerca va a buon fine, 1 altrimenti.
 */
int dijkstra(cityGraph g, int indexDepartureCity, dijkstra_val *dist, int *pred, int searchType);

#endif //CITY_GRAPH_H
