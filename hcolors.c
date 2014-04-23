#include "xhextris.h"

int xhextrisColors(int numberofpieces){
    char **buf = (char**)malloc(20*sizeof(char*));
    int i;
     
    if(xrm_database != NULL){ // Si on utilise un gestionnaire de ressources
        fprintf(stderr, "On initialise les couleurs depuis la base\n");
        for(i = 0; i < NUMBEROFPIECES + 2; i++){
            char c[4];
            XrmValue value;
            sprintf(c, "%d", i);

            XrmGetResource(xrm_database, c, "color", buf, &value);
            fprintf(stderr, "i = %d color= %s\n", i, value.addr);
            PieceNamedColors[i] = value.addr;
            fprintf(stderr, "PieceNamedColors = %s\n", PieceNamedColors[i]);
        }
    }

    for (i=0;i<=numberofpieces+1;i++){
        if (!XAllocNamedColor(dpy, 
			    DefaultColormap(dpy, DefaultScreen(dpy)),
			    PieceNamedColors[i],
			    &PieceColors[i],
			    &PieceColors[i]))
        return i+1;
    }

    return 0;
}

