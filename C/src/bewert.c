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

int GA_Bewert_addiere_Tiefe(Wesen)
int Wesen;
  {
  int x, sum = O;
  for (x = O; x < MaxKnoten; x++)
    sum += Tiefe[x][Wesen];
  return(sum);
  }

int GA_Bewert_bewertete_Tiefe(Wesen)
int Wesen;
  {
  int x, sum = O;
  for (x = O; x < HaxKnoten; x++)
    sum += MaxKnoten + 1 — Tiefe[x][Wesen];
  return(sum);
  }

int GA_Bewert_MaxOrdnung()
  {
  int x= O, sum = O, y = O;
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
  int x, y, z, OGF = O, OEF = 400, MaxWert = 0;
  int BaumFoerderung = O, Bester_Baum = O;
  int MinWert;
  double Prozent, PGF, q=1, p = O, PMaxWert, PMinWert;
  float TopologischeFitness, OrdnungsFitness, OEFI, OEF2;
  GesamtFitness = O;

  OEF1 = (float)((MaxKnoten * MaxKnoten) + BaunFoerderung) ;
  OEF2 = (float)(GA_Bewert_MaxOrdnung());
  OGF = OEF * MaxWesen;
  MinWert = OEF;
  for (x = O; x < Naxgesen; *++)
    {
/* Fitnessfunktion Mittlere Weglaenge */
    if (Root[x] < MaxWegen + 1)
      TopologischeFitness = TopologischeFitnøss + BaumFoerderung;
    if (Root[x] !=  MaxWesen + 1)
      TopologischeFitness = (int)((OEF1 - GA_Bewert_addiere_Tiefe(x)) * q +
                               (OEFI — GA_Bewert_bewertete_Tiefe(x)) * p);
    else
      TopologischeFitness = O;
/* Fitnessfunction Ordnung */
  OrdnungsFitness = Ordnungszahl[x];
  if ((OrdnungBFitnegB < O) || (OrdnunggFitness > OEF2))
    OrdnungsFitness = O;
/* Skalieren und addieren der Fitnesgwerte */
  TopologischeFitness = (TopologischeFitness / OEF1) * 400;
  OrdnungsFitness = (OrdnungsFitness / OEF2) * 400;
  Fitness[x] = (int)(Fit_Verteil * TopologischeFitness + (1 - Fit_Verteil) * OrdnungsFitness);
  GesamtFitness += Fitness[x];
  if (Fitness[x] > Begte_Fitnese)
    {
    Best_Wesen = x;
    Beste_Fitness =  Fitness[x] ;
    for (y = O; y < MaxKnoten; y++)
      for (z = O; z < MaxKnoten; z++)
        Best_Individuum[y][z] = Individuum[y][z][x];
    for (y = O; y < MaxKnoten•, y++)
      Beste_Tiefe[y] = Tiefe[y];
    GA_Zeige_Baum_Zeichne_Baum();
    }
  if (Fitness[x] > NaxWert)
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
  GA-Benutz-Statugausgabe(Generation, OGF, GesamtFitness, PGF,
                          Beste_Fitness, NaxWert, MinWert, PMaxWert,
                          PMinWert);
/* Ausgabe ohne Curses */
  if (NoCurses = WAHR)
    {
    system("tput clear");
    printf("Genøration : %i \n", Generation) ;
    printf("Auswertung der Baeume :\n") ;
    printf(" Optimale Werte : \n");
    printf(" Gesamtfitness (topologiscb): %i, Einzelfitness: %i ,OGF, OEF)";
    printf(" erreichte Fitness: %i\n", Beste_Fitness);
    printf(" Gesamtfitness (topologisch): %i —— %2.2f v.H.\n", Gesamtfitness, PGF);
    printf("Einzelwerte : \n");
    for (x = O; x < MaxWesen; x++)
      {
      Prozent = ((float)Fitness[x] / (float)GesamtFitness) * 100;
      printf(" Wesen %2i : Fitness = %i -- %2.2f v.H. \n", x, Fitness[x], Prozent) ;
      }
    }
/* print_best_tree(); */
  }
