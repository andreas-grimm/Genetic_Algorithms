with Text_io;
with simple_genetic_algorithms;

procedure test_environ is
  package Genetic_Algorithms is new simple_genetic_algorithms(5,6);

  use Genetic_Algorithms;
	  use Text_io;

  Population 	: Population_Array;
  Fitness	: Fitness_Array;
  Generation	: integer := 0;
  Value_Array   : Fitness_Array;
  Calc_Array    : Fitness_Array;
  Mutation_Quote : float := 0.005;

    function Binary_to_Integer (Genetic_String : Individuum) return
		   integer is
      Number : integer := 0;
      begin
	Number := Genetic_String(1);
        for t in 2..Genetic_String'Last loop
	  Number := Number + Genetic_String(t) * (2 ** (t - 1));
	end loop;
      return Number;
      end Binary_to_Integer;

    procedure Check_Fitness (Population : in     Population_Array;
			     Value_Array: in out Fitness_Array;
			     Calc_Array : in out Fitness_Array;
      			     Fitness    : in out Fitness_Array) is
      Sum_of_Fitness : float := 0.0;
      begin
	for t in Population'Range loop
	  Value_Array(t) := float(Binary_to_Integer(Population(t)));
-- as an example: calulate x^2
	  Fitness(t) := float(integer(Value_Array(t)) ** 2);
--
	  Calc_Array(t) := Fitness(t);
	  Sum_of_Fitness := Sum_of_Fitness + Fitness(t);
	end loop;
	if (Sum_of_Fitness <= 0.0) then
	  Sum_of_Fitness := 1.0;
        end if;
        for t in Population'Range loop
	  Fitness(t) := (Fitness(t) / Sum_of_Fitness) * 100.0;
	end loop;
      end Check_Fitness;

  begin
  put_line ("Test Environment for Genetics Algorithms Library started");
  Init_Population(Population);
  put_line("Start of cyklus"); 
  loop
    Check_Fitness(Population,Value_Array,Calc_Array,Fitness);
    Roulette_Wheel(Population,Fitness);
    Crossover(Population);
    Mutation(Population,Mutation_Quote);
    Simple_Display(Generation,Population,Fitness,Value_Array,Calc_Array);
    Generation := Generation + 1;
  end loop;
  end test_environ;
