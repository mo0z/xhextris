#include "xhextris.h"

#define my_id "vov"

int send_cleared_rows(external_user_t *users, int cleared_rows){
    int i = 0;
    external_user_t *it;

    if(cleared_rows)
        for(it = external_users, i=0; it; it=it->next_user, i++){
            //Envoyer le GET à user_ip
            char query[128];
            char nb_rows[3];
            sprintf(nb_rows, "%d", cleared_rows);
            strcat(query, "nombre_lignes=");
            strcat(query, nb_rows);
            strcat(query, "&");
            strcat(query, "background=");
            strcat(query, PieceNamedColors[0]);
            strcat(query, " ");
            strcat(query, my_id);

            //send_get(it->user_ip, query);
        }
    return i;
}
