/*
 * file : booking_list.h
 * In questo file vengono definite tutte le strutture dati, funzioni e procedure
 * che permettono di manipolare prenotazioni e liste di prenotazioni
 */

#ifndef PROGETTO_BOOKING_LIST_H
#define PROGETTO_BOOKING_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "path_list.h"

//DEFINZIONE STRUTTURA PER PRENOTAZIONI
struct T_booking{
    char departureCity[50];
    char destinationCity[50];
    double travelDuration;
    double travelCost;
    path pathway;
};
typedef struct T_booking booking;

//DEFINIZIONE STRUTTURA PER LISTA DI PRENOTAZIONI
struct T_booking_list{
    booking Booking;
    struct T_booking_list *next;
};
typedef struct T_booking_list linked_booking_list;
typedef linked_booking_list *bookingsList;

//DEFINIZIONE FUNZIONI PER MANIPOLARE UNA LISTA DI PRENOTAZIONI

/*
 * Restituisce 1 se la lista di prenotazioni Ã¨ vuota, 0 altrimenti
 */
int emptyBookingsList(bookingsList top);

/*
 * Inizializza la lista di prenotazioni
 */
bookingsList initBookingsList();

/*
 * Inserisce una nuova prenotazione in testa alla lista delle prenotazioni
 */
bookingsList addNewBooking(bookingsList top, booking newBooking);

/*
 * Procedura che permette di stampare una singola prenotazione
 */
void printBooking(booking tmp);

/*
 * Procedura che permette di stamapre una lista di prenotazione,
 * specificando l'username dell0utente a cui appartengono tali prenotazioni
 */
void printBookingsList(bookingsList top, char username[]);

/*
 * Elimina ogni elemento della lista, deallocandola
 */
bookingsList freeBookingsList(bookingsList top);

/*
 * Funzione che confronta due prenotazioni.
 * Restituisce 1 se le prenotazioni sono uguali. 0 altrimenti
 */
int compareBooking(booking b1, booking b2);

/*
 * Elimina la prenotazione "toDelete" della lista fi prenotazioni
 */
bookingsList deleteBoking(bookingsList top, booking toDelete);

#endif //PROGETTO_BOOKING_LIST_H
