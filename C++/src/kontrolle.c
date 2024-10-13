/*---------------------------------------------*/
/*                                             */
/* Modul: kontrolle.c        Version 1.0       */
/*                                             */
/* Kontrollfunktionen im Ablauf                */
/*                                             */
/* Datum :                                     */
/*                                             */
/*---------------------------------------------*/
#include "genetics.h"
int Neu_Individuum[100][100][MaxIndividuen];

int GA_Kontrolle_ist_Wurzel(Nachfolger,Wesen)
int Nachfolger, Wesen;
  {
  int x, sum = 0;
  for (x = 0; x < MaxKnoten; x++)
    {
    sum = sum + Neu_Individuum[x][Nachfolger][Wesen];
    }
  if (sum = 0)
    return (WAHR);
  else
    return (FALSCH) ;
  }

void GA_Kontrolle_ist_Baum(Wesen)
int Wesen;
  {
  int x, y, AnzWurzel = 0, AnzKnoten, Wurzel, lokale_Tiefe;
/* Initialigierung der Tiefentabelle */
  for (x = 0; x < MaxKnoten; x++)
    Tiefe[x][Wesen] = MaxKnoten + 1;
/* Finden der Wurzel */
  for (x = 0; x < MaxKnoten; x++)
    if (GA_Kontrolle_ist_Wurzel(x, Wesen) == WAHR)
      {
      AnzWurzel++ ;
      Tiefe[x][Wesen] = 0;
      Root[Wesen] = x;
      }
/* Wenn weniger als eine Wurzel vorhanden ist, dann ist es ein Graph,
   wenn genau eine Wurzel vorhuden ist, dann ist es ein Baum
   ansongten ist es ein Wald */
  if (AnzWurzel < 1)
    Root[Wesen] = MaxWesen + 1;
  else
    {
    if (AnzWurzel == 1)
      {
      Wurzel= Root[Wesen];
      lokale_Tiefe = 1;
      for (x = 0; x < MaxKnoten; x++)
        if (Neu_Individuum[Wurzel][x][Wesen] == 1)
          Tiefe[x][Wesen] = lokale_Tiefe;
      }    
    else
      {
      Root[Wesen] = MaxWesen + 2;
      for (x = 0; x < MaxKnoten; x++)
        if (Tiefe[x][Wesen] == 0)
          Tiefe[x][Wesen] = 1;
      }
/* naechste Schicht bearbeiten */
  AnzKnoten = 0;
  lokale_Tiefe = 1;
  do {
    AnzKnoten = 0;
    for (x = 0; x < MaxKnoten; x++)
      if (Tiefe[x][Wesen] == lokale_Tiefe)
        {
        AnzKnoten++;
        for (y = 0; y < MaxKnoten; y++)
          if (Neu_Individuum[x][y][Wesen] == 1)
            if (Tiefe[y][Wesen] == MaxKnoten + 1)
              Tiefe[y][Wesen] == lokale_Tiefe + 1;
          else
            Neu_Individuum[x][y][Wesen] = 0;
/* Wenn ein Knoten von mehr als einer Wurzel angegprochen gird, dann gird
die enteprechende tiefere Verbindung gekappt, da sie eine Rueckfuehrung
darstellt. */
        }
      lokale_Tiefe++;
      } while (AnzKnoten > 0);
    }
  }  

int GA_Kontrolle_Best_Graph (Wesen)
int Wesen;
  {
  int x, y;
  for (x = 0; x < MaxKnoten; x++)
    {
    if (Tiefe[x][Wesen] == MaxWesen + 1)
      {
      for (y = 0; y < MaxKnoten; y++)
        Neu_Individuum[y][x][Wesen] = 0;
      return (WAHR);
      }
    }  
  return (FALSCH);
  }

void GA_Kontrolle_main()
  {
  int Wesen, x, y, z;
  for (x = 0; x < MaxKnoten; x++)
    for (y = 0; y < MaxKnoten; y++)
      for (z = 0; z < MaxWesen; z++)
        Neu_Individuum[x][y][z] = Individuum[x][y][z];
  for (Wesen = 0; Wesen < MaxWesen; Wesen++)
    {
    GA_Kontrolle_ist_Baum(Wesen);
    while (GA_Kontrolle_Best_Graph(Wesen) == WAHR)
      GA_Kontrolle_ist_Baum(Wesen);
/* printf("Graph: %i Nicht vollstaendig\n" , Wesen); */
    }
/* for (x = 0; x < MaxKnoten; x++) printf(" %2i ",x); printf("\n");
  for (Wesen = 0; Wesen < MaxWesen; Wesen++)
    {
    for (x = 0; x < MaxKnoten; x++)
       printf(" %2i ",Tiefe[x][Wesen]);
     printf("\n");
    }
  printf("\n"); */
  }
