/*
 * file : users.h
 */
#include "users.h"

usersTree createUsersTree(const char file[]){
    FILE *fPtr;
    user userBuff;
    usersTree tmp;

    if((fPtr = fopen(file, "r")) == NULL) {
        printf("\n Errore apertura file...\n");
        exit(-1);
    }

    tmp = initUsersTree();

    while(fscanf(fPtr, "%s %s %d", userBuff.username, userBuff.password, &userBuff.points) > 0){
        tmp = insertNewUser(tmp, userBuff.username, userBuff.password, userBuff.points);
    }
    fclose(fPtr);

    return tmp;
}

int selectUsersAccessMode(){
    int tmp;

    printf("\n Selezionare un'opzione valida e premere INVIO\n\n  > 1. Login\n  > 2. Registrazione\n  > 0. Esci\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &tmp);
        if(tmp < 0 || tmp > 2)
            printf("\n ERRORE ! Opzione non valida\n\n Riprovare");
    }while(tmp < 0 || tmp > 2);

    return tmp;
}

user insertCredentials(){
    user tmp;

    printf("\n  - Inserire il nome utente : ");
    scanf("%s", tmp.username);
    printf("\n  - Inserire la password : ");
    scanf("%s", tmp.password);

    return tmp;
}

usersTree login(user utente, usersTree tree, int *error){
    usersTree user = searchUsers(tree, utente.username);

    if(user != NULL){
        if(strcmp(user->User.password, utente.password) == 0){
            *error = 1;
            user->User.status = ONLINE;
            printf("\n Login effettuato con SUCCESSO !\n\n\t\t\t ********* Benvenuto nella nostra Compagnia aerea ! *********\n\n");
            printf("\n Premere INVIO per tornare al MENU\n"); getchar(); getchar();
            system("clear");
        }else{
            *error = 0;
            printf("\n ACCESSO NEGATO ! Password errata...\n");
        }
    }else{
        *error = -1;
        printf("\n ERRORE ! Utente non presente nel sistema...\n");
    }

    return user;
}

void logout(usersTree user){
    int tmp;

    printf("\n Sicuro di voler effettuare il logout ?\n\n  > 1. SI\n  > 2. NO\n\n ");
    do{
        printf(" >>> ");
        scanf("%d", &tmp);
        if(tmp < 1 || tmp > 2)
            printf("\n ERRORE ! Scelta non valida...\n\n Riprovare");
    }while(tmp < 1 || tmp > 2);

    if(tmp == 1){
        user->User.status = OFFLINE;
        printf("\n\n Logout effettuato con successo !\n\n\t\t\t ********* Grazie per avre viaggiato con noi ! *********\n\n");
    }else{
        system("clear");
    }
}

usersTree registration(usersTree t, char file[], int *error){
    char newUsername[50], newPsw1[50], newPsw2[50];
    FILE *fPtr;

    regScreen();
    printf("\n - Inserire un username (una sola parola) e premere INVIO : ");
    scanf("%s", newUsername);

    if(searchUsers(t, newUsername) != NULL){
        printf("\n\n UTENTE GIA' PRESENTE NEL SISTEMA\n\n");
        *error = 1;
    }else{
        do{
            printf("\n\n - Inserire un password e premere INVIO : ");
            scanf("%s", newPsw1);

            printf("\n\n - Ripetere la password e premere INVIO : ");
            scanf("%s", newPsw2);

            if(strcmp(newPsw1, newPsw2) != 0)
                printf("\n\n ERRORE ! Le password non coincidono\n\n Riprovare...");
        }while((strcmp(newPsw1, newPsw2) != 0));

        if((fPtr = fopen(file, "a")) == NULL){
            printf("\n\n ERRORE REGISTRAZIONE UTENTE\n\n");
            *error = 1;
        }else{
            fprintf(fPtr, "%s %s %d\n", newUsername, newPsw1, 0);
            fclose(fPtr);

            t = insertNewUser(t, newUsername, newPsw1, 0);
            printf("\n\n\t\t\t *********** REGISTRAZIONE AVVENUTA CON SUCCESSO ! ***********\n");
            *error = 0;
        }
    }

    return t;
}

usersTree manageUnregisteredUser(usersTree t, char file[]){
    int tmp;

    printf("\n\n Vuoi registrarti adesso ?\n\n  > 1. SI\n  > 2. NO\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &tmp);
        if(tmp < 1 || tmp > 2)
            printf("\n\n ERRORE ! Scelta non valida !\n\n Riprovare");
    }while(tmp < 1 || tmp > 2);

    if(tmp == 1){
        system("clear");
        int error;
        t = registration(t, file, &error);
    }

    return t;
}

int usersMenu(){
    int tmp;

    printf("\n Inserire l'operazione da svolgere\n\n  > 1. Visualizza prenotazioni attive\n  > 2. Effettua prenotazione\n  > 3. Visualizza meta piu' gettonata\n  > 4. Visualizza voli disponibili\n  > 5. Visualizza punti accumulati\n  > 0. Logout\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &tmp);
        if(tmp < 0 || tmp > 5)
            printf("\n ERRORE ! Opzione non valida\n\n Riprovare");
    }while(tmp < 0 || tmp > 5);

    return tmp;
}

void usersOperation(int operation, usersTree user, cityGraph airport){
    int tmp;
    char city[50];

    switch(operation){
        case 1: //VISUALIZZAZIONE PRENOTAZIONI ATTIVE
            printBookingsList(user->User.Bookings, user->User.username);

            clearScreen();
        break;

        case 2: //INSERIMENTO NUOVA PRENOTAZIONE
            makeBooking(airport, user);

            clearScreen();
        break;

        case 3: //VISUALIZZAZIONE META PIU' GETTONATA
            tmp = mostPopular(airport);
            printf("\n\n La meta piu' gettonata e' : %s\n\n %d utenti hanno gia' viaggiato verso questa citta'\n", airport->cities[tmp].cityName, airport->cities[tmp].popularity);

            clearScreen();
        break;

        case 4: //VISUALIZZAZIONE VOLI DISPONIBILI
            printf("\n - Effettuare una scelta digitando il codice corrispondente e premere INVIO\n\n    > 1. Visualizza tutti i voli disponibili\n    > 2. Visualizza i voli diretti disponibili da una citta'\n\n ");
            do{
                printf("  >>> ");
                scanf("%d", &tmp);
                if(tmp < 1 || tmp > 2)
                    printf("\n ERRORE ! Inserire una scelta valita...\n\n - Riprovare");
            }while(tmp < 1 || tmp > 2);

            if(tmp == 1){
                system("clear");
                printCityGraph(airport);
            }else{
                printf("\n - Inserire il nome della citta' (senza spazi) e premere INVIO >>> ");
                scanf("%s", city);

                if((tmp = findIndexCity(airport->cities_abr, city)) != -1){
                    printf("\n\n Citta' di partenza %s,", city);
                    printList(airport->cities[tmp].routes);
                }else
                    printf("\n\n La nostra compagnia non possiede scali in questa citta'.\n");
            }

            clearScreen();
        break;

        case 5:
            printf("\n\n\t\t\t************** HAI ACCUMULATO %d PUNTI **************\n\n", user->User.points);
            clearScreen();
        break;

        //LOGOUT UTENTE
        case 0: logout(user); break;
    }
}

int adminMenu(){
    int tmp;

    printf("\n Inserire l'operazione da svolgere\n\n  > 1. Inserire nuova citta'\n  > 2. Inserire nuova tratta\n  > 3. Rimuovere citta'\n  > 4. Rimuovere tratta\n  > 5. Visualizza utenti registrati\n  > 6. Visualizza voli disponibili\n  > 7. Elimina un utente\n  > 0. Logout\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &tmp);
        if(tmp < 0 || tmp > 7)
            printf("\n ERRORE ! Opzione non valida\n\n Riprovare");
    }while(tmp < 0 || tmp > 7);

    return tmp;
}

void adminOperation(int operation, usersTree admin, usersTree *users, cityGraph airport){
    char city[50], departureCity[50], destinationCity[50], username[50];
    int tmp;
    int err = 0;
    double travelCost, travelTime;

    switch(operation){
        case 1: //AGGIUNTA NUVA CITTA
            printf("\n - Inserire il nome della nuova citta' (senza spazi) e premere INVIO >>> ");
            scanf("%s", city);

            insertNewCity(airport, stringLower(city));

            clearScreen();
        break;

        case 2: //AGGIUNTA NUOVA TRATTA AEREA
            printf("\n - Inserire la citta di partenza (senza spazi) e premere INVIO >>> ");
            scanf("%s", departureCity);

            printf("\n - Inserire la citta di destinazione (senza spazi) e premere INVIO >>> ");
            scanf("%s", destinationCity);

            printf("\n - Inserire il costo del volo e premere INVIO");
            do{
                printf(" >>> ");
                scanf("%lf", &travelCost);
                if(travelCost <= 0)
                    printf("\n ERRORE ! Costo inferiore o uguale a 0\n\n - Riprovare");
            }while(travelCost <= 0);

            printf("\n - Inserire la durata del volo e premere INVIO");
            do{
                printf(" >>> ");
                scanf("%lf", &travelTime);
                if(travelTime <= 0)
                    printf("\n ERRORE ! Durata volo inferiore o uguale a 0\n\n - Riprovare");
            }while(travelTime <= 0);
            printf("\n  - Il tempo inserito e' in :\n\n    > 1. Ore\n    > 2. Minuti\n\n   ");
            do{
                printf(" >>> ");
                scanf("%d", &tmp);
                if(tmp < 1 || tmp > 2)
                    printf("\n ERRORE ! Inserire una scelta valita...\n\n    Riprovare");
            }while(tmp < 1 || tmp > 2);
            if(tmp == 1)
                travelTime = hourstominutes(travelTime);

            addRoute(airport, stringLower(departureCity) , stringLower(destinationCity),travelCost, travelTime);

            clearScreen();
        break;

        case 3: //RIMOZIONE CITTA
            printf("\n - Inserire il nome della citta' da eliminare (senza spazi) e premere INVIO >>> ");
            scanf("%s", city);

            printf("\n - Sei sicuro di voler eliminare %s ?\n   La cancellazione provochera la rimozione di tutte le tratte da e per qiesta citta\n\n  > 1. SI\n  > 2. NO\n\n", city);
            do{
                printf(" >>> ");
                scanf("%d", &tmp);
                if(tmp < 1 || tmp > 2)
                    printf("\n ERRORE ! Inserire una scelta valita...\n\n - Riprovare");
            }while(tmp < 1 || tmp > 2);

            if(tmp == 1)
                removeCity(airport, city);
            else
                printf("\n\n RIMOZIONE %s ANNULLATA !\n", city);

            clearScreen();
        break;

        case 4: //RIMOZIONE TRATTA AEREA
            printf("\n - Inserire citta di partenza >>> ");
            scanf("%s", departureCity);
            printf("\n - Inserire citta di destinazione >>> ");
            scanf("%s", destinationCity);

            printf("\n - Sei sicuro di voler eliminare la tratta %s - %s ?\n\n  > 1. SI\n  > 2. NO\n\n", departureCity, destinationCity);
            do{
                printf(" >>> ");
                scanf("%d", &tmp);
                if(tmp < 1 || tmp > 2)
                    printf("\n ERRORE ! Inserire una scelta valita...\n\n - Riprovare");
            }while(tmp < 1 || tmp > 2);

            if(tmp == 1)
                removeRoute(airport, departureCity, destinationCity);
            else
                printf("\n\n RIMOZIONE TRATTA %s - %s ANNULLATA !\n", departureCity, destinationCity);

            clearScreen();
        break;

        case 5: //VISUALIZZAZIONE UTENTI ISCRITTI AL SISTEMA
            if(emptyUsersTree(*users))
                printf("\n Non ci sono utenti iscritti al sistema");
            else{
                printf("\n\n Gli utenti attualmente iscritti nel sistema sono :\n");
                inOrderViewUsers(*users);
            }

            clearScreen();
        break;

        case 6: //VISUALIZZAZIONE VOLI DISPONIBILI
            system("clear");
            printCityGraph(airport);

            clearScreen();
        break;

        case 7: //ELIMINAZIONE UTENTE
            printf("\n - Inserire username dell'utente da eliminare >>> ");
            scanf("%s", username);
            *users = deleteUser(*users, username, &err);
            if(err) printf("\n\n *********** Eliminazione avvenuta con successo ! ***********\n\n");
            else    printf("\n\n IMPOSSIBILE COMPLETARE L'OPERAZIONE : Utente non trovato!\n\n");

            clearScreen();
        break;


        //LOGOUT AMMINISTRATORE
        case 0: logout(admin); break;
    }
}

void updateFile(FILE *fPtr, usersTree users){
    if(!emptyUsersTree(users)){
        updateFile(fPtr, users->sx);
        fprintf(fPtr, "%s %s %d\n", users->User.username, users->User.password, users->User.points);
        updateFile(fPtr, users->dx);
    }
}

void saveUsersChangesOnFile(char file[], usersTree users){
    FILE *filePtr;

    if((filePtr = fopen(file, "w")) != NULL){
        updateFile(filePtr, users);
        fclose(filePtr);
    }else{
        printf("\n ERRORE AGGIORNAMENTO FILE\n");
        exit(-1);
    }
}

int selectCity(cityGraph g, char msg[], int noChoice){
    int index;

    printf("\n > Selezionare la citta' di %s digitando il relativo codice e premere INVIO\n", msg);
    for(int i = 0; i < g->numberOfCities; i++)
        if(i != noChoice)
            printf("\n\t%d. %s", i, g->cities[i].cityName);

    printf("\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &index);
        if(index < 0 || index >= g->numberOfCities || index == noChoice)
            printf("\n\n ATTENZIONE ! Codice non valido\n\n Riprovare");
    }while(index < 0 || index >= g->numberOfCities || index == noChoice);

    return index;
}

void obtainPoints (usersTree p_user, double cost) {
    int points;

    points = floor(cost/10);
    printf ("\n Hai ottenuto %d punti!\n", points);
    p_user->User.points += points;

}

double payWithPoints (usersTree p_user, double flight_price) {
    double discount, points, discounted_price;

    discounted_price = flight_price;
    points = p_user->User.points;

    if (p_user->User.points == 0) {
        printf ("\n L'utente non ha punti, impossibile applicare uno sconto.\n");
    }
    else if (p_user->User.points <= 25) {
        discount = (points/100) * flight_price;
        p_user->User.points = 0;
    }
    else {
        discount = (25.00/100.00) * flight_price;
        p_user->User.points -= 25;
    }
    discounted_price = flight_price - discount;

    if (discounted_price != flight_price)
        printf ("\n Il prezzo scontato e' %.2lf avendo applicato uno sconto di %.2lf euro\n\n I punti rimanenti sono %d\n", discounted_price,  discount, p_user->User.points);

    return discounted_price;
}

void makeBooking(cityGraph airport, usersTree user){
    int selection, indexDepartureCity, indexDestinationCity;
    int *pred;
    dijkstra_val *dist;
    double discounted_price;
    booking userBooking;

    printf("\n\n\t\t\t\t IN QUESTA SEZIONE E' POSSIBILE EFFETTUARE UNA PRENOTAZIONE\n\n");

    //SELEZIONE CITTA DI PARTENZA
    indexDepartureCity = selectCity(airport, "partenza", -1);

    //VERIFICO CHE CI SIANO VOLI CHE PARTONO DALLA CITTA' DESIGNATA COME PARTENZA
    if(airport->cities[indexDepartureCity].routes == NULL){
        printf("\n\n ATTENZIONE ! Non ci sono voli che partono da %s\n\n", airport->cities[indexDepartureCity].cityName);
        return;
    }

    system("clear");
    printf("\n\n Citta' di partenza : %s\n", airport->cities[indexDepartureCity].cityName);

    //SELEZIONARE META DI DESTINAZIONE
    printf("\n\n > Vuoi volare verso ?\n\n\t1. Seleziona una citta' di destinazione\n\t2. Meta piu' gettonata\n\t3. Meta piu' economica\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &selection);
        if(selection < 1 || selection > 3)
            printf("\n\n ATTENZIONE ! Scelta non valido\n\n Riprovare");
    }while(selection < 1 || selection > 3);

    printf("\n");
    switch(selection){
        //SELEZIONO CITTA' DI DESTINAZIONE
        case 1: indexDestinationCity = selectCity(airport, "destinazione", indexDepartureCity); break;

        //CERCO LA CITTA' PIU' POPOLARE
        case 2: indexDestinationCity = mostPopular(airport); break;

        //CERCO LA CITTA' CON LA TRATTA PIU' ECONOMICA PARTENDO DA
        case 3: indexDestinationCity = findCheapest(airport, indexDepartureCity, &userBooking.travelCost, &userBooking.travelDuration); break;
    }

    system("clear");
    printf("\n\n Citta' di partenza : %s\n", airport->cities[indexDepartureCity].cityName);
    printf("\n Citta' di destinazione sara' : %s\n", airport->cities[indexDestinationCity].cityName);

    //SELEZIONO MODALITA' DI RICERCA PERCORSO NEL CASO IN CUI
    //LA CITTA' DI DESTINAZIONE NON SIA QUELLA CON TRATTA PIU' ECONOMICA
    if(selection != 3){
        printf("\n\n Selezionare la modalita' di calcolo della rotta e premere INVIO\n\n\t1. Cerca percorso piu' economico\n\t2. Cerca percorso piu' breve\n\n");
        do{
            printf(" >>> ");
            scanf("%d", &selection);
            if(selection < 1 || selection > 2)
                printf("\n\n ATTENZIONE ! Scelta non valido\n\n Riprovare");
        }while(selection < 1 || selection > 2);

        //Inizializzazione array precedenti e pesi utilizzati in dijkstra
        pred = (int *)malloc(airport->numberOfCities * sizeof(int));
        dist = (dijkstra_val *)malloc(airport->numberOfCities * sizeof(dijkstra_val));

        if(selection == 1) dijkstra(airport, indexDepartureCity, dist, pred, MINIMUM_COST); //ricerca meta piu economica
        else    dijkstra(airport, indexDepartureCity, dist, pred, MINIMUM_DURATION); //ricerca meta piu breve

        //VERIFICO CHE CI SIANO VOLI CHE ARRIVANO ALLA CITTA' DESIGNATA COME DESTINAZIONE
        if(pred[indexDestinationCity] == -1){
            printf("\n\n ATTENZIONE ! Non ci sono voli per %s partenti da %s\n\n", airport->cities[indexDestinationCity].cityName, airport->cities[indexDepartureCity].cityName);
            //deallocazione strutture dati utilizzate in dijkstra
            free(pred);
            free(dist);
            return;
        }

        userBooking.pathway = createPath(airport, pred, indexDepartureCity, indexDestinationCity); //crea itinerario volo
        if(selection == 1){
            //TRATTA PIU' ECONOMICA
            userBooking.travelCost = dist[indexDestinationCity].v; //calcola il costo della tratta piu' economica
            userBooking.travelDuration = minutesToHours(dist[indexDestinationCity].v2); //calcola la durata della tratta piu' economica
        }else{
            //TRATTA PIU' BREVE
            userBooking.travelDuration = minutesToHours(dist[indexDestinationCity].v); //calcola la durata della tratta piu' breve
            userBooking.travelCost = dist[indexDestinationCity].v2; //calcola il costo della tratta piu' breve
        }

        //deallocazione strutture dati utilizzate in dijkstra
        free(pred);
        free(dist);
    }else{
        //creo il percorso costituito dal volo diretto dalla partenza alla destinazione
        userBooking.pathway = initPath();
        userBooking.pathway = insertHeadInPath(userBooking.pathway, airport->cities[indexDestinationCity].cityName);
        userBooking.pathway = insertHeadInPath(userBooking.pathway, airport->cities[indexDepartureCity].cityName);
        //calcola la durata del volo
        userBooking.travelDuration = minutesToHours(userBooking.travelDuration);
    }

    strcpy(userBooking.departureCity, airport->cities[indexDepartureCity].cityName);
    strcpy(userBooking.destinationCity, airport->cities[indexDestinationCity].cityName);

    system("clear");
    printf("\n\n **************** RIEPILOGO PRENOTAZIONE ****************\n\n");
    printBooking(userBooking);

    printf("\n\n Accettare prenotazione ?\n\n\t1. ACCETTA\n\t2. ANNULLA\n\n");
    do{
        printf(" >>> ");
        scanf("%d", &selection);
        if(selection < 1 || selection > 2)
            printf("\n\n ATTENZIONE ! Scelta non valida\n\n Riprovare");
    }while(selection < 1 || selection > 2);

    if(selection == 1){
        airport->cities[indexDestinationCity].popularity += 1; //aumento popolarita' citta di destinazione viaggio

        //AGGIUNTA SCONTO E GESTIONE PUNTI
        if (user->User.points == 0) {
            obtainPoints (user, userBooking.travelCost);
        } else {
            printf ("\n\n Vuoi pagare ottenendo uno sconto con i tuoi punti?\n");
            printf("\n\t1. SI\n\t2. NO\n\n");
            do{
                printf(" >>> ");
                scanf("%d", &selection);
                if(selection < 1 || selection > 2)
                    printf("\n\n ATTENZIONE ! Scelta non valida\n\n Riprovare");
            }while(selection < 1 || selection > 2);

            if (selection == 1) {
                discounted_price = payWithPoints (user, userBooking.travelCost);
                userBooking.travelCost = discounted_price;
                obtainPoints (user, discounted_price);
            }else{
                obtainPoints(user, userBooking.travelCost);
            }
        }

        //aggiungo prenotazione a lista prenotazioni dell'utente
        user->User.Bookings = addNewBooking(user->User.Bookings, userBooking);

        printf("\n\n **************** PRENOTAZIONE EFFETTUATA CON SUCCESSO ! ****************\n\n");
    }else{
        printf("\n\n **************** PRENOTAZIONE ANNULLATTA ! ****************\n\n");
    }
}
