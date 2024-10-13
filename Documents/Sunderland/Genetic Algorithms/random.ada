-- Random number generators in Ada
-- Version 1.0
-- see: W.H.Press, B.P.Flannery, S.A.Teukolsky, W.T.Vetterling
--      Numerical Recipes in C
--      Cambidge, 1988
--	ISBN 0-521-35465-X

--	Chapter 7, Pages 204 - 241

with ada_io; use ada_io;
with math_lib;
with calendar;

package random is
-- Function for normal (Gaussian) deviates
  function random_ND return float;
  function random_ND_integer(reach : integer) return integer; 
-- Function for Exponential deviates
  function random_ED return float;
  function random_ED_integer(reach : integer) return integer;
end random;

package body random is
-- static variables for the function "ran1"
  M1		: integer := 259200;
  M2		: integer := 134456;
  M3		: integer := 243000;
  IA1		: integer := 7141;
  IA2		: integer := 8121;
  IA3		: integer := 4561;
  IC1		: integer := 54773;
  IC2		: integer := 28411;
  IC3		: integer := 51349;
  RM1		: float	  := 0.0000038502;
  RM2		: float   := 0.0000074377;
  x 		: integer := 737;
  ix1, ix2, ix3 : integer;
  r		: array (0..98) of float;
  iff		: integer := 0;
  initialized   : boolean := false;
  init_value	: integer := -31415;
-- static variables for the function "ran2"
  M		: integer := 714025;
  IA		: integer := 1366;
  IC		: integer := 150889;
-- static variables for the function "ran3"
  MBIG		: integer := 1000000000;
  MSEED		: integer := 161803398;
  MZ		: integer := 0;
  FAC		: float;
-- static variables for the function "random_ND"
  iset		: integer := 0;
  gset		: float   := 0.0;

  function ran1 return float is
    temp : float;
    j    : integer;
    begin
      if (initialized  = false) then
	ix1 := (IC1 - init_value) mod M1;
	ix1 := (IA1 * ix1 + IC1) mod M1;
	ix2 := ix1 mod M2;
	ix1 := (IA1 * ix1 + IC1) mod M2;
	for j in 1..97 loop
	  ix1 := (IA1 * ix1 + IC1) mod M1;
	  ix2 := (IA2 * ix2 + IC2) mod M2;
	  r(j) := float(ix1 + ix2 * integer(RM2)) * RM1;
	end loop;
	initialized := true;
	end if;
      ix1 := (IA1 * ix1 + IC1) mod M1;
      ix2 := (IA2 * ix2 + IC2) mod M2;
      ix3 := (IA3 * ix3 + IC3) mod M3;
      j   := 1 + ((97 * ix3) / M3);
      temp := r(j);
      r(j) := float(ix1 + ix2 * integer(RM2)) * RM1;
      return temp;
    end ran1;

    function random_ND return float is
      use math_lib;
      fac, r, v1, v2	: float;
      temp		: float;
      begin
      if (iset = 0) then
	loop
	  v1 := 2.0 * ran1 -1.0;
	  v2 := 2.0 * ran1 -1.0;
	  r  := v1 * v1 + v2 * v2;
	  exit when (r >= 1.0);
	end loop;
	temp := ln(r)/r;
	if (temp < 0.0) then
	  fac  := sqrt(-2.0 * temp);
	else
	  fac  := sqrt(2.0 * temp);
	end if;
	gset := v1 * fac;
	iset := 1;
	temp := v2 * fac;
	return temp;
      else
	iset := 0;
	return gset;
      end if;
      end random_ND;

      function random_ND_integer(reach : integer) return integer is
        value		: integer := 0;
	minus_one	: integer := -1;
      begin
	value := integer(random_ND * float(reach)); 
	if (value < 0) then
	  value := (value * minus_one);
        end if;
	return value;
      end random_ND_integer;

      function random_ED return float is
      use math_lib;
        dummy : float := 0.0;
      begin
        dummy := -1.0 * (ln(ran1)/ln(10.0));
        return dummy;
      end random_ED;

      function random_ED_integer(reach : integer) return integer is
        value		: integer := 0;
	minus_one	: integer := -1;
      begin
	value := integer(random_ED * float(reach)); 
	if (value < 0) then
	  value := (value * minus_one);
        end if;
	return value;
      end random_ED_integer;

      function random_PD return float is
      use math_lib;
      begin
      end random_PD;

-- Initialization of package
use calendar;
begin
  init_value := integer(seconds(clock));
  if (init_value > 0) then
    init_value := -1 * init_value;
  end if;
end random;
