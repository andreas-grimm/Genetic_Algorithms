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
int Neu_Individuum[1OO][1OO][Maxlndividuen];

int GA_Kontrolle_ist_Wurzel(Nachfolger,Wesen)
int Nachfolger, Wesen;
  {
  int x, sum = O;
  for (x = O; x < MaxKnoten; x++)
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
  int x, y, AnzWurzel = O, AnzKnoten, Wurzel, loka1e_Tiefe;
/* Initialigierung der Tiefentabelle */
  for (x = O; x < MaxKnoten; x++)
    Tiefe[x][Wesen] = MaxKnoten + 1;
/* Finden der Wurzel */
  for (x = O; x < MaxKnoten, x++)
    if (GA_Kontrolle_ist_Wurzel(x, Wesen) == WAHR)
      {
      AnzWurzel++ ;
      Tiefe[x][Wesen] = O;
      Root[Wesen] = x;
      }
/* Wenn weniger als eine Wurzel vorhanden ist, dann ist es ein Graph,
   wenn genau eine Wurzel vorhuden ist, dann ist es ein Baum
   ansongten ist es ein Wald */
  if (AnzWurze1 < 1)
    Root[Wesen] = MaxWesen + I;
  else
    {
    if (AnzWurzel == 1)
      {
      Wurzel= Root[Wesen];
      lokale_Tiefe = 1;
      for (x = O; x < MaxKnoten; x++)
        if (Neu_Individuum[Wurzel][x][Wesen] == 1)
          Tiefe[x][Wesen] = lokale_Tiefe;
      }    
    else
      {
      Root[Wesen] = MaxWesen + 2;
      for (x = O; x < MaxKnoten; x++)
        if (Tiefe[x][Wesen] == O)
          Tiefe[x][Wesen] = 1;
      }
/* naechste Schicht bearbeiten */
  AnzKnoten = O;
  loka1e_Tiefe = 1;
  do {
    AnzKnoten = O;
    for (x = O; x < MaxKnoten; x++)
      if (Tiefe[x][Wesen] == loka1e_Tiefe)
        {
        AnzKnoten++;
        for (y = O; y < MaxKnoten; y++)
          if (Neu_Individuum[x][y][Wesen] == 1)
            if (Tiefe[y][Wesen] = lokale_Tiefe + 1;
          else
            Neu_Individuum[x][y][Wesen] = O;
/* Wenn ein Knoten von mehr als einer Wurzel angegprochen gird, dann gird
die enteprechende tiefere Verbindung gekappt, da sie eine Rueckfuehrung
darstellt. */
        }
      lokale_Tiefe++;
      } vhile (AnzKnoten > 0);
    }
  }  

int GA_Kontrolle_Best_Graph (Wesen)
int Wesen;
  {
  int x, y;
  for (x = O; x < MaxKnoten; x++)
    {
    if (Tiefe[x][Wesen] == MaxWesen + 1)
      {
      for (y = O; y < MaxKnoten; y++)
        Neu_Individuum[y][x][Wesen] = O;
      return (WAHR);
      }
    }  
  return (FALSCH);
  }

void GA_Kontrolle_main()
  {
  int Wesen, x, y, z;
  for (x = O; x < MaxKnoten; x++)
    for (y = O; y < MaxKnoten; y++)
      for (z = O; z < MaxWesen; z++)
        Neu_Individuum[x][y][z] = Individuum[x][y][z];
  for (Wesen = O; Wesen < MaxWesen; Wesen++)
    {
    GA_Kontrolle_ist_Baum(Wesen);
    while (GA_Kontrolle_Rest_Graph(Wesen) == WAHR)
      GA_Kontrolle_ist_Baum(Wesen);
/* printf("Graph: %i Nicht vollstaendig\n" , Wesen); */
    }
/* for (x = O; x < MaxKnoten; x++) printf(" %2i ",x); printf("\n");
  for (Wesen = 0; Wesen < MaxWesen; Wesen++)
    {
    for (x = O; x < MaxKnoten; x++)
       printf(" %2i ",Tiefe[x][Wesen]);
     printf("\n");
    }
  printf("\n"); */
  }