#include "users.h"
#include "city_graph.h"

int main() {
    int mod, loginResult, error;

    //Creazione delgli alberi per utenti e amministratori
    usersTree ABRutenti, ABRamministratori, utente = initUsersTree(), amministratore = initUsersTree();

    //Creazione del grafo aeroporto
    cityGraph airport = createAirport("citta.txt", "tratte_voli.txt");

    //Stampa logo aereo a video
    printAirplane();
    printf("\n\t\t\t\t BENVENUTI NELLA COMPAGNIA AEREA\n");

    //Prelevo utenti registrati dal file utenti
    ABRutenti = createUsersTree("utenti.txt");
    //Prelevo amministratori dal relativo file
    ABRamministratori = createUsersTree("amministratori.txt");

    /************ MODALITA AMMINISTRATORE *******************/
    printf("\n MODALITA AMMINISTRATORE\n\n In questa modalita' potrai aggiungere nuove citta e nuove tratte\n e rimuovere citta e tratte esistenti.\n Premendo su ESCI si passara' in modalita' utente\n\n");
    mod = selectUsersAccessMode();
    while(mod != 0){
        //AMMINISTRATORE EFFETTUA LOGIN
        if(mod == LOGIN){
            system("clear");
            logScreen();

            user tmp = insertCredentials(); //inserimento credenziali amministratore
            amministratore = login(tmp, ABRamministratori, &loginResult); //accesso amministratore
            if(loginResult != 0){
                if(loginResult == -1){
                    ABRamministratori = manageUnregisteredUser(ABRamministratori, "amministratori.txt");
                }

                while(amministratore != NULL && amministratore->User.status == ONLINE){
                    //OPERAZIONI AMMINISTRATORE
                    menuScreen();
                    printf("\n Amministratore %s\n", amministratore->User.username);
                    adminOperation(adminMenu(), amministratore, &ABRutenti, airport);
                }
            }
        }else{
        //AMMINISTRATORE EFFETTUA REGISTRAZIONE
            system("clear");
            ABRamministratori = registration(ABRamministratori, "amministratori.txt", &error);
        }

        printf("\n\n Premere INVIO per tornare alla HOMEPAGE modalita' admin\n\n"); getchar();getchar();
        system("clear");
        printf("\n MODALITA AMMINISTRATORE\n\n In questa modalita' potrai aggiungere nuove citta e nuove tratte\n e rimuovere citta e tratte esistenti.\n Premendo su ESCI si passara' in modalita' utente\n\n");
        mod = selectUsersAccessMode();
    }

    system("clear");

    /************ MODALITA UTENTE *******************/
    printAirplane();
    printf("\n MODALITA UTENTE\n\n");
    mod = selectUsersAccessMode();
    while(mod != 0){
        //UTENTE EFFETTUA LOGIN
        if(mod == LOGIN){
            system("clear");
            logScreen();

            user tmp = insertCredentials();
            utente = login(tmp, ABRutenti, &loginResult);
            if(loginResult != 0){
                if(loginResult == -1){
                    ABRutenti = manageUnregisteredUser(ABRutenti, "utenti.txt");
                }

                while(utente != NULL && utente->User.status == ONLINE){
                    //OPERAZIONI UTENTE
                    menuScreen();
                    printf("\n Utente %s\n", utente->User.username);
                    usersOperation(usersMenu(), utente, airport);
                }
            }
        }else{
            // REGISTRAZIONE UTENTE
            system("clear");
            ABRutenti = registration(ABRutenti, "utenti.txt", &error);
        }

        printf("\n\n Premere INVIO per tornare alla HOMEPAGE modalita' utente\n\n"); getchar();getchar();
        system("clear");
        printf("\n MODALITA UTENTE\n\n");
        mod = selectUsersAccessMode();
    }

    //aggiornamento file utenti
    saveUsersChangesOnFile("utenti.txt", ABRutenti);
    //aggiornamento file citta e tratte
    updateFiles(airport, "citta.txt", "tratte_voli.txt");

    //FINE PROGRAMMA
    printf("\n\n ____________________________________________________________________________________________");
    printf("\n\n GRAZIE PER AVER UTILIZZATO IL NOSTRO APPLICATIVO\n\n Developed By Luca Pastore, Lorenzo Musella, Lorenzo Pergamo\n\n");
    printf("\n\n Premere INVIO per USCIRE\n"); getchar(); getchar();
    return 0;
}
