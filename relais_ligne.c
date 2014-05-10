#include "xhextris.h"

#define QUERY_STRING "localhost"
#define USER_ID "vov"

int main (int argc, char **argv){
    char query[128];
    int nombre_lignes = 2;
    char *color = "darkgrey";
    // --> Couleur à chercher dans la base
    Window w;
    
    Display *dpy = XOpenDisplay(NULL);

    Atom xhextris_atom = XInternAtom(dpy, "xhextris_query_string", False);

    strcat(query, QUERY_STRING);
    strcat(query, " ");
    strcat(query, USER_ID);

    XGrabServer(dpy);
    w = XGetSelectionOwner(dpy, xhextris_atom);
    XSetSelectionOwner(dpy, w, xhextris_atom, CurrentTime);
    XUngrabServer(dpy);

    
    fprintf(stderr, "Sending atom to %i\n", (int)w);
    XChangeProperty(dpy,
            w,
            xhextris_atom,
            XA_STRING,
            8,
            PropModeReplace,
            query,
            strlen(query));
    XFlush(dpy);

    return 0;
}
