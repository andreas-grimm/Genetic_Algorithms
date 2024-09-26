/*---------------------------------------------*/
/*                                             */
/* Modul: Benutz.c           Version 1.0       */
/*                                             */
/* Benutzergchnittgtelle fuer GENETICS         */
/*                                             */
/* Datum : 20. August 1991                     */
/*                                             */
/*---------------------------------------------*/
#include "genetics.h"
#include "donenu.h"

char •menutab[5] = {
    "Startøn des Systems",
    "Aendern der Parameter",
    "",
    "Abbrechen",
    };

struct menu Nenu = {
    4, 25,
    "Genetische Algorithnen: Auswahlmenu",
    &menutab[0]
    };

static XmStringCharSet OSF_CharSet = (XmStringCharSet) XmSTRING_DEFAULT_CHARSET;

void GA_Benutz_error(Fehlerart)
int Fehlerart;
  {
  attron(A_BLINK I A_REVERSE);
  switch(FehIerart) {
    case 1:
      mvaddstr(12, 10, "Genetics:  Keine Verbindung mit dem X-Server moeglich\0");
      break;
    case 2:
      mvaddstr(12, 10, "Genetics: Definierter X11-Font nicht auffindbar\0");
    default :
        mvaddstr(12, 10, "Genetics: Nicht klassifizierbarer Fehler\0");
        break;
    }
  attroff(A_BLINK I A_REVERSE);
  refresh();
  endwin();
  exit(1);
  }

void GA_Benutz_C1earScreen()
  {
  clear() ;
  mvaddstr(0, 5, "Genetieche Algorithmen: Selbstorganisierende Datenstrukturen\0");
  refresh();
  }

void GA_Benutz_Vorinitial()
  {
  Korrektur_Ordnung = FALSCH;
  Korrektur_Topologie = FALSCH;
  MaxWesen = 20;
  MaxWesenHalbe = 10;
  MaxGeneration = 300;
  NaxKnoten = 20;
  H_Wahrschein = 0.0005;
  }

void GA_Benutz_Einstellung()
  {
  int Eingabe, weiter = FALSCH;
  float FEingabe. Rechfeld;
  long float LfEingabe ;
  while (weiter == FALSCH)
    {
    GA_Benutz_CiearScreen() ;
    mvaddstr(1, 50,"Eingabe : O = Nein, 1 = Ja\O ");
    mvaddstr(3, 5, "Systemparameter : \O");
    mvaddstr(4, 5, "Maximale Generationen :\O");
    mvaddstr(4, 45, " Anzahl der Knoten : \0");
    mvaddstr(5, 5, "Mutationswahrscheinlichkeit : \0");
    mvaddstr(5, 45, "Anzahl der Individuen : \O "); 
    mvaddstr(7, S, "Fitnessfunktionen: \0");
    mvaddstr(8, 5, "Verteilung Fitness : \0");
    mvaddstr(21, 5, "Korrektur : \O");
    mvaddstr(22, 5, "Ordnung : \O");
    mvaddstr(22, 45, "Topologie : \O");
    mvaddstr(23, 5, "O.K. ?\O");
    refresh();
/* Eingabe Anzahl der Generationen */
    do {
      move(4,34); scanw("%i",&Eingabe);
      printw("%i", Eingabe);
      } while ((Eingabe < 1) || (Eingabe > 999));
    MaxGeneration = Eingabe;
    refregh();
/* Eingabe Anzahl der Knoten */
    do {
      move(4, 65); scanw("%i",&Eingabe);
      printw("%i", Eingabe);
      } while ((Eingabe < 10) || (Eingabe > 99));
    MaxKnoten = Eingabe;
    refresh();
/* Eingabe der Mutationswahrscheinlichkeit */
    do {
      move(5, 34); scanw("%lf",&LfEingabe);
     printw( "%lf" ,LfEingabe) ;
    } while ((LfEingabe >= 1.0) || (LfEingabe < 0.000005));
    M_Wahrschein = LfEingabe;
    refresh() ;
/* Eingabe der Populationsgroesse */
    do {
      move(S, 69); scanw("%i", &Eingabe);
      printw("%i", Eingabe);
    } while ((Eingabe < 2) || (Eingabe > 50));
    MaxWesen = Eingabe ;
    MaxWesenHalbe = MaxWesen / 2;
    refresh() ;
/* Verteilung der Fitnessfunktionen */
    do {
      move(8, 34); scanw("%f",&FEingabe);
      Rechfeld = 1 — FEingabe;
      printw("%1.2f:%1.2f", FEingabe, Rechfeld);
    } while ((FEingabe > 1.0) || (FEingabe < 0.01));
    Fit_Verteil = FEingabe;
    refresh() ;
/* Eingabe Schalter fuer Ordnungs-Korrektur */
    do {
      move(22, 17); scanw("%i",&Eingabe);
      printw("%i", Eingabe);
      } vhile((Eingabe != O) && (Eingabe != 1));
    if (Eingabe == 1)
      Korrektur_Ordnung = WAHR;
    else
      Korrektur_Ordnung = FALSCH;
    refresh() ;
/* Eingabe Schalter fuer Topologie—Korrektur */
    do {
      move(22, S7); scanw("%i",&Eingabe);
      printw("%i",Eingabe);
      } while((Eingabe != O) && (Eingabe != 1));
    if (Eingabe == 1)
      Korrektur—Topologie = WAHR;
    else
      Korrektur—Topologie = FALSCH;
    refresh();
    do {
      move(23, 12); scanw("%i",&Eingabe);
      printw("%i",Eingabe);
      } while ((Eingabe != O) && (Eingabe != 1));
    if (Eingabe == 1)
      veiter = WAHR;
    refresh();
    }
  }

void GA_Benutz_Startmenu()
  {
  int Ergebnis, weiter;
  GA_Benutz_VorinitiaI();
  veiter = FALSCH;
  while (weiter == FALSCH)
    {
    GA_Benutz_ClearScreen();
    Ergebnis = GA_domenu_main(&Menu);
    svitch(Ergebnis)
      {
      case O:  weiter = WAHR;
               break;
      case 1:  GA_Benutz_Einstellung();
               break;
      default: resetty();
               endwin();
               exit(0);
      }
    }
  }

void GA_Benutz_Statusausgabe(Generation, ODF, GF, PGF ,BF, MaxWert,
                             MinWert, PMaxWert, PMinWert)
int Generation, OGF, GF, BF, MaxWert, MinWert;
double PGF, PMaxWert, PMinWert;
  {
  GA_Benutz_CIearScreen();
  mvaddstr(5,5,"Generation : \O");
  mvaddstr(7,5, "Erreichbare Fitness: \0");
  mvaddstr(8,S, "Erreichte   Fitness: \0");
  mvaddstr(8,45,"in Prozent : \O");
  mvaddstr(10,5, "Beste Einzelwerte : \0") ;
  mvaddstr(11,5, "in Ablauf             :\0");
  mvaddstr(12,5, "in dieser Generation :\0");
  mvaddstr(12,45, "prozentualer Anteil :\0");
  mvaddstr(14,5, "Schlechteste Einzelwerte :\0");
  mvaddstr(15,5, "in dieser Generation :\0");
  mvaddstr(15,45, "prozentualer Anteil :\0");
  move(5,20); printw("%i", Generation);
  move(7,26); printw("%i", OGF);
  move(8,26); printw("%i", GesamtFitness);
  move(8,60); printw("%2.2f", PGF);
  move(11,29); printw("%i", BF);
  move(12,29); printw("%i", MaxWert);
  move(12,67); printw("%2.2f", PMaxWert);
  move(15,29); printw("%i", MinWert);
  move(15,67); printw("%2.2f", PMinWert);
  refresh();
  }

void GA_Benutzerschnittste11e (Art, argc, argv)
int Art, argc;
char **argv;
  {
  char *progname = "Genetic";
  char *display_name = NULL;
  if (Art == FIRST_TIHE)
    {
    initscr(); savetty(); cbreak(); nonl(); echo(); standend();
    GA_Benutz_Startmenu();
    GA_Benutz_C1earScreen();
    mvaddgtr(10, 12, "Initialisierung X-Windovs : \0");
    refresh();
    XtToolkitInitialize();
    if ((display = XtOpenDisp1ay(NULL, NULL, argv[O], "Mwm", NULL,
                                 O, &argc, argv)) == NULL)
      GA_Benutz_error(I ) ;
    GA _Basicwin_load_font(&font_info);
    mvaddstr(10, 39, "O.K. \0");
    refresh();
    }
  if (Art == NORMAL_USE)
    {
    XUnloadFont (display, font_info->fid);
    XFreeGC (display, FS-Grafik);
    XCloseDisplay (display) ;
    Programmende = WAHR;
    resetty();
    endvin();
    }
  if (Art == FEHLER)
    {
    GA_Benutz_error(argc);
    }
  }
