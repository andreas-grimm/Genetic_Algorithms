/*---------------------------------------------*/
/* Modul: basicwin.c         Version 1.0       */
/*                                             */
/* X11— Schnittgtelle fuer GENETICS            */
/*                                             */
/* Datum : 10. Juli 1991                       */
/*                                             */
/*---------------------------------------------*/

/* Standardincludes */
#include "genetics.h"
#include <stdio.h>

int screen_num;
char *progname = "genetic\0";

void GA_Basicwin_Initialisierung_Fenster_Statistik()
  {
  int x, y;
/* Text fuer das Icon */ 
  char *FS_icon = "Statistik";
  char *FS_name = "Genetische Algorithmen: Statistik";
  Pixmap icon_pixmap;
  int count;
  window_size = 0;
  border_width = 4;

/*Uebernahme der Groesse des Bildøchirmes aus den Sygtemdaten */
  screen_num = DefaultScreen(display);
  display_width = DisplayWidth(display, screen_num);
  display_height = DisplayHeight(display, screen_num);

  x = 0;
  y = 400;

  FS_Hoehe = (int)(1.25 * (MaxKnoten * MaxKnoten - MaxKnoten));
  FS_Breite = MaxGeneration + 50;
  Org_FS_Hoehe = FS_Hoehe;
  Org_FS_Breite= FS_Breite;

/* Aufbau eines einzelnen Fensters entsprechend den Voreinstellungen */
  F_Statistik =  XCreateSimpleWindow(display, RootWindow(display, screen_num),
         x, y, FS_Hoehe, FS_Breite, border_width, BlackPixel(display, 
         screen_num), WhitePixel(display, screen_num));

  XGetIconSizes(display, RootWindow(display, screen_num), &size_list,
                &count);

  Statistik_Size.flags = PPosition | PSize | PMinSize;
  Statistik_Size.x = x;
  Statistik_Size.y = y;

  Statistik_Size.width = FS_Breite;
  Statistik_Size.height = FS_Hoehe;
  Statistik_Size.min_width = 300;
  Statistik_Size.min_height = 200;

  XSetStandardProperties (display, F_Statistik, FS_name, FS_icon,
       icon_pixmap, &progname, 0, &Statistik_Size);
  XSelectInput (display, F_Statistik, ExposureMask | ButtonPressMask | StructureNotifyMask);

  GA_Basicwin_erzeuge_Grafik_Umgebung(F_Statistik, &FS_Grafik, font_info);
  XMapWindow(display, F_Statistik);
}

void GA_Basicwin_Initialisierung_Fenster_Baum()
{
  int x, y;
/* Text fuer das Icon */
  char *FB_icon = "bester Graph";
  char *FB_name = "Genetische Algorithmen : Graph ";
  Pixmap icon_pixmap;
  int count;

  window_size = 0;
  border_width = 4;
  
/* Uebernahme der Grouse des Bildschirnes aus den Systemdaten */
  screen_num = DefaultScreen(display);
  display_width = DisplayWidth(display, screen_num);
  display_height = DisplayHeight(display, screen_num);

  FB_Hoehe = MaxWesen * 10;
  FB_Breite = MaxWesen * 10;

/* Aufbau eines einzelnen Fensters entsprechend den Voreinstellungen */
  F_Baum = XCreateSimpleWindow(display, RootWindow(display,screen_num),
           x, y, FB_Hoehe, FB_Breite, border_width, BlackPixel(display,
           screen_num), WhitePixel(display, screen_num));

  XGetIconSizes (display, RootWindow (display, screen_num), &size_list,
           &count);

  Baum_Size.flags = PPosition | PSize | PMinSize;
  Baum_Size.x = x;
  Baum_Size.y = y;
  Baum_Size.width = FB_Breite;
  Baum_Size.height= FB_Hoehe;
  Baum_Size.min_width = 300;
  Baum_Size.min_height = 200;

  XSetStandardProperties (display, F_Baum, FB_name, FB_icon,
      icon_pixmap, &progname, 0, &Baum_Size);
  XSelectInput (display, F_Baum, ExposureMask | ButtonPressMask | StructureNotifyMask);

  GA_Basicwin_erzeuge_Grafik_Umgebung(F_Baum, &FB_Grafik, font_info);
  XMapWindow(display, F_Baum);
 }
 
 void GA_Basicwin_Initialisierung_Fenster_bester_Baum()
 {
    int x, y;
/* Text fuer das Icon */
    char *FB_icon = "Baum";
    char *FB_name = "Genetische Algorithmen: Baum";
    Pixmap icon_pixmap;
    int count;

    window_size = 0;
    border_width = 4;

/* Uebernahme der Groesse des Bildschirmes aus den Systemdaten */
    screen_num = DefaultScreen(display);
    display_width = DisplayWidth(display, screen_num);
    display_height= DisplayHeight(display, screen_num);

    x = y = 0;

    FbB_Hoehe = MaxWesen * 10;
    FbB_Breite = MaxWesen * 10;

/* Aufbau eines einzelnen Fensters entsprechend den Voreinstellungen */
    Fb_Baum = XCreateSimpleWindow(display, RootWindow(display, screen_num),
            x, y, FbB_Hoehe, FbB_Breite, border_width, BlackPixel(display, 
            screen_num), WhitePixel (display, screen_num));

    XGetIconSizes (display, RootWindow (display, screen_num), &size_list,
                   &count);

    Baum_Size.flags = PPosition | PSize | PMinSize;
    Baum_Size.x = x;
    Baum_Size.y = y;
    Baum_Size.width = FbB_Breite;
    Baum_Size.height = FbB_Hoehe;
    Baum_Size.min_width = 300;
    Baum_Size.min_height = 200;
    XSetStandardProperties(display, Fb_Baum, FB_name, FB_icon,
                       icon_pixmap, progname, 0, &Baum_Size);
    XSelectInput(display, Fb_Baum, ExposureMask | ButtonPressMask | StructureNotifyMask);

    GA_Basicwin_erzeuge_Grafik_Umgebung(Fb_Baum, &FbB_Grafik, font_info);
    XMapWindow(display, Fb_Baum);
 }

void GA_Basicwin_erzeuge_Grafik_Umgebung(Fenster, Grafik_Umgebung, font_info)
Window Fenster;
GC *Grafik_Umgebung;
XFontStruct *font_info;
{
  unsigned long valuemask = 0;
  XGCValues values;
  unsigned int line_width = 0;
  int line_style = LineSolid;
  int cap_style = CapButt;
  int join_style = JoinRound;

  *Grafik_Umgebung = XCreateGC(display, Fenster, valuemask, &values);
  XSetFont(display, *Grafik_Umgebung, font_info->fid);
  XSetLineAttributes(display, *Grafik_Umgebung, line_width, line_style,
                     cap_style, join_style);
}

void GA_Basicwin_load_font(font_info)
XFontStruct **font_info;
{
  char *fontname = "fixed";
  if ((*font_info = XLoadQueryFont(display, fontname)) == NULL)
    {
    GA_Benutzerschnittstelle(FEHLER,2,NULL);
    }
}

void GA_Basicwin_Initia1isierung_Gra1ik()
{
  int x, Dehnungsfaktor_X, Dehnungsfaktor_Y;
  int len10, len50, len100;
  char *Marke10 = "10";
  char *Marke50 = "50";
  char *Marke100= "100";
  len10 = strlen(Marke10);
  len50 = strlen(Marke50);
  len100= strlen(Marke100);
  Dehnungsfaktor_Y = FS_Hoehe / Org_FS_Hoehe;
  Dehnungsfaktor_X = FS_Breite / Org_FS_Breite;
  if (Dehnungsfaktor_X < 1)
    Dehnungsfaktor_X = 1;
  if (Dehnungsfaktor_Y < 1)
    Dehnungsfaktor_Y = 1;

  XDrawLine(display,F_Statistik,FS_Grafik, 30, 0, 30, FS_Hoehe) ;
  XDrawLine(display, F_Statistik, FS_Grafik, 0, (FS_Hoehe -30), 
            FS_Breite, (FS_Hoehe - 30));
  for (x = 30; x < FS_Breite; x += (5 * Dehnungsfaktor_X))
      XDrawLine(display, F_Statistik, FS_Grafik, x, (FS_Hoehe - 30), x, (FS_Hoehe - 25));
  for (x = 30; x < FS_Breite; x += (50 * Dehnungsfaktor_X))
      XDrawLine(display, F_Statistik, FS_Grafik, x, (FS_Hoehe - 30), x, (FS_Hoehe - 20));
  for (x = (FS_Hoehe - 30); x > 0; x-= (5 * Dehnungsfaktor_Y))
      XDrawLine(display, F_Statistik, FS_Grafik, 25, x, 30, x);
  for (x = (FS_Hoehe - 30); x > 0; x-= (50 * Dehnungsfaktor_Y))
      XDrawLine(display, F_Statistik, FS_Grafik, 20, x, 30, x);
  XDrawString(display, F_Statistik, FS_Grafik,
      30 + (10 * Dehnungsfaktor_X), FS_Hoehe -15,
        Marke10, len10);
  XDrawString(display, F_Statistik, FS_Grafik,
      30 + (50 * Dehnungsfaktor_X), FS_Hoehe - 15,
        Marke50, len50);
  XDrawString(display, F_Statistik, FS_Grafik,
      30 + (100 * Dehnungsfaktor_X), FS_Hoehe - 15,
        Marke100, len100);
}

void GA_Basicwin_TooSmall(win, gc, font_info)
Window win;
GC gc;
XFontStruct *font_info;
{
  char *string1 = "Zu klein ! ";
  int y_offset, x_offset;

  y_offset = font_info->ascent + 2;
  x_offset = 2;

  XDrawString(display, win, gc, x_offset, y_offset, string1,
              strlen(string1));
}
