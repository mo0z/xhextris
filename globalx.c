/*  See header.h for licence */

#include "xhextris.h"

/* Ce fichier ne contient que les variables globales de type X11 */

Display *dpy;
Window win;
Window wincur;
GC gc=NULL;
GC hexgc=NULL;
GC pixgc=NULL;
XFontStruct *textfont;
Pixmap fond;
Pixmap black;
Pixmap white;
XrmDatabase xrm_database;
XColor PieceColors[NUMBEROFPIECES+2];
Atom atomes[2];
char *PieceNamedColors[NUMBEROFPIECES+2]=
  {    "darkgrey",
	"Orange1",
	"red1",
	"blue1",
	"green1",
	"yellow1",
	"chocolate1",
	"SteelBlue1",
	"Plum1",
	"pink1",
	"Maroon1",
	"purple1"
};
char *help[] = {
  "J,j,4 - va vers la gauche",
  "L,l,6 - va vers la droite",
  "K,k,5 - rotation gauche",
  "I,i,8 - rotation droite",
  "espace,0 - tombe",
  "N,n - recommence",
  "P,p - suspend",
  "U,u - reprend",
  "R,r - affiche",
  "Q,q - quitte"
};
