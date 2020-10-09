/*
 * file : booking_list.c
 */
#include "booking_list.h"

bookingsList initBookingsList(){
    return NULL;
}

int emptyBookingsList(bookingsList top){
    return top == NULL;
}

bookingsList addNewBooking(bookingsList top, booking newBooking){
    bookingsList tmp;

    tmp = (bookingsList)malloc(sizeof(linked_booking_list));
    tmp->Booking = newBooking;
    tmp->next = top;

    return tmp;
}

void printBooking(booking tmp){
    printf("\n - Citta' di partenza : %s", tmp.departureCity);
    printf("\n - Citta' di destinazione : %s", tmp.destinationCity);
    printf("\n - Durata del viaggio : %.2lf ore", tmp.travelDuration);
    printf("\n - Costo del biglietto : %.2lf Euro", tmp.travelCost);
    printf("\n - Numero scali : %d\n", numberOfStopovers(tmp.pathway));
    printPath(tmp.pathway);
}

void printBookingsList(bookingsList top, char username[]){
    bookingsList ptr = top;

    if(ptr != NULL){
        printf("\n Prenotazioni effettuate da %s\n", username);
        while(ptr != NULL){
            printBooking(ptr->Booking);
            ptr = ptr->next;
        }
    }else{
        printf("\n Nessuna prenotazione effettuata da %s\n", username);
    }
}

bookingsList freeBookingsList(bookingsList top){
    bookingsList ptr;

    while(!emptyBookingsList(top)){
        ptr = top;
        top = top->next;
        freePath(ptr->Booking.pathway);
        free(ptr);
    }

    return top;
}

bookingsList deleteHeadOfBookingsList(bookingsList top){
    bookingsList ptr;

    if(!emptyBookingsList(top)){
        ptr = top;
        top = top->next;
        free(ptr);
    }

    return top;
}

int compareBooking(booking b1, booking b2){
    return
        ((b1.travelCost == b2.travelCost) && (b2.travelDuration == b1.travelDuration) &&
        (strcmp(b1.departureCity, b2.destinationCity) == 0) &&
        (strcmp(b1.departureCity, b2.departureCity) == 0));
}

bookingsList deleteBoking(bookingsList top, booking toDelete){
    bookingsList prew, ptr;
    int found;

    if(compareBooking(top->Booking, toDelete)){
        top = deleteHeadOfBookingsList(top);
    }else{
        found = 0;
        prew = top;
        ptr = top->next;

        while(ptr != NULL && found == 0){
            if(compareBooking(top->Booking, toDelete)){
                prew->next = ptr->next;
                free(ptr);
                found = 1;
            }else{
                ptr = ptr->next;
            }
        }
    }

    return top;
}
