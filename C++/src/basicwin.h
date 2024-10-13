/*---------------------------------------------*/
/* Modul: basicwin.h         Version 1.0       */
/*                                             */
/* X11— Schnittgtelle fuer GENETICS            */
/*                                             */
/* Datum : 10. Juli 1991                       */
/*                                             */
/*---------------------------------------------*/

#ifndef BASICWIN_H
#define BASICWIN_H

void GA_Basicwin_Initialisierung_Fenster_Statistik();
void GA_Basicwin_Initialisierung_Fenster_Baum();
void GA_Basicwin_Initialisierung_Fenster_bester_Baum();
void GA_Basicwin_erzeuge_Grafik_Umgebung(Window Fenster, GC *Grafik_Umgebung, XFontStruct *font_info);
void GA_Basicwin_load_font(XFontStruct **font_info);
void GA_Basicwin_Initia1isierung_Gra1ik();
void GA_Basicwin_TooSmall(Window win, GC gc, XFontStruct *font_info);

#endif
