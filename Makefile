
# Attention, ceci doit etre un chemin absolu accessible au serveur X
BASE=~/Documents/Master/Semestre2/ACII/Projet
CONNU=$(BASE)/
SOL=$(CONNU)
F=/tmp/

B=xhextris
M=Makefile
H=header.h

D1=hevent
D2=hcolors
D3=hcurtain
D4=hend
D5=hscores
D6=hhex
D7=hhomepage
D8=hsetspeed
D9=hfont
D10=hinit
D11=hevents
D12=hresource
D13=hexternal
D14=hscoresmultiplayer
D15=hsend

G=grille
S=scores
A=globalx

ALLD=$(CONNU)$(G).c $(CONNU)$(S).c $(CONNU)$(A).c

ALLS=$(SOL)$(D1).c $(SOL)$(D2).c $(SOL)$(D3).c $(SOL)$(D4).c $(SOL)$(D5).c $(SOL)$(D6).c $(SOL)$(D7).c $(SOL)$(D8).c $(SOL)$(D9).c $(SOL)$(D10).c $(SOL)$(D11).c $(SOL)$(D12).c $(SOL)$(D13).c $(SOL)$(D14).c $(SOL)$(D15).c

ALLO=$(G).o $(S).o $(A).o $(D1).o $(D2).o $(D3).o $(D4).o $(D5).o $(D6).o $(D7).o $(D8).o $(D9).o $(D10).o $(D11).o $(D12).o $(D13).o $(D14).o $(D15).o

O=-Wall -O4 -g
I=-I/usr/include/X11 -I$(CONNU)
L=-L/usr/lib/X11

l=-lX11

$(B):   $(ALLO) $F/hex20.pcf
	gcc $L $l $(ALLO) -o $(B) `pkg-config --libs --cflags x11`

%.o:	$(CONNU)%.c $(B).h
	gcc $O $I -c $< -o $@

%.o:	$(SOL)%.c $(B).h
	gcc $O $I -c $< -o $@

$(F)/hex20.pcf: $(CONNU)hex20.bdf
	@if [ -d $F ] ; then : ; else mkdir $F ; fi
	echo $F
	bdftopcf <  $(CONNU)hex20.bdf > $@
	@chmod 444 $@
	mkfontdir $F

projet: exagere relais_ligne relais_score

exagere: hexagere.o
	gcc $L $l -o $@ $^

hexagere.o: hexagere.c xhextris.h
	gcc $I -c $< -o $@

relais_ligne: relais_ligne.o
	gcc $L $l -o $@ $^

relais_ligne.o: relais_ligne.c xhextris.h
	gcc $I -c $< -o $@

relais_score: relais_score.o
	gcc $L $l -o $@ $^

relais_score.o: relais_score.c xhextris.h
	gcc $I -c $< -o $@

test:
	./$(B) -a

raz:
	rm -rf $(ALLO) $(B) $(B).h 

# Construction automatique du .h en fonction de l'evolution des fichiers
# Si rien de neuf, reprendre le vieux pour ne pas recompiler a chaque fois

$(B).h: $(CONNU)$(H) $(M) $(ALLD) $(ALLS)
	@if [ -f $@ ] ; then mv $@ $@.old ; else > $@.old ;  fi
	@(if [ "`uname`" == "Darwin" ]; then echo '#include <strings.h>' ; else echo '#include <string.h>'; fi) >> $@ 
	@grep -v '^#include *<string.*h>' $(CONNU)$(H) >>  $@
	@echo "#define HEXFONTDIR \"$F\"" >> $@
	@echo "#define HIGHSCOREFILE \"$(B)-$(S)\"" >> $@
	@awk -F[=\;{] '/^[a-zA-Z]/ {print "extern " $$1 ";"}' $(ALLD) $(ALLS) >> $@
	@if diff $@ $@.old >/dev/null;then mv $@.old $@  ; else rm $@.old; fi

# Construction de l'index des fonctions utilisees:
# toutes celles ayant au moins une majuscule et une minuscules
# et pas celle portant le nom de l'application

$(B).idx:       $(ALLS) $(M)
	@awk -F'/\\*' '{print $$1}' $(ALLS) | \
	tr "{}[]().,;:?<>#\t' =\!+%|\*&^-" "\012" | grep "^[A-Z].*[a-z]" | \
	grep -v $(B) | sort  -u | sed 's/True//g;/./s/^/\\par /g' > $(B).idx
	@wc  $(B).idx
