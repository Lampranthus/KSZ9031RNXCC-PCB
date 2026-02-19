library ieee;	   
use ieee.std_logic_1164.all; 


entity mux_2a1_8 is

	port(
	x1,x2	: in std_logic_vector(7 downto 0);
	s			: in std_logic;
	y			: out std_logic_vector(7 downto 0)
	);
end mux_2a1_8;


architecture combinacional of mux_2a1_8 is 
begin
	process (s,x1,x2)
	begin
		case s is
			when '0'	=> y<=x1;
			when others => y<=x2;
		end case;
	end process;
end combinacional;