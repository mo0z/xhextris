#include "xhextris.h"

int main (int argc, char **argv){
    
    if(argc != 2){
        fprintf(stderr, "Usage : %s Window\n", argv[0]);
        exit(20);
    }
    Display *dpy = XOpenDisplay(NULL);
    Window game_window = (Window) atoi(argv[1]);
    XEvent event;
    KeySym sym = XStringToKeysym("2");
    KeyCode code = XKeysymToKeycode(dpy, sym);

    event.xkey.window = game_window;
    event.xkey.root = DefaultRootWindow(dpy);
    event.xkey.type = KeyPress;
    event.xkey.keycode = code;

    while(1){
        sleep(rand() % 16);
        fprintf(stderr, "Mauvais génie> Send Event to %i!\n", (int)game_window);
        XSendEvent(dpy, game_window, True, KeyPressMask, &event);
        XFlush(dpy);
    }

    return 0;
}
