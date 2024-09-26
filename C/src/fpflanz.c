/*---------------------------------------------*/
/* Modul: fpflanz.c          Version 1.0       */
/*                                             */
/* Fortpflanzungsphase                         */
/*                                             */
/* Datum : 12.11.1991                          */
/*                                             */
/*---------------------------------------------*/
#include "genetics.h"

void GA_Fpflanz_Roulette()
  {
  int Wheel[IOO], Prozent, t, u, x, y = O, z;
  int Neu_Individuum[IOO][IOO][Maxlndividuen];
/* Vorbereiten des Roulette— Rades */
  for (x = O; x < MaxWesen; x++)
    {
    Prozent = (int)(((float)Fitness[x] / (float)GesamtFitness) * 100) ;
    for (z = O; z < Prozent; z++)
      Wheel[y++] = x;
    }
/* Werfen des Roulette— Rades */
  for (x = O; x < MaxWesen; x++)
    {
    z = GA_Zufall_main() % y;
    for (t = O; t < MaxKnoten; t++)
      for (u = O; u < maxKnoten; u++)
        Neu_lndividuum[t][u][x] = Individuum[t][u][Wheel[z]];
    }    
/* Uebertragen der Ergebnisse */
/* Ohno Generation Gapping
  for (x = O; x < MaxWesen; x++) */
/* Mit Generation Gapping */
  for (t = O; t < MaxKnoten; t++)
    for (u = O; u < MaxKnoten,• u++)
      Individuum[t][u][0] = Individuum[t][u][Best_Wesen];
  for (x = i; x < MaxWesen; x++)
    for (t = O; t < MaxKnoten; t++)
      for (u = O; u < MaxKnoten; u++)
        Individuum[t][u][x] = Neu_Individuum[t][u][x];
  }

void GA_FpfIanz_Paarung()
  {
  int Paare[MaxIndividuenHa1be], t, u, x, y = O, z, Besetzt;
  int Neu—lndividuum[100][100][Maxlndividuen];
  for (x = O; x < MaxWesenHalbe; x++)
    Paare[x] = MaxWesen;
  for (x = O; x < MaxWesenHa1be; x++)
    {
    t = (GA_Zufall_main() % MaxWesenHalbe) + MaxWesenHalbe;
    do {
      Besetzt = FALSCH;
      for (y = O; y < x; y++)
        if (Paare[y] == t)
          {
          Besetzt = WAHR;
          t = (GA_Zufall_main() % MaxWesenHalbe) + MaxWesenHa1be;
          }
      } while (Besetzt == WAHR);
    Paare[x] = t;
    }
  for (x = O; x < MaxWesenHalbe; x++)
    {
    for (y = O; y < MaxKnoten; y++)
      for (z = O; z < MaxKnoten; z++)
        {
        Neu_Individuum[y][z][x] = Individuun[y][z][x];
        Neu_Individuum[y][z][Paare[x]] = Individuum[y][z][Paare[x]];
        }
    t = GA_Zufall_main() % MaxKnoten;
    u = GA_Zufall_main() % MaxKnoten;
    for (y = O; y < t; y++)
      for (z = O; z < u; z++)
        {
        Neu_Individuum[y][z][x] = Individuum[y][z][Paare[x]] ;
        Neu_Individuun[y][z][Paare[x]] = Individuum[y][z][x];
        }
    for (y = t; y < MaxKnoten; y++)
      for (z = O; z < MaxKnoten; z++)
        {
        Neu_Individuum[y][z][x] = Individuun[y][z][Paare[x]] ;
        Neu_Individuum[y][z][Paare[x]] = Individuum[y][z][x] ;
        }
    }
/* Uebertragen der Ergebnisse */
  for (x O; x < MaxWesen; x++)
    for (y = 0; y < MaxKnoten; y++)
      for (z = O; z < MaxKnoten; z++)
        Individuum[y][z][x] = Neu_lndividuum[y][z][x];
  }

void GA_Fpflanz_Mutation()
  {
  long float Elemente;
  int Nr, x, y, z;
  Elemente = MaxKnoten * MaxKnoten * MaxWesen;
  Elemente *= M_Wahrschein;
  if (Elemente > O)
    for (Nr = O; Nr < Elements; Nr++)
      {
      x = GA_Zufall_main() % MaxKnoten;
      y = GA_Zufall_main() % NaxKnoten;
      z = GA_Zufa11_main() % MaxWesen;
      if (Individuum[x][y][z] == O)
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