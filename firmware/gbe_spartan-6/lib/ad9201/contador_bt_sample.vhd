library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity contador_bt_sample is
	
	port(
	
	RST,CLK : in std_logic;
	
	t_sample 	: 	in std_logic_vector(23 downto 0);
	
	CLR : in std_logic;
	
	BT : out std_logic
	
	);
	
end contador_bt_sample; 


architecture secuencial of contador_bt_sample is

signal qp, qn : std_logic_vector(23 downto 0);

begin
	
	c1 : process (CLR,t_sample,qp)
	begin
		
	if (CLR='0') then
		
	if(qp=t_sample) then
		
		qn <= (others => '0');
		BT <= '1';
		
	else
		
		qn <= qp + 1;
		BT <= '0';
		
	end if;
	
	else 
		
		qn <= (others => '0');
		BT <= '0';
	
	end if;
	
	end process;
	
	
	secuencial : process (RST,CLK)
	begin
		
	if(RST = '0') then
		
		qp <= (others => '0');
		
	elsif(CLK'event and CLK='1') then
		qp <= qn;
	end if;
	end process;
end secuencial;