/*  See header.h for licence */

#include "xhextris.h"

unsigned long button_speed=SPEEDBUTTON;
unsigned long speed= 1000000000;
unsigned long score;
int total_pieces, rows=0, game_over = 2, end_all_games=1, saved=1;
unsigned char grid[MAXROW][MAXCOLUMN];
high_score_t high_scores[MAXHIGHSCORES];

/* Ceci est la d�finition des pi�ces, compos�es chacune de 4 hexagones.
 * Chaque pi�ce a donc six rotations (pas forc�ment distinctes) d�finies
 * par 4 paires de coordonn�es d�crivant le d�placement des 4 hexagones.
 * Toutefois, la quinconce impos�e par les hexagones d�double ces 4 paires.
 * Il y a donc 16 nombres par ligne, qu'on aurait pu d�couper en 2. 
 */

short shape[NUMBEROFPIECES*6][16]=
    {   { 0, 0,-1, 0, 1,-1, 1, 1,  -1, 0, 0,-1, 0, 1, 0, 0},	/* 00 */
	{ 0, 0, 0,-1, 0, 1, 1, 0,  -1,-1,-1, 1, 1, 0, 0, 0},	/* 01 */
	{ 0, 0,-1, 0, 1,-1, 1, 1,  -1, 0, 0,-1, 0, 1, 0, 0},	/* 02 */
	{ 0, 0, 0,-1, 0, 1, 1, 0,  -1,-1,-1, 1, 1, 0, 0, 0},	/* 03 */
	{ 0, 0,-1, 0, 1,-1, 1, 1,  -1, 0, 0,-1, 0, 1, 0, 0},	/* 04 */
	{ 0, 0, 0,-1, 0, 1, 1, 0,  -1,-1,-1, 1, 1, 0, 0, 0},	/* 05 */
	{ 0, 0,-1, 0, 1, 0, 2, 0,  -1, 0, 1, 0, 2, 0, 0, 0},	/* 10 */
	{ 0, 0, 0,-1, 1, 1, 1, 2,  -1,-1, 0, 1, 1, 2, 0, 0},	/* 11 */
	{ 0, 0, 1,-1, 0, 1,-1, 2,   0,-1,-1, 1,-1, 2, 0, 0},	/* 12 */
	{ 0, 0,-2, 0,-1, 0, 1, 0,  -2, 0,-1, 0, 1, 0, 0, 0},	/* 13 */
	{ 0, 0,-1,-2, 0,-1, 1, 1,  -1,-2,-1,-1, 0, 1, 0, 0},	/* 14 */
	{ 0, 0, 1,-2, 1,-1, 0, 1,   1,-2, 0,-1,-1, 1, 0, 0},	/* 15 */
	{ 0, 0,-1, 0, 1, 0, 1, 1,  -1, 0, 1, 0, 0, 1, 0, 0},	/* 20 */
	{ 0, 0, 0,-1, 1, 1, 0, 1,  -1,-1, 0, 1,-1, 1, 0, 0},	/* 21 */
	{ 0, 0, 1,-1, 0, 1,-1, 0,   0,-1,-1, 0,-1, 1, 0, 0},	/* 22 */
	{ 0, 0, 0,-1,-1, 0, 1, 0,  -1,-1,-1, 0, 1, 0, 0, 0},	/* 23 */
	{ 0, 0, 0,-1, 1,-1, 1, 1,   0,-1,-1,-1, 0, 1, 0, 0},	/* 24 */
	{ 0, 0, 1,-1, 1, 0, 0, 1,   0,-1, 1, 0,-1, 1, 0, 0},	/* 25 */
	{ 0, 0,-1, 0, 1,-1, 1, 0,  -1, 0, 0,-1, 1, 0, 0, 0},	/* 30 */
	{ 0, 0, 0,-1, 1, 0, 1, 1,  -1,-1, 1, 0, 0, 1, 0, 0},	/* 31 */
	{ 0, 0, 1,-1, 0, 1, 1, 1,   0,-1,-1, 1, 0, 1, 0, 0},	/* 32 */
	{ 0, 0,-1, 0, 1, 0, 0, 1,  -1, 0, 1, 0,-1, 1, 0, 0},	/* 33 */
	{ 0, 0, 0,-1,-1, 0, 1, 1,  -1,-1,-1, 0, 0, 1, 0, 0},	/* 34 */
	{ 0, 0, 0,-1, 1,-1, 0, 1,  -1,-1, 0,-1,-1, 1, 0, 0},	/* 35 */
	{-1, 0, 0,-1, 1,-1, 1, 0,  -1, 0,-1,-1, 0,-1, 1, 0},	/* 40 */
	{ 0,-1, 1,-1, 1, 0, 1, 1,  -1,-1, 0,-1, 1, 0, 0, 1},	/* 41 */
	{ 1,-1, 1, 0, 1, 1, 0, 1,   0,-1, 1, 0, 0, 1,-1, 1},	/* 42 */
	{ 1, 0, 1, 1, 0, 1,-1, 0,   1, 0, 0, 1,-1, 1,-1, 0},	/* 43 */
	{ 1, 1, 0, 1,-1, 0, 0,-1,   0, 1,-1, 1,-1, 0,-1,-1},	/* 44 */
	{ 0, 1,-1, 0, 0,-1, 1,-1,  -1, 1,-1, 0,-1,-1, 0,-1},	/* 45 */
	{-1, 0, 1, 1, 2, 1, 0, 0,  -1, 0, 0, 0, 0, 1, 1, 1},	/* 50 */
	{ 0,-1, 0, 0, 0, 1, 0, 2,  -1,-1, 0, 0,-1, 1, 0, 2},	/* 51 */
	{ 1,-1, 0, 0,-1, 0,-1, 1,   0,-1, 0, 0,-1, 0,-2, 1},	/* 52 */
	{ 1, 0, 0, 0, 0,-1,-1,-1,   1, 0, 0, 0,-1,-1,-2,-1},	/* 53 */
	{ 0,-2, 1,-1, 0, 0, 1, 1,   0,-2, 0,-1, 0, 0, 0, 1},	/* 54 */
	{ 2,-1, 1, 0, 0, 0, 0, 1,   1,-1, 1, 0, 0, 0,-1, 1},	/* 55 */
	{ 0, 0, 1,-1, 1, 0, 1, 1,   0, 0, 0,-1, 1, 0, 0, 1},	/* 60 */
	{ 0, 0, 1, 0, 1, 1, 0, 1,   0, 0, 1, 0, 0, 1,-1, 1},	/* 61 */
	{ 0, 0, 1, 1, 0, 1,-1, 0,   0, 0, 0, 1,-1, 1,-1, 0},	/* 62 */
	{ 0, 0, 0, 1,-1, 0, 0,-1,   0, 0,-1, 1,-1, 0,-1,-1},	/* 63 */
	{ 0, 0,-1, 0, 0,-1, 1,-1,   0, 0,-1, 0,-1,-1, 0,-1},	/* 64 */
	{ 0, 0, 0,-1, 1,-1, 1, 0,   0, 0,-1,-1, 0,-1, 1, 0},	/* 65 */
	{-1, 0, 0, 0, 1, 0, 2, 1,  -1, 0, 0, 0, 1, 0, 1, 1},	/* 70 */
	{ 0,-1, 0, 0, 1, 1, 0, 2,  -1,-1, 0, 0, 0, 1, 0, 2},	/* 71 */
	{ 1,-1, 0, 0, 0, 1,-1, 1,   0,-1, 0, 0,-1, 1,-2, 1},	/* 72 */
	{ 1, 0, 0, 0,-1, 0,-1,-1,   1, 0, 0, 0,-1, 0,-2,-1},	/* 73 */
	{ 0,-2, 0,-1, 0, 0, 1, 1,   0,-2,-1,-1, 0, 0, 0, 1},	/* 74 */
	{ 2,-1, 1,-1, 0, 0, 0, 1,   1,-1, 0,-1, 0, 0,-1, 1},	/* 75 */
	{-1, 0, 0, 0, 1, 0, 2,-1,  -1, 0, 0, 0, 1, 0, 1,-1},    /* 80 */
	{ 0,-1, 0, 0, 1, 1, 2, 1,  -1,-1, 0, 0, 0, 1, 1, 1},	/* 81 */
	{ 1,-1, 0, 0, 0, 1, 0, 2,   0,-1, 0, 0,-1, 1, 0, 2},	/* 82 */
	{ 1, 0, 0, 0,-1, 0,-1, 1,   1, 0, 0, 0,-1, 0,-2, 1},	/* 83 */
	{-1,-1, 0,-1, 0, 0, 1, 1,  -2,-1,-1,-1, 0, 0, 0, 1},	/* 84 */
	{ 0,-2, 1,-1, 0, 0, 0, 1,   0,-2, 0,-1, 0, 0,-1, 1},	/* 85 */
	{-1, 0, 0, 0, 1,-1, 2,-1,  -1, 0, 0, 0, 0,-1, 1,-1},	/* 90 */
	{ 0,-1, 0, 0, 1, 0, 2, 1,  -1,-1, 0, 0, 1, 0, 1, 1},	/* 91 */
	{ 1,-1, 0, 0, 1, 1, 0, 2,   0,-1, 0, 0, 0, 1, 0, 2},	/* 92 */
	{ 1, 0, 0, 0, 0, 1,-1, 1,   1, 0, 0, 0,-1, 1,-2, 1},	/* 93 */
	{ 1, 1, 0, 0,-1, 0,-1,-1,   0, 1, 0, 0,-1, 0,-2,-1},	/* 94 */
	{ 0,-2, 0,-1, 0, 0, 0, 1,   0,-2,-1,-1, 0, 0,-1, 1}};   /* 95 */

#define GETROTATION(type,rotation,column) \
	&shape[(type-1)*6+rotation][(column&1) ? 0 : (NUMBEROFHEX<<1)]

/* Choisir entre un tirage al�atoire ou invariant de la pi�ce suivante */

#define NEXTPIECE ((((int)random()) % NUMBEROFPIECES)+1) 
// #define NEXTPIECE ((total_pieces % NUMBEROFPIECES)+1) 

void new_piece(piece_t *npiece)
{
    total_pieces++;
    npiece->type = NEXTPIECE ;
    npiece->rotation = 0;
    npiece->row = 1;
    npiece->column = MAXCOLUMN / 2;
    DEBUGPRINT(("piece %d: %d\n", total_pieces, npiece->type ));
}

/*  visualisation de la pi�ce � venir, en dessous de la grille */

void show_next_piece(piece_t *npiece)
{
    int i;
    short *p=GETROTATION(npiece->type, 0, 0);

    for (i = 0; i < ( (NUMBEROFHEX)<<1); i += 2) {
      xhextrisHex(MAXROW+5+p[i], (MAXCOLUMN>>1)+p[i+1] ,npiece->type);
    }
}

/* Placement de la pi�ce en haut de la grille    */
/* et reflet de sa position dans la ligne en dessous,  */
/* dont tous les hexagones sont redessin�s, mais une fois seulement */

void init_piece(piece_t *piece)
{
  int i;
  int pos[MAXCOLUMN];
  short *p=GETROTATION(piece->type, piece->rotation, piece->column);

  for (i = 0; i < MAXCOLUMN; i++) { pos[i] = 0;} 

  for (i = 0; i <( (NUMBEROFHEX)<<1) ; i += 2) {
    DEBUGPRINT(("init_piece\n"));
    xhextrisHex(piece->row+(p[i]), piece->column+(p[i+1]), piece->type);
    xhextrisHex((MAXROW + 2),  piece->column+(p[i+1]), piece->type);
    pos[piece->column+(p[i+1])] = 1;
  }

  for (i = 0; i < MAXCOLUMN; i++)
    { if (!pos[i]) xhextrisHex(MAXROW + 2, i, NOPIECE);}
}

/* Placement de la pi�ce dans sa nouvelle position		*/
/* Chaque hexagone de la nouvelle est recherch� dans l'ancienne.*/
/* S'il y figure, on �vite de le redessiner.			*/
/* Sym�triquement, chaque hexagone de l'ancienne trouv� dans la nouvelle */
/* n'a pas besoin d'etre effac�.					*/
/* Si upos !=0 la nouvelle position est reflet�e sur la ligne du bas */

void place_piece(piece_t *old, piece_t *new, int upos)
{
    int i, j, c, r, diff;
    int pos[MAXCOLUMN];
    int efface[NUMBEROFHEX<<1];
    short *p=GETROTATION(old->type, old->rotation, old->column);
    short *q=GETROTATION(new->type, new->rotation, new->column);

    if (upos) { for (i = 0; i < MAXCOLUMN; i++) { pos[i] = 0;} }
    for (i = 0; i < ((NUMBEROFHEX)<<1); i += 2) { efface[i] = 0 ; }
    for (i = 0; i < ((NUMBEROFHEX)<<1); i += 2) {
        c=new->column+q[i+1];
	r=new->row+q[i];
	pos[c] = 1;
	diff = 1;
	for (j = 0; j < ((NUMBEROFHEX)<<1); j += 2) {
	    if ((r ==  old->row+p[j]) && (c == old->column+p[1+j])) {
		diff = 0;
		efface[j]=1;
		break;
		    }
	}
	if (diff) {
	  DEBUGPRINT(("place_piece %d %d\n", c ,r));
	  xhextrisHex(r, c, new->type);
	  if (upos) {
	    DEBUGPRINT(("place_pos %d\n",c));
	    xhextrisHex((MAXROW + 2), c, new->type);
	  }
	}
    }
    if (upos) {
      for (i = 0; i < MAXCOLUMN; i++)
      { if (!pos[i]) xhextrisHex(MAXROW + 2, i, NOPIECE);} 
    } 
    c=old->column;
    r=old->row;
    for (i = 0; i < ( (NUMBEROFHEX)<<1); i += 2) {
      if (!efface[i]) {
	DEBUGPRINT(("place_pos 0 %d\n",c));
	xhextrisHex(r+p[i], c+p[i+1], NOPIECE);
      }
    }
}
   
/* Controle si un pi�ce peut se mettre � un certain endroit */

int check_piece(piece_t *tpiece, unsigned char grid[MAXROW][MAXCOLUMN])
{
    int i;
    int r=tpiece->row;
    int c=tpiece->column;
    short *p=GETROTATION(tpiece->type, tpiece->rotation, c);

    for (i = 0; i < ((NUMBEROFHEX)<<1); i += 2) {
      if (r+p[i] >= MAXROW) return 1;  /* en dessous de la grille ! */
      if (c+p[i+1] >= MAXCOLUMN) return 1; /* � droite de la grille ! */
      if (c+p[i+1] < 0) return 1;	 /* � gauche de la grille ! */
      if (grid[r+p[i]][c+p[i+1]] != NOPIECE) return 1; /* occup� !*/
    }

    return 0;
}

/* Inscrit la position finale de la piece dans la grille */

void drop_piece(piece_t *piece)
{
    int i;
    int row= piece->row;
    int col= piece->column;
    int type=piece->type;
    short *p=GETROTATION(type, piece->rotation, col);
    DEBUGPRINT(("drop[]%d\n",type));

    for (i = 0; i < ( (NUMBEROFHEX)<<1); i += 2) {
	grid[row+p[i]][col+p[1+i]] = type;
    }
}

/* Redessine la grille, avec sa bordure sur 3 cot�s  */

void redraw_grid()
{
    int  j, i;

    for (i = MAXROW - 1; i >= 0; i--)
	for (j = 0; j < MAXCOLUMN; j++)
	  xhextrisHex(i, j, grid[i][j]);

    for (i = 0; i <= MAXROW; i++) {
	xhextrisHex(i,-1,BORDERPIECE); 
	xhextrisHex(i,MAXCOLUMN,BORDERPIECE); 
    }

    for (i = 0; i < MAXCOLUMN; i++) xhextrisHex(MAXROW,i,BORDERPIECE);
}

/* Efface la ligne pass�e en argument, et d�cale le reste de la grille */

void shift_redraw_grid(int start)
{
    int row, column;
    unsigned char *p,*q;

    DEBUGPRINT(("shift_redraw:%d\n", start));
    for (row = start; row > 0; row--)
	for (column = 0; column < MAXCOLUMN; column++) {
	  p=&grid[row][column];
	  q=&grid[row-1][column];
	  if (*p != *q) { *p = *q; xhextrisHex(row,column,*p); }
	}
    for (column = 0; column < MAXCOLUMN; column++) {
      if (grid[0][column] != NOPIECE) {
	grid[0][column] = NOPIECE;
	xhextrisHex(0,column,NOPIECE);
      }
    }
}

/* Meme chose, pour les lignes impaires  */

void shift_offset_redraw_grid(int start)
{
    int row, column, r;
    unsigned char *p,*q;

    DEBUGPRINT(("shift_offset:%d\n", start));
    for (row = start; row > 1; row--)
	for (column = 0; column < MAXCOLUMN; column++) {
	  r=row-(column & 1);
	  p=&grid[r][column];
	  q=&grid[r-1][column];
	  if (*p != *q) { *p = *q; xhextrisHex(r,column,*p); }
	}
    for (column = 0; column < MAXCOLUMN; column++) {
      if (grid[1-(column & 1)][column] != NOPIECE) {
	grid[1-(column & 1)][column] = NOPIECE;
	xhextrisHex(1-(column & 1),column,NOPIECE);
      }
    }
}

/* Recherche des lignes compl�tes, paires ou impaires */

int check_rows(unsigned char grid[MAXROW][MAXCOLUMN])
{
    int row, column, clear, clear_off, total_clear=0;

    for (row=MAXROW-1; row >= 0; row=(!(clear||clear_off))? row-1:row) {
	clear = 1;
	for (column = 0; column < MAXCOLUMN; column++)
	  if (grid[row][column] == NOPIECE) {clear = 0; break;}
	if (clear) { shift_redraw_grid(row); total_clear++;}
	clear_off = 1;
	for (column = 0; column < MAXCOLUMN; column++)
	  if (grid[row-(column & 1)][column] == NOPIECE) {clear_off=0; break;}
	if (clear_off) {shift_offset_redraw_grid(row); total_clear++;}
    }
    return total_clear;
}

/* Chute normale de pi�ce, avec contr�le d'arriv�e */

void update_drop(piece_t *npiece, piece_t *piece)
{
   int cleared_rows;
   piece_t tpiece = *piece;
   tpiece.row++;
   if (check_piece(&tpiece,grid)) {
      /* impossible de descendre plus bas */
	drop_piece(piece);
	cleared_rows = check_rows(grid);
    
    // Question 4)
    // Envoyer les scores aux users
    send_cleared_rows(external_users, cleared_rows);

	score += (int)((cleared_rows<<8) / button_speed);
	rows += cleared_rows;
	xhextrisScores(score,rows);
	*piece=*npiece;
	new_piece(npiece);
	show_next_piece(npiece);
	init_piece(piece);
	game_over=(tpiece.row < NUMBEROFHEX-1);
    } else {
      /* plus molle sera la chute */
	piece->row=tpiece.row;
	tpiece.row--;
	place_piece(&tpiece,piece, 0);
	game_over=0; // ne sert qu'au premier passage
    }
}

void update_left(piece_t *piece, piece_t tpiece)
{  
  piece->column--;
  if (! check_piece(piece,grid))
    place_piece(&tpiece,piece, 1);
  else {
    piece->row -= (1-((piece->column & 1)*2));
    if (! check_piece(piece,grid)) {
      place_piece(&tpiece,piece, 1);
    } else {
      piece->column = tpiece.column;
      piece->row = tpiece.row;
    }
  }
}

void update_right(piece_t *piece, piece_t tpiece)
{
  piece->column++;
  if (! check_piece(piece,grid)) /* a droite sur la meme ligne */
    place_piece(&tpiece,piece, 1);
  else {
    piece->row -=(1-((piece->column & 1)*2)); /* a droite sur la ligne inf*/
    if (! check_piece(piece,grid)) {
      place_piece(&tpiece,piece, 1);
    } else {
      piece->column = tpiece.column;
      piece->row = tpiece.row;
    }
  }
}

void update_rotateCCW(piece_t *piece, piece_t tpiece)
{
  piece->rotation = (piece->rotation == 5) ? 0 : piece->rotation+1;
  if (! check_piece(piece,grid)) {
    place_piece(&tpiece,piece, 1);
  }else {
    piece->rotation = tpiece.rotation;
  }
}

void update_rotateCW(piece_t *piece, piece_t tpiece)
{
  piece->rotation = (!piece->rotation) ? 5 : piece->rotation-1;
  if (! check_piece(piece,grid)) {
    place_piece(&tpiece,piece, 1);
  }else {
    piece->rotation = tpiece.rotation;
  }
}

void update_fall(piece_t *piece, piece_t tpiece)
{
  tpiece.row++;
  while (! check_piece(&tpiece,grid)) {
    place_piece(piece,&tpiece,0);
    piece->row=tpiece.row;
    tpiece.row++;
  }
}

void double_speed(){
    fprintf(stderr, "Double speed!\n");
    speed = speed / 2;
}

/* Aiguillage sur la touche frapp�e au clavier */

void do_choice(char choice, piece_t *npiece, piece_t *piece)
{
    switch (choice) {
    case 'j': case 'J': case '4': case 'B':
      if (! game_over) {update_left(piece,*piece);}
	break;
    case 'l': case 'L': case '6': case 'C':
      if (! game_over) {update_right(piece,*piece);}
	break;
    case 'k': case 'K': case '5': case 'D':
      if (! game_over) {update_rotateCCW(piece,*piece);}
	break;
    case 'i': case 'I': case '8': case 'A':
      if (! game_over) {update_rotateCW(piece,*piece);}
	break;
    case ' ': case '0':
      if (! game_over) {update_fall(piece,*piece);}
	break;
    case 'q': case 'Q':
      game_over=1; 
      end_all_games=0;
	break;
    case 'r': case 'R':
      redraw_game(npiece, piece);
      break;
    case 'p': case 'P':
      game_over=2;
      redraw_game(npiece, piece);
      break;
    case 'u': case 'U':
      if (game_over==2) game_over=0;
      redraw_game(npiece, piece);
      break;
    case 'n': case 'N':
	if (game_over!=2)
	  { xhextrisScores(score, rows); xhextrisCurtain(grid);}
	new_game(npiece, piece);
	redraw_game(npiece,piece);
	break;
    case '2':
        if(!game_over)
            double_speed();

    break;
    }
}

/* r�affiche */

void redraw_game(piece_t *npiece, piece_t *piece)
{
  if (game_over==2) {
    xhextrisHomepage();
    xhextrisSetspeed(button_speed);
  } else {
    xhextrisScores(score,rows);
    redraw_grid();
    show_next_piece(npiece);
    init_piece(piece);
  }
}

/* R�initialisation des variables globales. */

void new_game(piece_t *npiece, piece_t *piece)
{
    int row, column;
	
    for (row = 0; row < MAXROW; row++)
      for (column = 0; column < MAXCOLUMN; column++) {
	grid[row][column] =  NOPIECE;
      }
    game_over = saved = score = total_pieces=0;
    rows = 0;
    new_piece(piece);
    new_piece(npiece);
}

/* mode automatique */

void choose_choice(int go, piece_t *npiece, piece_t *piece)
{
  static char com[6]={'j','k','l','i',' ','j'};
  usleep(SPEED>>2);
  do_choice((go) ? 'n' : com[((int)random()) % 6], npiece, piece);
}

/* La boucle principale */

int main(int argc, char **argv){
    struct timeval tp;
    struct timezone tzp;
    char *fontdir = HEXFONTDIR;
    int man_backcolor = 0;
    int multiplayer = 0;
    char backcolor[120];
    int autom=0;
    char key=0;
    fd_set fdst;
    int i, sock, oldscore = -1;
    piece_t npiece, piece;
    int users_start;
    int option_index;
    
    setlocale(LC_MESSAGES, "");
        { // traitement des options
           const char * help_msg = 
                "usage: %s [-h][-a][-Ffontdir]\n"
            	"-h, --help\t\t\tDisplay help message.\n"
            	"-a, --auto\t\t\tComputer plays alone.\n"
                "-b, --background string\t\t\tChoose the background color.\n"
                "-u, --users <IP/userid>\t\t\tSpecifies the users that will play.\n"
            	"-F, --font-dir string\t"
            	"string indicates which font directory to use.\n";
            struct option options[] = {
            	{"help", no_argument, NULL, 'h'},
            	{"auto", no_argument, NULL, 'a'},
                {"background", required_argument, NULL, 'b'},
            	{"font-dir", required_argument, NULL, 'F'},
                {"users", no_argument, NULL, 'u'},
            	{NULL, 0, NULL, 0}};
            char opt;

            while ((opt = getopt_long (argc, argv, "habuF:", options,&option_index)) != -1)
            	switch(opt){
                	case 'h': printf(help_msg, argv[0]); exit(0);
                	case 'a': autom = 1; break;
                    case 'b': 
                        strcpy(backcolor, optarg);
                        man_backcolor = 1;
                        break;
                    case 'u':
                        multiplayer = 1;
                        users_start = option_index - 2; 
                        printf("argv[i] = %s\n", argv[users_start]);
                        external_users = external_users_init(argv, users_start, argc);
                        break; 
                	case 'F': fontdir = optarg; break;
    
                	default:  fprintf(stderr, help_msg, argv[0]); exit(1);
            	}
        }// FIN traitement des options

    read_user();
    read_high_scores(high_scores);
    // creation de la connexion et des fenetres 
    sock = xhextrisInit(argv, argc);
    if (!sock) {
    	fprintf(stderr,"xhextris: Can't guess socket connection.\n");
    	exit(100);
    }
    // Question 1) creation des couleurs si possible
    // Si l'option -background a �t� choisie => XrmPutRessource
    if(man_backcolor){
        fprintf(stderr, "Backcolor: %s\n", backcolor);
        initXrm(backcolor);
    }

    // Question 5)
    // Cr�er la fen�tre annexe
    if(multiplayer)
        xhextrisScoreMultiplayer();
    
    i = xhextrisColors(NUMBEROFPIECES);
    if (i) xhextrisEnd(i);
    // creation du contexte graphique pour les pieces
    hexgc = xhextrisFont(HEXFONTNAME,
		       fontdir,
		       PieceColors[NOPIECE].pixel,
		       PieceColors[NOPIECE].pixel);

    // creation du contexte graphique pour les scores
    gc = xhextrisFont(FONTNAME, "", white, black);
    gettimeofday(&tp, &tzp);
    srandom((int)(tp.tv_usec)); 

    while(end_all_games) {
        oldscore = -1;
        while ((score != oldscore)) {
            oldscore = score;
            speed = ACCEL(speed,rows);
        	tp.tv_sec = 0;
        	tp.tv_usec = speed;
        	FD_ZERO(&fdst);
        	FD_SET(sock,&fdst);
        	select(sock+1,&fdst,0,0,&tp);
        	key = xhextrisEvent();
        	if (key) do_choice(key,&npiece,&piece);
        }
        if (autom) choose_choice(game_over,&npiece,&piece);
        if (!game_over) update_drop(&npiece,&piece);
        if (game_over && !saved) {
            if (is_high_score(score, rows, total_pieces, high_scores))
	            write_high_scores(high_scores);
            saved=1;
        }
    }
    xhextrisEnd(0);
    exit(0);
}
