#include "xhextris.h"

void initXrm(char *backcolor){
    int i;
    
    PieceNamedColors[0] = backcolor;

    XrmInitialize();
    xrm_database = XrmGetFileDatabase(XRMDATABASE);
    if(xrm_database == NULL){
        fprintf(stderr, "Impossible d'ouvrir le gestionnaire de ressources.\n");
        return;
    }
    for(i = 0; i < NUMBEROFPIECES + 2; i++){
        XrmValue value;
        char c[4];

        sprintf(c, "%d", i);
        value.addr = PieceNamedColors[i];
        value.size = strlen(PieceNamedColors[i]);
        XrmPutResource(&xrm_database, c, "color", &value);
    }
    XrmPutFileDatabase(xrm_database, XRMDATABASE);
}
