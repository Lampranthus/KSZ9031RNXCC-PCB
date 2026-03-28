library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity parallel_reg_10 is
	
	
	port(
	
	Din : in std_logic_vector(9 downto 0);   
	
	OPR : in std_logic_vector(1 downto 0);
	
	RST,CLK : in std_logic; 
	
	Qout : out std_logic_vector(9 downto 0)	
	
	);
	
end parallel_reg_10;


architecture simple of parallel_reg_10 is

signal qn, qp : std_logic_vector(9 downto 0);

begin
	
	c1 : process(OPR, qp, Din)
	begin 
		
		case (OPR) is
			
			when "01" => qn <= qp;
			when "00" => qn <= Din;
			when others => qn <= (others => '0');
			
		end case;
		
	end process;

	secuencial : process (RST, CLK)
	begin
		
		if(RST='0') then
			
			qp <= (others => '0');
			
		elsif(CLK'event and CLK='1') then
			
			qp <= qn;	
			
		end if;
		
	end process;	
	
	Qout <= qp;
	
end simple;