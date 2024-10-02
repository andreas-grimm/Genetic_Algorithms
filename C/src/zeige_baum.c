/*---------------------------------------------*/
/* Modul: zeige_baum.c       Version 1.0       */
/*                                             */
/* Graphische Ausgabe fuer  GENETICS           */
/*                                             */
/* Datum : 10 . Juli 1991                      */
/*                                             */
/*---------------------------------------------*/
#include <stdio.h>
#include "genetics.h"

void GA_Zeige_Baum_print_tree(Wesen)
int Wesen;
  {
  int x, y;
  for (x = 0; x < MaxKnoten; x++)
    {
    for (y = 0; y < MaxKnoten; y++)
      printf(" %i ", Individuum[x][y][Wesen]);
    printf("\n");
    }
  }

void GA_Zeige_Baum_best_tree()
  {
  int x, y;
  for (x = 0; x < MaxKnoten; x++) 
    {
    for (y = 0; y < MaxKnoten; y++)
      printf(" %i ", Best_Individuum[x][y]);
    printf("\n");
    }
  }

void GA_Zeige_Baum_Zeichne_Statistik_neu()
  {
  int Dehnungsfaktor_X, Dehnungsfaktor_Y, x, y, z;
  Dehnungsfaktor_Y = FS_Hoehe / Org_FS_Hoehe;
  Dehnungsfaktor_X = FS_Breite/ Org_FS_Breite;
  if (Dehnungsfaktor_X < 1)
    Dehnungsfaktor_X = 1;
  if (Dehnungsfaktor_Y < 1)
    Dehnungsfaktor_Y = 1;
  for (z = 0; z < (Generation - 2); z++)
    {
    x = 30 + z * Dehnungsfaktor_X;
    y = (FS_Hoehe - 30) - (Statistik[z][BESTER] * Dehnungsfaktor_Y);
    XDrawPoint(display,F_Statistik,FS_Grafik, x, y);
    y = (FS_Hoehe - 30) - (Statistik[z][MITTEL] * Dehnungsfaktor_Y);
    XDrawPoint(display, F_Statistik, FS_Grafik, x, y);
    y = (FS_Hoehe - 30) - (Statistik[z][SCHLECHT] * Dehnungsfaktor_Y);
    XDrawPoint(display, F_Statistik, FS_Grafik, x, y);
    }
  }

void GA_Zeige_Baum_Zeichne_Statistik()
  {
  int Dehnungsfaktor_X, Dehnungsfaktor_Y, x, y;
  Dehnungsfaktor_Y = FS_Hoehe / Org_FS_Hoehe;
  Dehnungsfaktor_X = FS_Breite/ Org_FS_Breite;
  if (Dehnungsfaktor_X < 1)
    Dehnungsfaktor_X = 1;
  if (Dehnungsfaktor_Y < 1)
    Dehnungsfaktor_Y = 1;
  x = 30 + Generation * Dehnungsfaktor_X;
  y = (FS_Hoehe - 30) - (Statistik[Generation][BESTER] * Dehnungsfaktor_Y);
  XDrawPoint(display,F_Statistik,FS_Grafik, x, y) ;
  y = (FS_Hoehe - 30) - (Statistik[Generation][MITTEL] * Dehnungsfaktor_Y);
  XDrawPoint(display, F_Statistik, FS_Grafik, x, y);
  y = (FS_Hoehe - 30) - (Statistik[Generation][SCHLECHT] * Dehnungsfaktor_Y);
  XDrawPoint(display, F_Statistik, FS_Grafik, x, y);
  }

void GA_Zeige_Baum_Zeichne_Baum()
  {
  int Koordinate[MaxIndividuen][2], x, y, z, Zeichenlaenge;
  char Zeichen[4];
  for (x = 0; x < MaxWesen; x++)
    {
    Koordinate[x][XKOORDINATE] = 0;
    Koordinate[x][YKOORDINATE] = 0;
    }
  XClearWindow (display, F_Baum);
  y = x = 0;
  for (y = 0; y < MaxKnoten; y++)
    {
    for (z = 0; z < MaxKnoten; z++)
      {
      if (Beste_Tiefe[z] == y)
        {
        Koordinate[z][XKOORDINATE] = (x++ * 30 + 15);
        Koordinate[z][YKOORDINATE] = (y * 50 + 15);
        }
      }
    x = 0;
    }
  for (y = 0; y < MaxKnoten; y++)
    {
    (void) sprintf(Zeichen,"%d",y) ;
    Zeichenlaenge = strlen(Zeichen);
    XDrawString(display, F_Baum, FB_Grafik, Koordinate[y][XKOORDINATE],
                                            Koordinate[y][YKOORDINATE],
                                            Zeichen, Zeichenlaenge);
    }
  for (x = 0; x < MaxKnoten; x++)
    for (y = 0; y < MaxKnoten; y++)
      if (Best_Individuum[x][y] == 1)
        {
        if (Koordinate[x][YKOORDINATE] < Koordinate[y][YKOORDINATE])
          XDrawLine(display,F_Baum,FB_Grafik,Koordinate[x][XKOORDINATE],
                                             Koordinate[x][YKOORDINATE],
                                             Koordinate[y][XKOORDINATE],
                                             Koordinate[y][YKOORDINATE] -10);
        if (Koordinate[x][YKOORDINATE] > Koordinate[y][YKOORDINATE])
          XDrawLine(display,F_Baum,FB_Grafik,Koordinate[x][XKOORDINATE],
                                             Koordinate[x][YKOORDINATE] -10,
                                             Koordinate[y][XKOORDINATE],
                                             Koordinate[y][YKOORDINATE]);
        if (Koordinate[x][YKOORDINATE] == Koordinate[y][YKOORDINATE])
          XDrawLine(display,F_Baum,FB_Grafik,Koordinate[x][XKOORDINATE],
                                             Koordinate[x][YKOORDINATE] +3,
                                             Koordinate[y][XKOORDINATE],
                                             Koordinate[y][YKOORDINATE] +3);
        }
  }

void GA_Zeige_Baum_Zeichne_bester_Baum(bester_Baum) 
int bester_Baum;
  {
  int Koordinate[MaxIndividuen][2], x, y, z, Zeichenlaenge;
  char Zeichen[4];
  for (x = 0; x < MaxWesen; x++)
    {
    Koordinate[x][XKOORDINATE] = 0;
    Koordinate[x][YKOORDINATE] = 0;
    }
  XClearWindow (display, Fb_Baum);
  y = x = 0;
  for (y = 0; y < MaxKnoten; y++)
    {
    for (z = 0; z < MaxKnoten; z++)
      {
      if (Tiefe[z][bester_Baum] == y)
        {
        Koordinate[z][XKOORDINATE] = (x++ * 30 + 15);
        Koordinate[z][YKOORDINATE] = (y * 50 + 15);
        }
      }
    x = 0;
    }  
  for (y = 0; y < MaxKnoten; y++)
    {
    (void) sprintf(Zeichen,"%d",y);
    Zeichenlaenge = strlen(Zeichen);
    XDrawString(display, Fb_Baum, FbB_Grafik, Koordinate[y][XKOORDINATE] ,
                                            Koordinate[y][YKOORDINATE],
                                            Zeichen, Zeichenlaenge) ;
    }
  for (x = 0; x < MaxKnoten; x++)
    for (y = 0; y < MaxKnoten; y++)
      if (Individuum[x][y][bester_Baum] == 1)
        {
        if (Koordinate[x][YKOORDINATE] < Koordinate[y][YKOORDINATE])
          XDrawLine(display,Fb_Baum,FbB_Grafik,Koordinate[x][XKOORDINATE],
                                            Koordinate[x][YKOORDINATE],
                                            Koordinate[y][YKOORDINATE],
                                            Koordinate[y][YKOORDINATE] -10);
        if (Koordinate[x][YKOORDINATE] > Koordinate[y][YKOORDINATE])
          XDrawLine(display,Fb_Baum,FbB_Grafik,Koordinate[x][XKOORDINATE],
                                            Koordinate[x][YKOORDINATE] -10,
                                            Koordinate[y][XKOORDINATE],
                                            Koordinate[y][YKOORDINATE]);
        if (Koordinate[x][XKOORDINATE] == Koordinate[y][YKOORDINATE])
          XDrawLine(display,Fb_Baum,FbB_Grafik,Koordinate[x][XKOORDINATE],
                                            Koordinate[x][YKOORDINATE] +3,
                                            Koordinate[y][XKOORDINATE],
                                            Koordinate[y][YKOORDINATE] +3);
        }
  }
