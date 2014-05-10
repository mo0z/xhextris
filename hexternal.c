#include "xhextris.h"

external_user_t * external_users;

external_user_t * external_users_init(char **argv, int user_start, int user_end){
    char *p;
    int i = user_start;
    fprintf(stderr, "Ext init > %d end %d\n", i, user_end);
    external_users = (external_user_t*)malloc(sizeof(external_user_t));
    memset(external_users, 0, sizeof(external_user_t));
    external_users->next_user = NULL;
    
    while(i != user_end){

        fprintf(stderr, "External init > %s\n", argv[i]);
        p = index(argv[i], '/');
        strncpy(external_users->user_ip, argv[i], p-argv[i]);
        argv[i] = p;
        strcpy(external_users->user_id, argv[i]); 
        
        external_user_t *n = (external_user_t*)malloc(sizeof(external_user_t));
        memset(n, 0, sizeof(external_user_t));
        n->next_user = external_users->next_user;
        external_users->next_user = n;
        i++;
    }
    return external_users;
}
