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


/*char xhextrisExposeEvent(XExposeEvent *ev){
    if(ev->count){
        return 'r';
    }
    return 0;
}

char xhextrisKeyPress(XKeyPressedEvent *ev){
    char buff[8];
    KeySym keys;
    XComposeStatus composes;
    XLookupString(ev, buff, 8, &keys, &composes);
    return buff[0];
}

char xhextrisButtonPress(XButtonEvent *ev){
    XEvent xe;
    xhextrisSetspeed(ev->x);
    while(1){
        XMaskEvent(dpy, ButtonReleaseMask | Button1MotionMask, &xe);
        if(xe.type == ButtonRelease) break;
        else xhextrisSetspeed(xe.x);
    }
    return 0;
}*/

