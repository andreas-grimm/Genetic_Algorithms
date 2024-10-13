pragma LIST(ON);

with text_io; use text_io;
with random; use random;
with fio; use fio;
with iio; use iio;

generic
-- To be defined :
-- MaxAllele = Numbers of Alleles in an Individuum
-- MaxPopSize = Number of Individuums in a Population
   MaxAllele	    	: integer;
   MaxPopSize		: integer;

package Simple_Genetic_Algorithms is
--
-- First definition of the most important types for genetic algorithms
--
  type Individuum       is array (1..MaxAllele) of integer range 0..1;
  type Population_Array is array (1..MaxPopSize) of Individuum;
  type Fitness_Array    is array (1..MaxPopSize) of float;
--
-- Definition of the initialization of the population
--
  procedure Init_Population (Population : in out Population_Array);
--
-- Definition of the elementary functions of SGAs
--
  procedure Roulette_Wheel (Population : in out Population_Array;
			    Fitness    : in     Fitness_Array);
  procedure Crossover      (Population : in out Population_Array);
  procedure Mutation       (Population : in out Population_Array;
			    Mutationquote: in   float);
  procedure Simple_Display(Generation : integer;
			   Population : in Population_Array;
			   Fitness    : in Fitness_Array;
			   Org_Value  : in Fitness_Array;
			   Calc_Value : in Fitness_Array);

end Simple_Genetic_Algorithms;

--
-- Package body, closed as a secret !
--

package body Simple_Genetic_Algorithms is

  Best_Org_Value	: float := 0.0;
  Best_Calc_Value	: float := 0.0;
  Best_Generation	: integer := 0;
  Last_Gen_Accum_Org	: float := 0.0;
  Last_Gen_Accum_Calc	: float := 0.0;

  procedure Init_Population (Population : in out Population_Array) is
    t, x		: integer;
    Single_Individuum	: Individuum;
  begin
    for t in Population'Range loop
      for x in Population(t)'Range loop
        Single_Individuum(x) := random_ND_integer(65535) mod 2; 
	if (Single_Individuum(x) > 1) then
	  Single_Individuum(x) := 1;
        end if;
      end loop;
      Population(t) := Single_Individuum;
    end loop;
  end Init_Population;
  
  procedure Roulette_Wheel (Population : in out Population_Array;
			    Fitness    : in     Fitness_Array) is
    New_Population : Population_Array;
    Wheel_Length   : constant := 100;
    Wheel          : array (1..Wheel_Length) of integer;
    Position       : integer := 1;
    t              : integer;
    x              : integer;
    field          : integer;

  begin
-- Initialization of the Roulette Wheel. Every Individuum gets fields,
-- iff it's Fitness is better then 1 % of the accumulated fitness in the
-- system. This will be less or equal 100 fields on the Roulette Wheel.
    for t in Population'Range loop
      if (Fitness(t) >= 1.0) then
	for x in Position..(Position+integer(Fitness(t))) loop
	  if (x <= 100) then
	    Wheel(x):=t;
          end if;
	end loop;
	Position := Position + integer(Fitness(t));
      end if;
    end loop;
-- Start of the selection of new generation.
    for t in Population'Range loop
      field := 101;
      while (field > 100) loop
        field := (random_ND_integer(65535) mod Position) + 1;
      end loop;
      New_Population(t) := Population(Wheel(field));
    end loop;
-- Let the new generation take the place of the old one.
    for t in Population'Range loop
      Population(t) := New_Population(t);
    end loop;
-- Finished and end of the reproduction phase.
  end Roulette_Wheel;

  procedure Crossover (Population : in out Population_Array) is
    New_Population     : Population_Array;
    Partner            : array (Population'Range) of integer;
    x,y,z	       : integer;
    filled	       : boolean;
    Selected_Partner   : integer;
    Point_of_Crossover : integer;
    New_1st_Individuum : Individuum;
    New_2nd_Individuum : Individuum;
    Dummy	       : Individuum;

  begin
-- Initialize the fields for the relationship
    for x in Partner'Range loop
      Partner(x) := Population'Length + 1;
    end loop;
-- Select the partners
    for x in 1..(Partner'Last / 2) loop
      Selected_Partner := (random_ND_integer(65535) mod (Population'Length / 2))
			   + (Population'Length / 2) + 1;
      loop
	filled := false;
	for y in 1..x loop
	  if (Partner(y) = Selected_Partner) then
	    filled := true;
            Selected_Partner :=(random_ND_integer(65535) mod (Population'Length
				/ 2)) +(Population'Length / 2);		
	    end if;
	  end loop;
	exit when (filled = false);
      end loop;
      Partner(x) := Selected_Partner;
    end loop;
-- Find Point of Crossover and start the change of the genetic information
    for x in 1..(Partner'Last / 2) loop
      New_1st_Individuum := Population(x);
      New_2nd_Individuum := Population(Partner(x));
      Point_of_Crossover := (random_ND_integer(65535) mod Population(x)'Length);
      if (Point_of_Crossover > 0) then
        Dummy := New_1st_Individuum;
        for z in 1..Point_of_Crossover loop
	  New_1st_Individuum(z) := New_2nd_Individuum(z);
	  New_2nd_Individuum(z) := Dummy(z);
        end loop;
      end if;
      Population(x) := New_1st_Individuum;
      Population(Partner(x)) := New_2nd_Individuum;
    end loop;
-- Final procedures of this phase
  end Crossover;

  procedure Mutation       (Population : in out Population_Array;
			    Mutationquote: in   float) is
    Number_of_Mutations : integer;
    Selected		: integer;
    Point_of_Mutation   : integer;
    Mutant		: Individuum;
    Quote		: float;
    Correction		: float;

    begin
      Quote := Mutationquote;
      if (Mutationquote < 0.001) then
	put_line("Quote of Mutation too small ! Assumed new quote : 0.005 ");
	Quote := 0.005;
      elsif (Mutationquote > 0.999) then
	put_line("Quote of Mutation too big ! Assumed new quote : 0.005 ");
	Quote := 0.005;
      end if;
      Correction := 1000.0 / float(MaxPopSize);
      Number_of_Mutations := integer(Quote * float(MaxPopSize) * Correction);
      if (Number_of_Mutations > 0) then
        Number_of_Mutations := random_ND_integer(65535) mod Number_of_Mutations;
      end if;
      if (Number_of_Mutations > 0) then
	for x in 1..Number_of_Mutations loop
	  Selected := (random_ND_integer(65535) mod Population'Length) + 1;
	  Point_of_Mutation := (random_ND_integer(65535) mod
	                         Population(Selected)'Length) + 1;
	  Mutant := Population(Selected);
          if (Mutant(Point_of_Mutation) = 0) then
	    Mutant(Point_of_Mutation) := 1;
          else
	    Mutant(Point_of_Mutation) := 0;
          end if;
        Population(Selected) := Mutant;
	end loop;
      end if;
    end Mutation;

  procedure Simple_Display(Generation : integer;
			   Population : in Population_Array;
			   Fitness    : in Fitness_Array;
			   Org_Value  : in Fitness_Array;
			   Calc_Value : in Fitness_Array) is
  Single_Allele		: integer;
  Element		: Individuum;
  This_Gen_Accum_Org	: float;
  This_Gen_Accum_Calc	: float;
  Change_of_Accum_Calc  : float;
  
  begin
    new_page;
    put ("Genetic Algorithms Experimental Environment: Simple Display ");
    put_line ("Procedure");
    new_line;
    put ("Generation :");
    put (Generation);
    new_line;
    for T in Population'Range loop
      Element := Population(T);
      for X in Element'Range loop
        Single_Allele := Element(X);
        put(Single_Allele,1);
      end loop;
    put(" | "); put(integer(Fitness(T)),4);
    put(" | "); put(integer(Org_Value(T)),4);
    This_Gen_Accum_Org := This_Gen_Accum_Org + Org_Value(T);
    put(" | "); put(integer(Calc_Value(T)),4);
    This_Gen_Accum_Calc := This_Gen_Accum_Calc + Calc_Value(T);
    if (Best_Calc_Value < Calc_Value(T)) then
      Best_Calc_Value := Calc_Value(T);
      Best_Generation := Generation;
    end if;
    new_line;
    end loop;
    Change_of_Accum_Calc := This_Gen_Accum_Calc - Last_Gen_Accum_Calc;
    put("Best Fitness :  "); put(integer(Best_Calc_Value));
    put(" in Generation : "); put(Best_Generation); new_line;
    put("Accum. Fitness: "); put(integer(This_Gen_Accum_Calc));
    put(" Last Generation : "); put(integer(Last_Gen_Accum_Calc));
    put(" Change : "); put(integer(Change_of_Accum_Calc)); new_line;
    Last_Gen_Accum_Calc := This_Gen_Accum_Calc;
  end Simple_Display;
  
end Simple_Genetic_Algorithms;
pragma LIST(OFF);
