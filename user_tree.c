/*
 * file : user_tree.c
 */
#include "user_tree.h"

int emptyUsersTree(usersTree t){
    return (t == NULL);
}

usersTree initUsersTree(){
    return NULL;
}

void printUsers(user utente){
    printf("\n\n Username: %s,\t Punti accumulati: %d\n", utente.username, utente.points);
}

void inOrderViewUsers(usersTree t){
    if( !emptyUsersTree(t) ){
        inOrderViewUsers(t->sx);
        printUsers(t->User);
        printf("\n"),
        inOrderViewUsers(t->dx);
    }
}

usersTree allocateNewNodeUsers(char newUser[], char newPassword[], int points){
    usersTree tmp;

    tmp = (usersTree)malloc(sizeof(ABRusers));
    strcpy(tmp->User.username, newUser);
    strcpy(tmp->User.password, newPassword);
    tmp->User.points = points;
    tmp->User.Bookings = initBookingsList();
    tmp->User.status = OFFLINE;
    tmp->sx = NULL;
    tmp->dx = NULL;

    return tmp;
}

usersTree insertNewUser(usersTree t, char newUsername[], char newPassword[], int points){
    if( !emptyUsersTree(t) ){
        if( strcmp(newUsername, t->User.username ) < 0 )
            t->sx = insertNewUser(t->sx, newUsername, newPassword, points);
        else if( strcmp(newUsername, t->User.username ) > 0 )
            t->dx = insertNewUser(t->dx, newUsername, newPassword, points);
    }else{
        t = allocateNewNodeUsers(newUsername, newPassword, points);
    }

    return t;
}

usersTree searchUsers(usersTree t, char username[]){
    if( !emptyUsersTree(t) ){
        if( strcmp(username, t->User.username ) < 0 )
            return searchUsers( t->sx, username );

        if( strcmp(username, t->User.username ) > 0 )
            return searchUsers( t->dx, username );
    }

    return t;
}

usersTree detachMinimumUser (usersTree T, usersTree P){
    if( T != NULL ){
        if( T->sx != NULL )
            return detachMinimumUser ( T->sx, T );

        if( P->sx == T )
            P->sx = T->dx;
        else
            P->dx = T->dx;
    }

    return T;
}

usersTree deleteRootUser(usersTree T){
    usersTree tmp;

    if(T != NULL){
        if( T->sx == NULL  || T->dx == NULL ){
            tmp = T;
            if(T->sx != NULL)
                T = T->sx;
            else
                T = T->dx;
        }else {
            tmp = detachMinimumUser( T->dx, T );
            T->User = tmp->User;
        }

        free(tmp);
    }

    return T;
}

usersTree deleteUser(usersTree T, char username[], int* err){
    if( T != NULL){
        if( strcmp (T->User.username, username) == 0 ){
            T = deleteRootUser( T );
            *err = 1;
        }

        else if( strcmp(T->User.username, username) < 0 )
            T->dx = deleteUser( T->dx, username, err);
        else
            T->sx = deleteUser( T->sx, username, err);
    }

    return T;
}
