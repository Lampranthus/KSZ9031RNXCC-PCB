library ieee;
use ieee.std_logic_1164.all;

entity fsm_time is

	port(
	
	RST,CLK : in std_logic;
	
	pmt : in std_logic;
	
	bt_sample : in std_logic;
	bt_int : in std_logic;
	
	clr_sample : out std_logic;
	clr_int : out std_logic;
	
	adc_clk : out std_logic;
	int_rst : out std_logic;
	data_valid : out std_logic;
	sample_c : out std_logic
	
	);
end fsm_time;

architecture fsm of fsm_time is	


signal qp, qn : std_logic_vector(2 downto 0);

begin  
	
	c1 : process(qp,pmt,bt_sample,bt_int)
	begin
		
		case(qp) is
		
		--s0
		when "000" =>
		clr_sample <= '1'; 

		clr_int <= '1';

		adc_clk <= '0';
		int_rst <= '1';
		data_valid <= '0';
		sample_c <= '0';
		
		if(pmt='1') then
			qn <= "001";
		else
			qn <= "000";
		end if;
		
		--s1
		when "001" =>
		clr_sample <= '0'; --bt sample start

		clr_int <= '0'; --bt int start

		adc_clk <= '0';
		int_rst <= '0';   --ventana de integracion
		data_valid <= '0';
		sample_c <= '0';
		
		if(bt_int='1') then
			qn <= "010";
		else
			qn <= "001";
		end if;
		
		--s2
		when "010" =>
		clr_sample <= '0';
	
		clr_int <= '1'; --bt int reset

		adc_clk <= '1'; --adc_clk up
		int_rst <= '0';   --ventana de integracion
		data_valid <= '0';
		sample_c <= '0';
		
		qn <= "011";
		
		--s3 
		when "011" =>
		
		clr_sample <= '0';

		clr_int <= '1';

		adc_clk <= '1'; --adc_clk up
		int_rst <= '0';   --ventana de integracion
		data_valid <= '0';
		sample_c <= '0';
		
		qn <= "100";
		
		--s4 
		when "100" =>
		clr_sample <= '0';

		clr_int <= '1';

		adc_clk <= '1'; --hold up
		int_rst <= '1';   --reset integragor
		data_valid <= '1'; --valid
		sample_c <= '0'; 
		
		qn <= "101";
		
		--s5
		when "101" =>
		clr_sample <= '0';
		
		clr_int <= '1';

		adc_clk <= '1'; --hold up
		int_rst <= '1';   --reset integragor
		data_valid <= '0'; --valid
		sample_c <= '1';  --counter sample
		
		qn <= "110";
		
		--s6
		when others =>
		clr_sample <= '0';
		
		clr_int <= '1';

		adc_clk <= '0';
		int_rst <= '1';   --reset integragor
		data_valid <= '0'; 
		sample_c <= '0'; 
		
		if(bt_sample='1') then
			qn <= "000";
		else
			qn <= "110";
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