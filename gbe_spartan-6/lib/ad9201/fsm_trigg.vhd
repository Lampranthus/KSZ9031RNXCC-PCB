library ieee;
use ieee.std_logic_1164.all;

entity fsm_trigg is

	port(
	
	RST,CLK : in std_logic;
	
	trigg_sw0 : in std_logic;
	sw0 : in std_logic;
	end_sample : in std_logic;
	
	op_wr : out std_logic;
	start_ram : out std_logic;
	data_last : out std_logic
	
	);
end fsm_trigg;

architecture fsm of fsm_trigg is	


signal qp, qn : std_logic_vector(1 downto 0);

begin  
	
	c1 : process(qp,trigg_sw0,sw0,end_sample)
	begin
		
		case(qp) is
		
		--s0
		when "00" =>
		op_wr <= '1';
		start_ram <= '0'; 
		data_last <= '0';
		
		if((trigg_sw0='1') and (sw0 = '0')) then
			qn <= "01";
		else
			qn <= "00";
		end if;
		
		--s1
		when "01" =>
		op_wr <= '0';
		start_ram <= '1'; 
		data_last <= '1';
		
		qn <= "10";
		
		--s2
		when others =>
		op_wr <= '0';
		start_ram <= '0'; 
		data_last <= '1';
		
		if(end_sample = '1' or (sw0 = '1')) then
			qn <= "00";
		else 
			qn <= "10";
		end if;
		
		
	
		end case;
		
	end process;
	
	secuencial : process(RST,CLK)
	begin
		if(RST='0') then
			qp <= (others => '0');
		elsif(CLK'event and CLK='1') then
			qp <= qn;
		end if;
	end process;
	
end fsm;