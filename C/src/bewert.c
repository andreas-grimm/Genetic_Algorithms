/*---------------------------------------------*/                           
/* Modul: bewert.c           Version 1.0       */                           
/*                                             */                           
/* Globale Variablendefinitionen fuer GENETICS */                           
/*                                             */                           
/* Datum : 31 . August 1991                    */                           
/*                                             */                           
/*---------------------------------------------*/                           
#include <stdio.h>
#include "genetics.h"
#include "zeige_baum.h"

int GA_Bewert_addiere_Tiefe(Wesen)
int Wesen;
  {
  int x, sum = 0;
  for (x = 0; x < MaxKnoten; x++)
    sum += Tiefe[x][Wesen];
  return(sum);
  }

int GA_Bewert_bewertete_Tiefe(Wesen)
int Wesen;
  {
  int x, sum = 0;
  for (x = 0; x < MaxKnoten; x++)
    sum += MaxKnoten + 1 - Tiefe[x][Wesen];
  return(sum);
  }

int GA_Bewert_MaxOrdnung()
  {
  int x= 0, sum = 0, y = 0;
  for (y = 0; y < MaxKnoten; y++)
    for (x = y; x < MaxKnoten; x++)
      sum++ ;
  return(sum);
  }

void GA_Bewert_nain()
  {
  /* OGF — optimale Gesamtfitnesg
     OEF - optimale Einzeliitness
     PGF — Prozent der Gesamtfitness */
  int x, y, z, OGF = 0, OEF = 400, MaxWert = 0;
  int BaumFoerderung = 0, Bester_Baum = 0;
  int MinWert;
  double Prozent, PGF, q=1, p = 0, PMaxWert, PMinWert;
  float TopologischeFitness, OrdnungsFitness, OEF1, OEF2;
  GesamtFitness = 0;

  OEF1 = (float)((MaxKnoten * MaxKnoten) + BaumFoerderung) ;
  OEF2 = (float)(GA_Bewert_MaxOrdnung());
  OGF = OEF * MaxWesen;
  MinWert = OEF;
  for (x = 0; x < MaxWesen; x++)
    {
/* Fitnessfunktion Mittlere Weglaenge */
    if (Root[x] < MaxWesen + 1)
      TopologischeFitness = TopologischeFitness + BaumFoerderung;
    if (Root[x] !=  MaxWesen + 1)
      TopologischeFitness = (int)((OEF1 - GA_Bewert_addiere_Tiefe(x)) * q +
                               (OEF1 - GA_Bewert_bewertete_Tiefe(x)) * p);
    else
      TopologischeFitness = 0;
/* Fitnessfunction Ordnung */
  OrdnungsFitness = Ordnungszahl[x];
  if ((OrdnungsFitness < 0) || (OrdnungsFitness > OEF2))
    OrdnungsFitness = 0;
/* Skalieren und addieren der Fitnesgwerte */
  TopologischeFitness = (TopologischeFitness / OEF1) * 400;
  OrdnungsFitness = (OrdnungsFitness / OEF2) * 400;
  Fitness[x] = (int)(Fit_Verteil * TopologischeFitness + (1 - Fit_Verteil) * OrdnungsFitness);
  GesamtFitness += Fitness[x];
  if (Fitness[x] > Beste_Fitness)
    {
    Best_Wesen = x;
    Beste_Fitness =  Fitness[x] ;
    for (y = 0; y < MaxKnoten; y++)
      for (z = 0; z < MaxKnoten; z++)
        Best_Individuum[y][z] = Individuum[y][z][x];
    for (y = 0; y < MaxKnoten; y++)
      Beste_Tiefe[y] = Tiefe[y][x];
    GA_Zeige_Baum_Zeichne_Baum();
    }
  if (Fitness[x] > MaxWert)
    {
    MaxWert = Fitness[z];
    Bester_Baum = x;
    }
  if (Fitness[x] < MinWert)
    MinWert = Fitness[x];
  }
  GA_Zeige_Baum_Zeichne_bester_Baum(Bester_Baum);
  Statistik[Generation][BESTER] = MaxWert;
  Statistik[Generation][MITTEL] =  GesamtFitness / MaxWesen;
  Statistik[Generation][SCHLECHT] = MinWert ;
  PGF = (float)GesamtFitness / (float)OGF * 100;
  PMinWert = ((float)MinWert / (float)GesamtFitness) * 100;
  PMaxWert = ((float)MaxWert / (float)GesamtFitness) * 100;
  GA_Benutz_Statugausgabe(Generation, OGF, GesamtFitness, PGF,
                          Beste_Fitness, MaxWert, MinWert, PMaxWert,
                          PMinWert);
/* Ausgabe ohne Curses */
  if (NoCurses = WAHR)
    {
    system("tput clear");
    printf("Genøration : %i \n", Generation) ;
    printf("Auswertung der Baeume :\n") ;
    printf(" Optimale Werte : \n");
    printf(" Gesamtfitness (topologiscb): %i, Einzelfitness: %i",OGF, OEF);
    printf(" erreichte Fitness: %i\n", Beste_Fitness);
    printf(" Gesamtfitness (topologisch): %i —— %2.2f v.H.\n", GesamtFitness, PGF);
    printf("Einzelwerte : \n");
    for (x = 0; x < MaxWesen; x++)
      {
      Prozent = ((float)Fitness[x] / (float)GesamtFitness) * 100;
      printf(" Wesen %2i : Fitness = %i -- %2.2f v.H. \n", x, Fitness[x], Prozent) ;
      }
    }
/* print_best_tree(); */
  }
