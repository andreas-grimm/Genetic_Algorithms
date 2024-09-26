/*---------------------------------------------*/
/* Modul: zufall.c           Version 1.0       */
/*                                             */
/* Schnittstelle zum Zufallsgenerator          */
/*                                             */
/* Datum :                                     */
/*                                             */
/*---------------------------------------------*/
#include <sys/time.h>
#include "genetics.h"

long GA_Zufall_main()
  {
  return(lrand48());  
  }