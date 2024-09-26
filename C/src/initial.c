/*---------------------------------------------*/
/*                                             */
/* Modul: Initial            Version 1.0       */
/*                                             */
/* Initialigierung der Adjazenzmatrix          */
/*                                             */
/* Datum : 20. Juli 1991                       */
/*                                             */
/*---------------------------------------------*/

#include <stdio.h>
#include "genetics.h"

/* ein Element ist genau daan Blatt, wenn es nur Vorgaenger hat */
int GA_Initial_ist_Blatt(Wurzel, Wesen)
int Wurzel, Wesen;
  {
  int x, sum = O;
  for (x = O; x < MaxKnoten; x++)
    sum = sum + Individuum[Wurze1][x][Wesen];
  if (sum == 0)
    {
    for (x = O; x < MaxKnoten; x++)
      sum = sum + Individuum[x][ Wurzel][Wesen];
    if (sum != O)
      return (WAHR);
    }
  return (FALSCH) ;
  }

/* ein Element igt genau dann Wurzel, wenn es keine Yachfolger hat */
int GA_Initial_ist_Wurzel(Nachfolger,Wesen)
int Nachfolgør, Wesøn;
  {
  int x, sum = 0;
  for (x = O; x < MaxKnoten; x++)
    {
    sum = sum + Individuum[x][Nachfolger][Wesen];
    }
  if (sum == O)
    return (WAHR);
  else
    return (FALSCH);
  }

/* ein Element ist genau dann frei, wenn es weder Wurzel noch Knoten ist */
int GA_Initial_ist_freies_Element(Wesen)
int Wesen;
  {
  int x, y, sum = 0;
  for (x = 0; x < MaxKnoten; x++)
    {
    for (y = 0; y < MaxKnoten; y++)
      sum = sum +Individuum[x][y][Wesen] + Individuum[y][x][Wesen];
    if (sum == 0)
      return(WAHR);
    else
      sum = O;
    }
  return (FALSCH);
  }

void GA_Initial_Baue_Baum(Wesen)
int Wesen;
  {
  int Wurzel, Nachfolgør, x;
/* Suche eine Wurzel */
  Wurzel = GA_Zufall_main() % MaxKnoten;
  Root[Wesen] = Wurzel;
/* TESTLAUF
  printf("Wurzel des Baumes: %i\n", Wurzel);
*/
  do {
/* Suche Nachfolger entsprechend eingestellter Rang */
    Nachfolger = Wurzel;
    for (x = O; x < MaxNachfolger•, x++)
      {
      while ((Yachfolger == Wurzel) ||
             (GA_Initial_ist_Wurzel(Nachfolger , Wesen) == FALSCH))
        Nachfolger = GA_Zufall_main() % MaxKnoten;
      if (Root[Wesen] != Nachfolger)
        {
/* TESTLAUF
        printf("Nachfolger : %i\n", Nachfolger);
*/
        Individuum[Wurzel][Nachfolger][Wesen] = 1 ;
        }
     Nachfolger = Wurzel;
      }
/* Neue Wurzel suchen */
    while (GA_Initial_ist_Blatt(Wurzel,Wesen) == FALSCH)
      Wurzel = GA_Zufall_main() % MaxKnoten;
/* TESTLAUF
    printf("Neue Wurzel: %i \n",Wurzel);
*/
    } while (GA_initial_ist_freies_Element(Wesen) == WAHR);
  }

void GA_Initial_Wesen()
  {
  int x, y, z;
/* Vorinitiaiißierung der Individuen */
  Beste_Fitness = O;
  for (z = O; z < MaxWesen; z++)
    {
    for (x = O; x < MaxKnoten; x++)
      for (y = O; y < MaxKnoten; y++)
        Individuum[x] = O;
    }
/* Aufbau der Baeume */
  for (z = O; z < MaxWesen; z++)
    {
    GA_Initial_Baue_Baum(z);
/* Testausgabe der erzeugten Baeume
    printf("\ni");
    print_tree(z); */
    }
  }