/*---------------------------------------------*/
/*                                             */
/* Modul: genetics.h         Version 1.0       */
/*                                             */
/* Globale Variablendefinitionen fuer GENETICS */
/*                                             */
/* Datum : 31 . August 1991                    */
/*                                             */
/*---------------------------------------------*/

/* Standardincludes */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/PushB.h>

#include <stdio.h>
#include <curses.h>

/* Globale Fegtlegungen */
#define      BITKAPDEPTH         1
#define      TOO_SHALL           0
#define      BIG_ENOUGH          1

#define      XKOORDINATE         0
#define      YKOORDINATE         1

#define      WAHR                1
#define      FALSCH              0
#define      BESTER              0
#define      MITTEL              1
#define      SCHLECHT            2

#define      FIRST-TIME          0
#define      NORMAL_USE          1
#define      LAST_TIME           2
#define      FEHLER              3

#define      BREITENSUCHE        0
#define      TIEFEYSUCHE         1
#define      ARIADNE             2

#define      MarNachfolger       2
#define      MaxIndividuen       50
#define      MaxIndividuenHalbe  25

int          NoCurses;
int          NoX11;
int          MaxGeneration;
int          MaxKnoten;
int          MaxWesen;
int          MaxWesenHalbe;
long float   M_Wahrschein;

/* Definitionen fuer den Zufallggenerator */
long         Zufa11_r[97];
short        Zufall_iif;

/* Definitionen fuer XII */
Display      *display;
GC           FB_Grafik, FS_Grafik, FbB_Grafik;
XEvent       Aktion;
XSizeHints   Baum_Size, Statistik_Size;
XIconSize    *size_list;
XFontStruct  *font_info;
unsigned int icon_width, icon_height;  
Window       F_Statistik, F_Baum, Fb_Baum;

/* Daten fuer das Statigtik— Fenster */
unsigned int FS_Hoehe, FS_Breite, Org_FS_Hoehe, Org_FS_Breite;

/* Daten fuer das Baum—Fenster */
unsigned int FB_Hoehe, FB_Breite, Org_FB_Hoehe, Org_FB_Breite;
int          FB—aktiv; 

/* Daten fuer den besten Baum */
unsigned int FbB_Hoehe, FbB—Breite, Org_FbB_Hoehe, Org_FbB_Breite;
unsigned int border_width, display—width, display-height;
int          windov_size;

short        Generation, Programmende;
int          GesamtFitness, Beste_Fitness, Best_Wesen;
int          Korrektur—Ordnung, Korrektur_Topologie;

int          Individuum[100][100][MaxIndividuen];
int          Root[MaxIndividuen];
int          Tiefe[100][NaxIndividuen], Beste_Tiefe[100];
int          Fitness [Maxlndividuen];
int          Statistik[100][3];
int          Best-Individuum[100][100];
int          Ordnungszahl[MaxIndividuen];
