/*
 * File : city_graph.c
 *
 * In questo file vengono implementate tutte le funzioni che permettono di
 * manipolare un grafo di citta
 */
#include "city_graph.h"

/*
 * Numero massimo di citta inseribili.
 * Se il numero di citta' inserite supera MAX_NUMBER_OF_CITY,
 * allora quest'ultimo viene raddoppiato. In questo modo, si
 * le chiamate alla funzione realloc (inefficiente) sono ridotte
 * al minimo
 */
int MAX_NUMBER_OF_CITY = 200;

int isNullCityGraph(cityGraph g){
    return g == NULL;
}

int emptyCityGraph(cityGraph g){
    return (isNullCityGraph(g) || g->numberOfCities == 0);
}

cityGraph initCityGraph(){
    cityGraph tmp = (cityGraph)malloc(sizeof(city_graph));
    tmp->numberOfCities = 0;
    tmp->cities = (city *)calloc(MAX_NUMBER_OF_CITY, sizeof(city));
    tmp->cities_abr = NULL;

    return tmp;
}

int getNumbersOfCity(cityGraph g){
    int ret;

    if(!emptyCityGraph(g))   ret = g->numberOfCities;
    else    ret = 0;

    return ret;
}

cityGraph createCityGraphFromFile(char file[]){
    cityGraph g;
    FILE *fPtr;
    char buffCityName[50];
    int buffCityPopularity;

    if((fPtr = fopen(file, "r")) == NULL){
        printf("\n\n ERRORE APERTURA FILE %s\n\n", file);
        exit(-1);
    }

    g = initCityGraph();
    while(fscanf(fPtr, "%s %d", buffCityName, &buffCityPopularity) > 0){
        g->cities[g->numberOfCities].popularity = buffCityPopularity;
        strcpy(g->cities[g->numberOfCities].cityName, buffCityName);
        g->cities[g->numberOfCities].routes = initList();

        g->cities_abr = insertNewCityInABR(g->cities_abr, buffCityName, g->numberOfCities);

        g->numberOfCities += 1;
    }
    fclose(fPtr);

    return g;
}

void crerateAirRoutesFromFile(cityGraph g, char file[]){
    FILE* fPtr;
    char buffDepartureCity[50], buffDestinationCity[50];
    double buffCost, buffTime, time_in_minutes;
    int error, index;

    if((fPtr = fopen(file, "r")) == NULL){
        printf("\n\n\n ERRORE APERTURA FILE %s\n\n\n", file);
        exit(-1);
    }

    while(fscanf(fPtr, "%s %s %lf %lf", buffDepartureCity, buffDestinationCity, &buffCost, &buffTime) > 0){
        time_in_minutes = hourstominutes(buffTime);

        if ((index = findIndexCity(g->cities_abr, buffDepartureCity)) != -1)
            g->cities[index].routes = insertNewRoutesInTail(g->cities[index].routes, buffDestinationCity, buffCost, time_in_minutes, &error);
    }
    fclose(fPtr);
}

cityGraph createAirport(char citiesFile[], char routesFile[]){
    cityGraph g;

    g = createCityGraphFromFile(citiesFile);
    crerateAirRoutesFromFile(g, routesFile);

    return g;
}

void printCityGraph(cityGraph g) {
    printf("\n Le tratte aeree presenti sono :\n");

    if (!(emptyCityGraph(g))) {
        int i;

        for (i = 0; i < g->numberOfCities; i++) {
            printf("\n Citta di Partenza %s, ", g->cities[i].cityName);
            printList(g->cities[i].routes);
        }
    }else{
        printf("\n Non ci sono tratte aeree disponibili...\n");
    }
}

int freeCityGraph(cityGraph g) {
    int ret;

    if (!(emptyCityGraph(g))) {
        for (int i = 0; i < g->numberOfCities; i++)
            freeList(g->cities[i].routes);

        freeABR(g->cities_abr);
        free(g->cities);
        free(g);

        ret = 1;
    }
    else{
        ret = 0;
    }

    return ret;
}

int removeRoute(cityGraph g, char* departureCity, char* destinationCity){
    int index, error;

    if(emptyCityGraph(g)){
        printf("\n\n ERRORE ! Il grafo è vuoto\n Inizializzare il grafo prima di rimuovere l'arco\n");
        return 0;
    }

    if(strcmp(departureCity, destinationCity) == 0){
        printf("\n ERRORE ! La citta' di partenza e di destinazione coincidono (impossibilie!)\n");
        return 0;
    }

    if((index = findIndexCity(g->cities_abr, departureCity)) == -1) {
        printf("\n\n ERRORE ! %s non presente nel grafo,\n aggiungere il vertice prima di rimuovere questo arco\n" ,departureCity);
    }else if(searchCityInABR(g->cities_abr, destinationCity) == NULL) {
        printf("\n\n ERRORE ! %s non presente nel grafo,\n aggiungere il vertice prima di rimuovere questo arco\n" ,destinationCity);
    }else{
        g->cities[index].routes = deleteRoutesToList(g->cities[index].routes, destinationCity, &error);
        if(error == 0)
            printf("\n\n TRATTA %s - %s ELIMINATA CON SUCCESSO !\n", departureCity, destinationCity);
    }

    return ((index != -1) && (error == 0));
}

int addRoute(cityGraph g, char* departureCity , char* destinationCity, double travelCost, double flighTime){
    int error, index;

    if (emptyCityGraph(g)){
        printf("\n\n ERRORE ! Il grafo e' vuoto\n Inizializzare il grafo prima di aggiungere l'arco\n");
        return 0;
    }

    if(strcmp(departureCity, destinationCity) == 0){
        printf("\n\n ERRORE !\n La citta' di partenza e di destinazione coincidono (impossibilie!)\n");
        return 0;
    }

    if((index = findIndexCity(g->cities_abr, departureCity)) == -1) {
        printf("\n\n ERRORE ! %s non presente nel grafo,\n aggiungere il vertice prima di rimuovere questo arco\n" ,departureCity);
    }else if(searchCityInABR(g->cities_abr, destinationCity) == NULL) {
        printf("\n\n ERRORE ! %s non presente nel grafo,\n aggiungere il vertice prima di rimuovere questo arco\n" ,destinationCity);
    }else {
        g->cities[index].routes = insertNewRoutesInTail(g->cities[index].routes, destinationCity, travelCost, flighTime, &error);
        if(error == 0)
            printf("\n\n TRATTA %s - %s INSERITA CON SUCCESSO !\n", departureCity, destinationCity);
        else
            printf("\n\n TRATTA %s - %s GIA' PRESENTE !\n INSERIMENTO ANNULLATO...\n", departureCity, destinationCity);
    }

    return ((index != -1) && (error == 0));
}

cityList flightRouteFromCity(cityGraph g, char* departureCity, int *error){
    cityList tmp;
    int index;

    if(!emptyCityGraph(g)){
        index = findIndexCity(g->cities_abr, departureCity);

        if(index == -1)  tmp = NULL;
        else    tmp = g->cities[index].routes;

        *error = (index == -1);
    }else{
        *error = -1;
    }

    return tmp;
}

cityList thereIsDirectRoute(cityGraph g, char departureCity[], char destinationCity[]){
    cityList cur, res;
    int index;

    if(!emptyCityGraph(g)){
        if((index = findIndexCity(g->cities_abr, departureCity)) != -1 && searchCityInABR(g->cities_abr, destinationCity) != NULL){
            cur = g->cities[index].routes;
            while(cur != NULL && res == NULL){
                if(strcmp(cur->cityName, destinationCity) == 0)
                    res = cur;
                else
                    cur = cur->next;
            }
        }else  res = NULL;
    } else res = NULL;

    return res;
}

int findCheapest(cityGraph G, int indexStartCity, double *price, double *duration){
    int index;
    cityList cur, min;

    cur = G->cities[indexStartCity].routes;
    if(cur) {
        min = cur;
        cur = cur->next;
        while (cur) {
            if (cur->travelCost < min->travelCost)
                min = cur;

            cur = cur->next;
        }
        *price = min->travelCost;
        *duration = min->flighTime;
        index = findIndexCity(G->cities_abr, min->cityName);
    }else{
        index = -1;
    }

    return index;
}

int mostPopular(cityGraph g){
    int indexOfMostPopular, i;

    if(!emptyCityGraph(g)){
        indexOfMostPopular = 0;
        for(i=1;i<g->numberOfCities;i++)
            if (g->cities[i].popularity > g->cities[indexOfMostPopular].popularity)
                indexOfMostPopular = i;
    } else
        indexOfMostPopular = -1;

    return indexOfMostPopular;
}

void updateFiles(cityGraph g, char citiesFile[], char routesFile[]){
    FILE *cittaPtr, *trattePtr;
    int i;
    double time_in_hours;
    cityList cursor;

    if((cittaPtr = fopen(citiesFile, "w")) != NULL && (trattePtr = fopen(routesFile, "w")) != NULL){
        for(i=0;i<g->numberOfCities;i++){
            fprintf(cittaPtr, "%s %d\n", g->cities[i].cityName, g->cities[i].popularity);

            cursor = g->cities[i].routes;
            while(cursor != NULL){
                time_in_hours = minutesToHours(cursor->flighTime);
                fprintf(trattePtr, "%s %s %.2f %.2f\n", g->cities[i].cityName, cursor->cityName, cursor->travelCost, time_in_hours);
                cursor = cursor->next;
            }
        }

        fclose(cittaPtr);
        fclose(trattePtr);
    }else{
        printf("\n\n ERRORE AGGIORNAMENTO FILE\n\n");
        exit(-1);
    }
}

int insertNewCity(cityGraph g, char newCity[]){
    if(isNullCityGraph(g)) {
        return -1;
    }

    if(searchCityInABR(g->cities_abr, newCity) != NULL) {
        printf("\n\n ATTENZIONE ! Citta' %s gia' presente nel sistema\n Inserimento annullato...\n\n", newCity);
        return 0;
    }

    if(g->numberOfCities == MAX_NUMBER_OF_CITY){
        MAX_NUMBER_OF_CITY *= 2;
        g->cities = (city *)realloc(g->cities, MAX_NUMBER_OF_CITY * sizeof(city));
    }

    g->numberOfCities += 1;
    strcpy(g->cities[g->numberOfCities - 1].cityName, newCity);
    g->cities[g->numberOfCities - 1].popularity = 0;
    g->cities_abr = insertNewCityInABR(g->cities_abr, newCity, g->numberOfCities - 1);
    printf("\n\n CITTA %s INSERITA CON SUCCESSO !\n", newCity);

    return 1;
}

int removeCity(cityGraph g, char cityToRemove[]){
    int index, error;

    if(emptyCityGraph(g) || (index = findIndexCity(g->cities_abr, cityToRemove)) == -1) {
        printf("\n\n ATTENZIONE ! Citta' %s non presente nel sistema\n\n", cityToRemove);
        return 0;
    }

    freeList(g->cities[index].routes);
    if(index != g->numberOfCities - 1){
        g->cities[index].routes = g->cities[g->numberOfCities - 1].routes;
        g->cities[index].popularity = g->cities[g->numberOfCities - 1].popularity;
        strcpy(g->cities[index].cityName, g->cities[g->numberOfCities - 1].cityName);
        searchCityInABR(g->cities_abr, g->cities[index].cityName)->index = index;
    }
    g->numberOfCities -= 1;

    for(int i=0;i<g->numberOfCities;i++)
        g->cities[i].routes = deleteRoutesToList(g->cities[i].routes, cityToRemove, &error);

    g->cities_abr = deleteNode(g->cities_abr, cityToRemove);
    printf("\n\n CITTA %s RIMOSSA CON SUCCESSO !\n", cityToRemove);

    return 1;
}

/*
 * Funzione di inizializzazione array pred (predecessori) e dist(stima distanze)
 * utilizzati dall'Algoritmo Dijkstra
 */
void initArrayDijkstra(cityGraph g, int s, int *pred, dijkstra_val *dist){
    if(!emptyCityGraph(g)){
        int i;

        for(i=0;i<g->numberOfCities;i++){
            //Inizializzo i valori nell'array dei predecessori a -1
            //dato che questo valore non identifica nessun ID vertice (ID >= 0)
            pred[i] = -1;
            //inizializzo le distanze ad un numero sicuramente maggiore di quelle presenti nel grafo
            dist[i].v = (double)9999999;
            dist[i].v2 = (double)9999999;
        }

        dist[s].v = 0; //la stima di distanza della sorgente di visita (s) viene posta a 0
        dist[s].v2 = 0; //stima per il secondo peso dell'arco
    }
}

/*
 * Funzione di Relax utilizzata dall'algoritmo Dijkstra
 */
void Relax_Dijkstra(priorityQueue Q, int *pred, dijkstra_val *dist, int u, int v, double weight, double weight2){
    int pos;

    if(dist[v].v > dist[u].v + weight){
        dist[v].v = dist[u].v + weight;
        dist[v].v2 = dist[u].v2 + weight2;
        pred[v] = u;

        //Aggiorna coda di priorità
        pos = getPositionOfKey(Q, v);
        increaseKey(Q, pos, dist[v].v);
    }
}


int dijkstra(cityGraph g, int indexDepartureCity, dijkstra_val *dist, int *pred, int searchType){
    // pred = array dei predesecessori
    // dist = della stima delle distanze minime
    int i, v, u, error;
    double weight, weight2;
    cityList adj = NULL;
    priorityQueue Q = NULL;

    if(!emptyCityGraph(g)){
        //controllo che esista almeno un volo partente da departureCity
        if(g->cities[indexDepartureCity].routes == NULL)     return -1;

        //Allocazione coda di priorità
        Q = initPriorityQueue(g->numberOfCities);

        //Inizializzazione degli arrat dist e pred
        initArrayDijkstra(g, indexDepartureCity, pred, dist);

        //Inserimento vertici in coda di priorità Q
        for(i = 0; i < g->numberOfCities; i++){
            //Inserisce in coda di priorità gli ID dei vertici,
            //cioe' gli indici corrispondenti ad ogni vertice
            if(g->cities[i].routes)
                insertNewElementInPriorityQueueu(Q, i, dist[i].v);
        }

        while(!isEmptyPriorityQueue(Q)){
            //Viene estratto l'elemento dalla coda con il minimo valore di priorità (valore dist)
            u = exstractMinPriorityQueue(Q);

            //Ricava i vertici adiacenti al vertice u, cioe' i voli diretti che partono dalla citta di indice u
            adj = g->cities[u].routes;

            while(adj != NULL){     //Per ogni vertice v adiacente a u
                //Ricava l'ID dell'adiacente adj
                v = findIndexCity(g->cities_abr, adj->cityName);

                //Ricava il peso dell'arco che va dal vertice u al vertice v
                if(searchType == MINIMUM_COST){
                    weight = adj->travelCost;
                    weight2 = adj->flighTime;
                }else{
                    weight = adj->flighTime;
                    weight2 = adj->travelCost;
                }

                //Rilassamento arco che va dal vertice u al vertice v con peso weight
                Relax_Dijkstra(Q, pred, dist, u, v, weight, weight2);

                //Avanza al prossimo adiacente se esiste, altrimenti adj sarà NULL
                adj = adj->next;
            }
        }
        //Deallocazione strutture utilizzate dalla visita
        freePriorityQueue(Q);

        error = 0;
    }else   error = 1;

    return error;
}
