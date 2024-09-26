LIB=-lXm -lXt -lX11 lPW -lnsl_s -lnet -lc -lbad -lcurses -lm OBJ=Hauptprogramm.o zeige_baum.o zufall.o initial.o kontrolle.o bewert.o fpflanz.o basicwin.o benutz.o ordnung.o domenu.o
genetic: $(0BJ}
  cc -O ${OBJ} -o genetics S{LIB}
Hauptprogramm.o: 	Hauptprogramm.c zeige_baum.c benutz.c genetics.h
benutz.o:			benutz.c domenu.c domenu.h genetics.h
zeige_baum.o:		zeige_baum.c genetics.h
initial.o:			initial.c zeige_baum.c zufall.c genetics.h
kontrolle.o:    	kontrolle.c genetics.h
bewert.o:			bewert.c genetics.h
fpflanz. o:			fpflanz.c zufall.c genetics.h
basicwin.o:			basicwin.c genetics.h
zufall.o:			zufall.c genetics.h
domenu. o:			domenu.c domenu.h
ordnung. o:			ordnung.c genetics.h