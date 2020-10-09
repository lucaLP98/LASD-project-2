/*
 * File : utilities.c
 */
#include "utilities.h"

void printAirplane(){
    printf("\n");
    printf("%50s\n", "|");
    printf("%50s\n", "|");
    printf("%51s\n", "_'_");
    printf("%52s\n", ".   .");
    printf("%53s\n", "' ___ '");
    printf("%63s\n", "_________'  .-.  '_________");
    printf("%54s\n", "'  .-.  '");
    printf("%79s\n", "_________________________'       '_________________________");
    printf("%78s\n", " ''''''-|---|--/   \\==][^',_m_,'^][==/   \\--|---|-'''''' ");
    printf("%63s\n", "                 \\   /                 \\   /");
    printf("\n");
}

void logScreen(){
    printf("\n");
    printf("%54s\n", "_      ______    ____");
    printf("%55s\n", " | |    |  __  |  / ___|" );
    printf("%54s\n", " | |    | |  | | | |  _");
    printf("%55s\n", " | |___ | |__| | | |_| |");
    printf("%55s\n", " |_____||______|  \\____|");
    printf("\n\n");
    printf("______________________________________________________________________________________________\n");
    printf("______________________________________________________________________________________________\n");
}

void regScreen(){
    printf("\n\t\t\t");
    printf("%35s\n\t\t\t", "      _____    _____     _____              ");
    printf("%35s\n\t\t\t", "     | ___ \\  |  ___|   /  ___\\         ");
    printf("%35s\n\t\t\t", "     | |_/ /  | |___    | |              ");
    printf("%35s\n\t\t\t", "     |    /   |  ___|   | |  __            ");
    printf("%35s\n\t\t\t", "     | |\\ \\   | |____   | |__| |           ");
    printf("%35s\n\t\t\t", "     \\_| \\_|  \\_____/   \\_____/          ");
    printf("\n");
    printf("_________________________________________________________________________________________________\n");
    printf("_________________________________________________________________________________________________\n");
    printf("\n");
}

void menuScreen(){
    printf("\t\t\t");
    printf("%35s\n\t\t\t", "      __  __   _____   _   _   _   _        ");
    printf("%35s\n\t\t\t", "     |  \\/  | |  ___| | \\ | | | | | |      ");
    printf("%35s\n\t\t\t", "     | .  . | | |___  |  \\| | | | | |       ");
    printf("%35s\n\t\t\t", "     | |\\/| | |  ___| | . ` | | | | |      ");
    printf("%35s\n\t\t\t", "     | |  | | | |___  | |\\  | | |_| |      ");
    printf("%35s\n\t\t\t", "     \\_|  |_/ \\_____/ \\_| \\_/  \\___/       ");
    printf("\n");
    printf("_________________________________________________________________________________________________\n");
    printf("_________________________________________________________________________________________________\n");
    printf("\n");
}

double minutesToHours (double time) {
    int int_time, hours;
    double minutes, result;
    time = time + 0.0000000000001;
    int_time = (int)time;
    hours = time/60;
    minutes = int_time%60;
    minutes = minutes/100;
    result = hours+minutes;
    return result;
}

double hourstominutes (double time) {
    int hours;
    double minutes, result;
    hours = (int) time;
    minutes = (time - hours)*100;
    result = (hours*60) + minutes;
    return result;
}

void clearScreen(){
    printf("\n\n Premere INVIO per continuare...\n");getchar(); getchar();
    system("clear");
}

char *stringLower(char *str){
    int i = -1;
    char *newStr = (char *)malloc((strlen(str)+1)*sizeof(char));

    while(str[++i] != '\0')
        newStr[i] = (char)tolower(str[i]);

    newStr[i] = '\0';

    return newStr;
}
