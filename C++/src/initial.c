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
#include "zufall.h"

/* ein Element ist genau daan Blatt, wenn es nur Vorgaenger hat */
int GA_Initial_ist_Blatt(Wurzel, Wesen)
int Wurzel, Wesen;
  {
  int x, sum = 0;
  for (x = 0; x < MaxKnoten; x++)
    sum = sum + Individuum[Wurzel][x][Wesen];
  if (sum == 0)
    {
    for (x = 0; x < MaxKnoten; x++)
      sum = sum + Individuum[x][ Wurzel][Wesen];
    if (sum != 0)
      return (WAHR);
    }
  return (FALSCH) ;
  }

/* ein Element igt genau dann Wurzel, wenn es keine Yachfolger hat */
int GA_Initial_ist_Wurzel(Nachfolger,Wesen)
int Nachfolger, Wesen;
  {
  int x, sum = 0;
  for (x = 0; x < MaxKnoten; x++)
    {
    sum = sum + Individuum[x][Nachfolger][Wesen];
    }
  if (sum == 0)
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
      sum = 0;
    }
  return (FALSCH);
  }

void GA_Initial_Baue_Baum(Wesen)
int Wesen;
  {
  int Wurzel, Nachfolger, x;
/* Suche eine Wurzel */
  Wurzel = GA_Zufall_main() % MaxKnoten;
  Root[Wesen] = Wurzel;
/* TESTLAUF
  printf("Wurzel des Baumes: %i\n", Wurzel);
*/
  do {
/* Suche Nachfolger entsprechend eingestellter Rang */
    Nachfolger = Wurzel;
    for (x = 0; x < MaxNachfolger; x++)
      {
      while ((Nachfolger == Wurzel) ||
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
    } while (GA_Initial_ist_freies_Element(Wesen) == WAHR);
  }

void GA_Initial_Wesen()
  {
  int x, y, z;
/* Vorinitiaiißierung der Individuen */
  Beste_Fitness = 0;
  for (z = 0; z < MaxWesen; z++)
    {
    for (x = 0; x < MaxKnoten; x++)
      for (y = 0; y < MaxKnoten; y++)
        Individuum[x][y][z] = 0;
    }
/* Aufbau der Baeume */
  for (z = 0; z < MaxWesen; z++)
    {
    GA_Initial_Baue_Baum(z);
/* Testausgabe der erzeugten Baeume
    printf("\ni");
    print_tree(z); */
    }
  }
