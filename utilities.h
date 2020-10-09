/*
 * file : utilities.h
 * In questo file vengono definite tutte le funzioni e le procedure
 * impiegate per il controllo dell'esecuzione del programma
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Funzione che permette di stampare a video l'immagine
 * stilizzata di un aereo
 */
void printAirplane();

/*
 * Stampa la scritta LOG a schermo
 */
void logScreen();

/*
 * Stampa la scritta REG a schermo
 */
void regScreen();

/*
 * Stampa la scritta MENU a schermo
 */
void menuScreen();

/*
 * Funzione che permette di selezionare la modalita' di accesso:
 * 1 -> accesso come amministratore
 * 2 -> accesso come utente
 * 0 -> uscire dl programma
 */
int accessMode();

/*
 * Converte il tempo inserito in minuti nel formato
 * "ore.minuti".
 */
double minutesToHours (double time);

/*
 * Converte il tempo inserito nel formato "ore.minuti"
 * in minuti.
 */
double hourstominutes (double time);

/*
 * Funzione che permette di pulire lo schermo
 */
void clearScreen();

/*
 * Funzione che riceve una stringa in input e restituisce la stessa stringa
 * in cui ogni carattere e' stato convertito in minuscolo
 */
char *stringLower(char *str);

#endif //UTILITIES_H
