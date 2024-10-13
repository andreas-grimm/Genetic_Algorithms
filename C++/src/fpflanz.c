/*---------------------------------------------*/
/* Modul: fpflanz.c          Version 1.0       */
/*                                             */
/* Fortpflanzungsphase                         */
/*                                             */
/* Datum : 12.11.1991                          */
/*                                             */
/*---------------------------------------------*/
#include "genetics.h"
#include "zufall.h"

void GA_Fpflanz_Roulette()
  {
  int Wheel[100], Prozent, t, u, x, y = 0, z;
  int Neu_Individuum[100][100][MaxIndividuen];
/* Vorbereiten des Roulette— Rades */
  for (x = 0; x < MaxWesen; x++)
    {
    Prozent = (int)(((float)Fitness[x] / (float)GesamtFitness) * 100) ;
    for (z = 0; z < Prozent; z++)
      Wheel[y++] = x;
    }
/* Werfen des Roulette— Rades */
  for (x = 0; x < MaxWesen; x++)
    {
    z = GA_Zufall_main() % y;
    for (t = 0; t < MaxKnoten; t++)
      for (u = 0; u < MaxKnoten; u++)
        Neu_Individuum[t][u][x] = Individuum[t][u][Wheel[z]];
    }    
/* Uebertragen der Ergebnisse */
/* Ohno Generation Gapping
  for (x = 0; x < MaxWesen; x++) */
/* Mit Generation Gapping */
  for (t = 0; t < MaxKnoten; t++)
    for (u = 0; u < MaxKnoten; u++)
      Individuum[t][u][0] = Individuum[t][u][Best_Wesen];
  for (x = 1; x < MaxWesen; x++)
    for (t = 0; t < MaxKnoten; t++)
      for (u = 0; u < MaxKnoten; u++)
        Individuum[t][u][x] = Neu_Individuum[t][u][x];
  }

void GA_FpfIanz_Paarung()
  {
  int Paare[MaxIndividuenHalbe], t, u, x, y = 0, z, Besetzt;
  int Neu_Individuum[100][100][MaxIndividuen];
  for (x = 0; x < MaxWesenHalbe; x++)
    Paare[x] = MaxWesen;
  for (x = 0; x < MaxWesenHalbe; x++)
    {
    t = (GA_Zufall_main() % MaxWesenHalbe) + MaxWesenHalbe;
    do {
      Besetzt = FALSCH;
      for (y = 0; y < x; y++)
        if (Paare[y] == t)
          {
          Besetzt = WAHR;
          t = (GA_Zufall_main() % MaxWesenHalbe) + MaxWesenHalbe;
          }
      } while (Besetzt == WAHR);
    Paare[x] = t;
    }
  for (x = 0; x < MaxWesenHalbe; x++)
    {
    for (y = 0; y < MaxKnoten; y++)
      for (z = 0; z < MaxKnoten; z++)
        {
        Neu_Individuum[y][z][x] = Individuum[y][z][x];
        Neu_Individuum[y][z][Paare[x]] = Individuum[y][z][Paare[x]];
        }
    t = GA_Zufall_main() % MaxKnoten;
    u = GA_Zufall_main() % MaxKnoten;
    for (y = 0; y < t; y++)
      for (z = 0; z < u; z++)
        {
        Neu_Individuum[y][z][x] = Individuum[y][z][Paare[x]] ;
        Neu_Individuum[y][z][Paare[x]] = Individuum[y][z][x];
        }
    for (y = t; y < MaxKnoten; y++)
      for (z = 0; z < MaxKnoten; z++)
        {
        Neu_Individuum[y][z][x] = Individuum[y][z][Paare[x]] ;
        Neu_Individuum[y][z][Paare[x]] = Individuum[y][z][x] ;
        }
    }
/* Uebertragen der Ergebnisse */
  for (x = 0; x < MaxWesen; x++)
    for (y = 0; y < MaxKnoten; y++)
      for (z = 0; z < MaxKnoten; z++)
        Individuum[y][z][x] = Neu_Individuum[y][z][x];
  }

void GA_Fpflanz_Mutation()
  {
  float Elemente;
  int Nr, x, y, z;
  Elemente = MaxKnoten * MaxKnoten * MaxWesen;
  Elemente *= M_Wahrschein;
  if (Elemente > 0)
    for (Nr = 0; Nr < Elemente; Nr++)
      {
      x = GA_Zufall_main() % MaxKnoten;
      y = GA_Zufall_main() % MaxKnoten;
      z = GA_Zufa11_main() % MaxWesen;
      if (Individuum[x][y][z] == 0)
        Individuum[x][y][z] = 1;
      else
        Individuum[x][y][z] = 0;
      }
  }

void GA_Fpflanz_main()
  {
  GA_Fpflanz_Roulette();
  GA_FpfIanz_Paarung();
  GA_Fpflanz_Mutation();
  }
