with Text_io;
with iio; with fio;
with Advanced_Genetic_Algorithms;

procedure Traveling_Salesman is
-- Number of Allele in the String : 8
-- Population : 10 Strings
-- Number of Points to cut the String : 7
  package Genetic_Algorithms is new Advanced_Genetic_Algorithms(24,80,7);

  use Genetic_Algorithms;
  use Text_io; use iio; use fio;

  No_of_Towns : constant integer := 8;
  type Route  is array (1..No_of_Towns) of integer;
  type Routes is array (1..80) of Route;
  Towns       : array (1..No_of_Towns) of string(1..10) :=
    ("London    ",
     "Edinburgh ",
     "Cardiff   ",
     "Newcastle ",
     "York      ",
     "Holyhead  ",
     "Thurso    ",
     "Dover     ");
  Distance_Array : array (1..No_of_Towns,1..No_of_Towns) of integer :=
   ((  0, 378, 159, 274, 193, 259, 651,  71),
    (378,   0, 385, 110, 194, 308, 278, 449),
    (159, 385,   0, 301, 240, 201, 650, 237),
    (274, 110, 301,   0,  84, 247, 384, 345),
    (193, 194, 240,  84,   0, 188, 462, 264),
    (259, 308, 201, 247, 188,   0, 587, 339),
    (651, 278, 650, 384, 462, 587,   0, 717),
    ( 71, 449, 237, 345, 264, 339, 717,   0));

  Population     : Population_Array;
  Fitness        : Fitness_Array;
  Generation     : integer := 0;
  best_Generation: integer := 0;
  Value_Array    : Fitness_Array;
  Calc_Array     : Fitness_Array;
  Way            : Routes;
  Mutation_Quote : float := 0.05;
  Crossing_Dummy : Crossing_Points;
  best_Way       : Route;
  best_Value     : float := 99999.99;
  Roulette	 : boolean := false;

  procedure Show_Way (Way : in Route) is
    begin
    for t in 1..(Way'Last-1) loop
      put(Towns(Way(t))); put(" --> ");
      if ((t mod 4) = 0) then
	new_line;
	end if;
      end loop;
    put(Towns(Way(Way'Last))); 
    end Show_Way;

  procedure Change_String_to_Route (Genetic_String  : in     Individuum;
				    Transformed_Way : in out Route) is
    x : integer := 1;
    begin
    for t in Transformed_Way'Range loop
      Transformed_Way(t) := Genetic_String(x) * 4 + Genetic_String(x+1) * 2
                                                  + Genetic_String(x+2) + 1;
      x := x + 3;
      end loop;
    end Change_String_to_Route;

  procedure Check_Fitness(Population  : in out Population_Array;
			  Way         : in out Routes;
			  Calc_Array  : in out Fitness_Array;
			  Fitness     : in out Fitness_Array) is
    Sum_of_Fitness  : float := 0.0;
    Sum_Distance    : float := 0.0;
    Number_of_Knots : integer := 0;
    Error_Coeff     : integer := 0;
    Double          : integer := 0;

    function Distance (Way : in Route) return float is
      Way_Gone     : float   := 0.0;
      Short_Cycle  : boolean := false;
      used_Towns   : array(1..No_of_Towns) of integer;
      Acculum_Dist : integer := 0;
      begin
      for t in used_Towns'Range loop
	used_Towns(t) := Way(t);
	end loop;
      for t in 1..(Way'Last-1) loop  -- former -1!
	for x in used_Towns'Range loop
	  if ((used_Towns(x) = Way(t)) and (x /= t)) then
	    Short_Cycle := true;
	    Error_Coeff := Error_Coeff + 1;
	    Double      := t;
	    end if;
          end loop;
        used_Towns(t) := Way(t);
	Acculum_Dist := Acculum_Dist + Distance_Array(Way(t),Way(t+1));
	end loop;
      if (Short_Cycle = true) then
	return 99999.99;
      else
	return float(Acculum_Dist);
	end if;
      end Distance;

    procedure Repair(Element : in out Individuum; Way : in Route) is
      missing      : integer := 0;
      First_Allele : integer := 0;
      in_it        : boolean := false;
      begin
      for t in 1..No_of_Towns loop
	for x in 1..No_of_Towns loop
	  if (Way(x) = t) then
	    in_it := true;
	    end if;
	  end loop; 
        if (in_it = false) then
          missing := t;
          in_it := false;
          end if;
        end loop;
      First_Allele := (Double * 3) - 2;
      for t in First_Allele..(First_Allele+2) loop
	Element(t) := missing / 2;
	missing := missing mod 2;
	end loop;
      end Repair;

    begin
    for t in Population'Range loop
      Change_String_to_Route (Population(t),Way(t));
      Calc_Array(t) := Distance(Way(t));
      if (Error_Coeff = 1) then
	Repair(Population(t),Way(t));
	Change_String_to_Route (Population(t),Way(t));
	Calc_Array(t) := Distance(Way(t));
	end if;
      Error_Coeff := 0;
      if (Calc_Array(t) /= 99999.99) then
        Sum_Distance := Sum_Distance + Calc_Array(t);
	end if;
      end loop;
    for t in Population'Range loop
      if (Calc_Array(t) = 99999.99) then
	Fitness(t) := 0.0;
      else
        Fitness(t) := (Calc_Array(t) / Sum_Distance) * 100.0;
	end if;
      end loop;
    end Check_Fitness;

  begin
    Init_Population(Population);
    best_Way := Way(1);
    loop
      Check_Fitness(Population, Way, Calc_Array, Fitness);
      Generation := Generation + 1;
      put("Generation : "); put(Generation); new_line;
      for t in Population'Range loop
	if (best_Value > Calc_Array(t)) then
	  best_Value := Calc_Array(t);
	  best_Way   := Way(t);
	  best_Generation := Generation;
	  end if;
        if (Fitness(t) > 0.0) then
	  Show_Way(Way(t)); put(integer(Calc_Array(t))); new_line;
	  end if;
        end loop;
      put("best Value : Generation : "); put(best_Generation); new_line;
      Show_Way(best_Way); put(integer(best_Value)); new_line;
      Roulette := false;
      for t in Fitness'Range loop
	if (Fitness(t) > 0.0) then
	  Roulette := true;
	  end if;
        end loop;
      if (Roulette = true) then
        Roulette_Wheel(Population,Fitness,0);
        end if;
      Crossover(Population,haploid,randomize,Crossing_Dummy,0,0);
      Mutation(Population,Mutation_Quote,0);
      end loop;
  end Traveling_Salesman;
