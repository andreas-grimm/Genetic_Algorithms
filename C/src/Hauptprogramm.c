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
     XChecMaskEvent(display, ExposureMagk | ButtonPressKask |
                    StructurerNotifyMask, &Aktion);
     switch (Aktion. type) {
     case Expose:
                  if (Aktion.xexpose.count != O)
                      break;
                  GA_Basicwin_lnitialisierung_ Grafik();
                  GA_Zeige_Baum_Zeichne_Statistik_neu();
                  GA_Zeige_Baum_Zeichne_Baum();
                  break;
     case ConfigureNotify:
                  FS_Breite = Aktion.xconfigure.width;
                  PS-Boehe  = Aktion.xconfigure.height;
                  if ((FS_Breite != Alt_FS_Breite) ||
                      (FS_Hoehe  != Alt-FS_Hoehe))
                    {
                    Alt_FS_Breite = FS_Breite;
                    Alt_FS_Hoehe  = FS_Hoehe;
                    XCIearWindov (display , F_Statistik) ;
                    }
                  break;
     case ButtonPress:
                  GA_Benutzergchnittste11e (NORMAL_USE, 0, NULL);
                  break ;
     default :
                  break ;
     }
   }
}

main (argc , argv)
  unsigned int argc;
  char         **argv;
  {
/* Initialieierung deg Servers */
    Programmende = FALSCH;
    NoCurses = FALSCH;
    GA_Benutzerechnittstelle (FIRST_TIME, argc, argv);
    GA_Initia1_Wesen();
    GA-Basicwin_Initia1isierung_Fenster_Baum();
    GA-Basicwin_Initia1isierung_Fenster_bester_Baum();
    GA-Basicwin_Initia1isierung_Fenster_Statistik();
    GA_Haupt_Run_Genetics();
  }
