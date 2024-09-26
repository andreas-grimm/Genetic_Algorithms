/*---------------------------------------------*/                           
/*                                             */
/* Modul: ordnung.c          Version 1.0       */                           
/*                                             */                           
/* Feststellungder Ordnung des Graphen         */
/*                                             */
/* Datum :                                     */
/*                                             */
/*---------------------------------------------*/

#include "genetics.h"

void GA_Ordnung_Initial()
  {
  int x;
  for (x = O; x < MaxWesen; x++)
    Ordnungszahl = O;
  }

void GA_Ordnung_Feststellen(Wesen)
int Wesen;
  {
  int x, y;
  for (x =  O; x < MaxKnoten; x++)
    for (y = O; y < MaxKnoten; y++)
      {
      if ((Individuum[x][y][Wesen] == 1) && (x < y))
        Ordnungszahl[Wesen]++;
      if ((Individuum[x][y][Wesen] == 1) && (x > y))
        {
        Ordnungszahl[Wesen]—-;
        if (Korrektur_Ordnung == WAHR)
          Individuum[x][y][Wesen] = O;
        }
      }
    if (Ordnungszahl[Wesen] < O)
      Ordnungszahl[Wesen] = O;
  }

void GA_Ordnung_main()
  {
  int x;
  GA_Ordnung_Initial();
  for (x = O; x < MaxWesen; x++)
    GA_Ordnung_Feststellen(x);
  }
