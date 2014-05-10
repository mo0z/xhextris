#include "xhextris.h"

char xhextrisExposeEvent(XExposeEvent *ev){
    DEBUGPRINT(("Exp: '%d'\n",ev->window));;
    return ((ev->count) ? 0 : 'r');
}

char xhextrisKeyPress(XKeyPressedEvent *ev){
    KeySym key;
    XComposeStatus compose;
    char buffer[8];
    int  bufsize=8;

    XLookupString(ev,buffer,bufsize, &key, &compose);
    DEBUGPRINT(("KeyEvent: '%s'\n", buffer));
    return (buffer[(strncmp(buffer, "\024[", 2) ? 0 : 3)]);
}

char xhextrisButtonPress(XButtonEvent *ev){
    int w = ev->x;
    XEvent xe;

    while (1) {
        w=xhextrisSetspeed(w);
        XMaskEvent(dpy, ButtonPressMask|ButtonReleaseMask|ButtonMotionMask,&xe);
        if (xe.type == MotionNotify){
            w= xe.xmotion.x;
        }else if (xe.type == ButtonRelease) break;
    }
    button_speed=w+(CURSOR_H>>1);
    return 0;
}

char xhextrisProperty(XPropertyEvent *ev){
    int format;
    char read[128];
    unsigned long lus, restants;
    Atom type_obtenu;

    XGetWindowProperty(dpy,
		     wincur,
		     atomes[1],
		     0,        /* pas de decalage dans la lecture      */
		     64,       /* multiple de 32 bits, soit 256 octets */
		     False,    /*  detruire une fois la valeur lue     */
		     AnyPropertyType,  /* pas de type precis demande   */
		     &type_obtenu,     /* le type obtenu               */
		     &format,          /* son format 8, 16 ou 32 bits  */
		     &lus,	 /* quantite lue                 */
		     &restants,        /* le reste = offre - demande   */
		     (unsigned char **)read); /* la valeur lue            */ 
    return 0;
}

