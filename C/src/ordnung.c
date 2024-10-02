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
  for (x = 0; x < MaxWesen; x++)
    Ordnungszahl[x] = 0;
  }

void GA_Ordnung_Feststellen(Wesen)
int Wesen;
  {
  int x, y;
  for (x =  0; x < MaxKnoten; x++)
    for (y = 0; y < MaxKnoten; y++)
      {
      if ((Individuum[x][y][Wesen] == 1) && (x < y))
        Ordnungszahl[Wesen]++;
      if ((Individuum[x][y][Wesen] == 1) && (x > y))
        {
        Ordnungszahl[Wesen]--;
        if (Korrektur_Ordnung == WAHR)
          Individuum[x][y][Wesen] = 0;
        }
      }
    if (Ordnungszahl[Wesen] < 0)
      Ordnungszahl[Wesen] = 0;
  }

void GA_Ordnung_main()
  {
  int x;
  GA_Ordnung_Initial();
  for (x = 0; x < MaxWesen; x++)
    GA_Ordnung_Feststellen(x);
  }
