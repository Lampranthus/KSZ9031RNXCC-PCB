library ieee;
use ieee.std_logic_1164.all;

entity fsm_trigger_start is

	port(
	
	RST,CLK : in std_logic;
	s_trigger : in std_logic_vector(1 downto 0);
	s_ext_oneshot : in std_logic_vector(1 downto 0);
	s_ext_delay : in std_logic_vector(1 downto 0);
	clr_start : out std_logic;
	clr_stop : out std_logic;
	clr_delay_start : out std_logic;
	clr_delay_stop : out std_logic;
	op_start : out std_logic_vector(1 downto 0);
	op_stop : out std_logic_vector(1 downto 0)
	
	);
end fsm_trigger_start;

architecture fsm of fsm_trigger_start is


signal qp : std_logic_vector(5 downto 0);

begin  
	
	c1 : process(qp)
	begin
		
		case (qp) is
		
		--s0
		when "000000" =>
		clr_start <= '0'; --run bt start "\x00" "\x50" 
		clr_stop <= '0';	--run bt stop
		op_start <= "00";--internal start
		op_stop <= "00";--internal stop
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop
		
		--s1
		when "000001" =>
		clr_start <= '0'; ----run bt start "\x01" "\x50" 
		clr_stop <= '1';	--reset bt stop
		op_start <= "00"; --internal start
		op_stop <= "01";  --external stop
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop
		
		--s2
		when "000010" =>
		clr_start <= '1'; --reset bt start "\x02" "\x50" 
		clr_stop <= '0';	--run bt stop
		op_start <= "01"; --external start
		op_stop <= "00";	--internal stop
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop
		
		--s3
		when "000011" =>
		clr_start <= '1'; --reset bt start "\x03" "\x50" 
		clr_stop <= '1';	--reset bt stop
		op_start <= "01"; --external start
		op_stop <= "01";	--external stops
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop
		
		--oneshot stop, oneshot need be an external trigger
		when "000101" =>
		clr_start <= '0'; --run bt start "\x00" or "\x01" "\x51" 
		clr_stop <= '1';	--reset bt stop
		op_start <= "00"; --internal start
		op_stop <= "10";	--external stops with oneshot
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop
	
		
		--oneshot start, oneshot need be an external trigger
		when "001010" =>
		clr_start <= '1'; --reset bt start "\x00" or "\x02" "\x52" 
		clr_stop <= '0';	--run bt stop
		op_start <= "10"; --external start with oneshot
		op_stop <= "00";	--internal stop
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop
		
		
		--oneshot start and stop, oneshot need be an external trigger
		when "001111" =>
		clr_start <= '1'; --reset bt start "\x0X" "\x53" 
		clr_stop <= '1';	--reset bt stop
		op_start <= "10"; --external start with oneshot
		op_stop <= "10";	--external stops with oneshot
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop
		

		
		--delay external stop and internal start 
		when "010101" =>
		clr_start <= '0'; ----run bt start "\x01" or "\x00" "\x51" or "\x50" "\x81" 
		clr_stop <= '1';	--reset bt stop
		op_start <= "00"; --internal start
		op_stop <= "11";  --external stop with one shot and delay
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '0';--run bt delay stop
		
		--delay external start and internal stop DEFAULT
		when "101010" =>
		clr_start <= '1'; ----run bt start "\x02" or "\x00" "\x50" or "\x52" "\x82" 
		clr_stop <= '0';	--run bt stop
		op_start <= "11"; --external start with one shot and delay
		op_stop <= "00";  --internal stop
		clr_delay_start <= '0';--run bt delay start
		clr_delay_stop <= '1';--reset bt delay stop

		
		--delay external start and stop 
		when "111111" =>
		clr_start <= '1'; ----reset bt start "\x0X" "\x5X" "\x83" 
		clr_stop <= '1';	--reset bt stop
		op_start <= "11"; --external start with one shot and delay
		op_stop <= "11";  --external stop with one shot and delay
		clr_delay_start <= '0';--run bt delay start
		clr_delay_stop <= '0';--run bt delay stop
		
		--default all internal triggers
		when others =>
		clr_start <= '0'; --run bt start "\x00" "\x50" 
		clr_stop <= '0';	--run bt stop
		op_start <= "00";--internal start
		op_stop <= "00";--internal stop
		clr_delay_start <= '1';--reset bt delay start
		clr_delay_stop <= '1';--reset bt delay stop

		end case;
		
	end process;
	
	secuencial : process(RST,CLK)
	begin
		if(RST='0') then
			qp <= "101010"; --DEFAULT 
		elsif(CLK'event and CLK='1') then
			qp <= s_ext_delay & s_ext_oneshot & s_trigger;
		end if;
	end process;
	
end fsm;