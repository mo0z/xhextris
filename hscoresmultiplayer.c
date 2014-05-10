#include "xhextris.h"

#define DISPLAYTEXT(x, y, win, text) \
    XDrawString(dpy, win, gc, x, y, text, strlen(text));

void xhextrisScoreMultiplayer(){
    int y, i, x;
    static char *header[] = {"Ordre", "Joueur", "Score", "IP" };
    char message[16];
    external_user_t *it;

    Window scores_multiplayer = 
        XCreateSimpleWindow (dpy, DefaultRootWindow(dpy), 0, 0,
                WINDOWIDTH,
			    (MAXROW+8)*HEXWIDTH,
			    0, white, black);
    XMapWindow(dpy, scores_multiplayer);
    
    y = ((CURSOR_H<<2))+32;
    x = 35;
    for(i= 0 ; i <4; i++){
      DISPLAYTEXT(x, y, scores_multiplayer, header[i]);
      x+=strlen(header[i])*9;
    }

    y=((CURSOR_H<<2))+32;

    for(it=external_users; it; it=it->next_user, y+=16){
        sprintf(message, "%3d", i+1);
        DISPLAYTEXT(x, y, scores_multiplayer, message);
        x+=strlen(header[0])*10;

        DISPLAYTEXT(x, y, scores_multiplayer, it->user_id);
        x+=strlen(message)*10;

        sprintf(message, "%d",  it->user_score);
        DISPLAYTEXT(x, y, scores_multiplayer, message);
        x+=strlen(message)*10;

        DISPLAYTEXT(x, y, scores_multiplayer, it->user_ip);
    }

}
