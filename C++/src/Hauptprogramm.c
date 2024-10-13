/*---------------------------------------------*/                           
/* Modul: Hauptprogramm.c    Version 1.0       */                           
/*                                             */                           
/* Globale Variablendefinitionen fuer GENETICS */                           
/*                                             */                           
/* Datum : 31 . August 1991                    */                           
/*                                             */                           
/*---------------------------------------------*/                           

#include "genetics.h"

void GA_Haupt_Run_Genetics()
  {
  unsigned int Alt_FS_Hoehe, Alt_FS_Breite;
  while (Programmende == FALSCH)
    {
      if (Generation < MaxGeneration)
        {
        GA_Kontrolle_main();
        GA_Ordnung_main();
        GA_Bewert_main();
        GA_Fpflanz_main();
        GA_Zeige_Baum_Zeichne_Statistik();
        Generation++;
        }
     XCheckMaskEvent(display, ExposureMask | ButtonPressMask |
                    StructureNotifyMask, &Aktion);
     switch (Aktion. type) {
     case Expose:
                  if (Aktion.xexpose.count != 0)
                      break;
                  GA_Basicwin_lnitialisierung_Grafik();
                  GA_Zeige_Baum_Zeichne_Statistik_neu();
                  GA_Zeige_Baum_Zeichne_Baum();
                  break;
     case ConfigureNotify:
                  FS_Breite = Aktion.xconfigure.width;
                  FS_Hoehe  = Aktion.xconfigure.height;
                  if ((FS_Breite != Alt_FS_Breite) ||
                      (FS_Hoehe  != Alt_FS_Hoehe))
                    {
                    Alt_FS_Breite = FS_Breite;
                    Alt_FS_Hoehe  = FS_Hoehe;
                    XClearWindow(display , F_Statistik) ;
                    }
                  break;
     case ButtonPress:
                  GA_Benutzerschnittste11e (NORMAL_USE, 0, NULL);
                  break ;
     default :
                  break ;
     }
   }
}

void main(argc , argv)
  unsigned int argc;
  char         **argv;
  {
/* Initialieierung deg Servers */
    Programmende = FALSCH;
    NoCurses = FALSCH;
    GA_Benutzerechnittstelle (FIRST_TIME, argc, argv);
    GA_Initia1_Wesen();
    GA_Basicwin_Initia1isierung_Fenster_Baum();
    GA_Basicwin_Initia1isierung_Fenster_bester_Baum();
    GA_Basicwin_Initia1isierung_Fenster_Statistik();
    GA_Haupt_Run_Genetics();
  }
