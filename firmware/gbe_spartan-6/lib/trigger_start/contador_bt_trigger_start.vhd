library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity contador_bt_trigger_start is
	
	port(
	
	RST,CLK : in std_logic;
	
	stop_time	: 	in std_logic_vector(23 downto 0);
	
	CLR : in std_logic;
	
	BT : out std_logic
	
	);
	
end contador_bt_trigger_start; 


architecture secuencial of contador_bt_trigger_start is

signal qp, qn : std_logic_vector(23 downto 0);

begin
	
	c1 : process (CLR,stop_time, qp)
	begin
	
	if (CLR='0') then
		
		if(qp=stop_time) then
		
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