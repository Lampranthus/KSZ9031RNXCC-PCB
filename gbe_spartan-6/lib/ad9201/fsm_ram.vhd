library ieee;
use ieee.std_logic_1164.all;
USE ieee.numeric_std.ALL;


entity fsm_ram is

	port(
	
	RST,CLK : in std_logic;
	
	pmt : in std_logic;
	data_last_n : in std_logic_vector(14 downto 0);
	data_c_n : in std_logic_vector(14 downto 0);
	end_sample : in std_logic; 
	
	start_ram : out std_logic;
	rst_sample_c : out std_logic;
	ram_sample_c : out std_logic;
	data_last : out std_logic;
	
	tlast_axi : in std_logic
	
	);
end fsm_ram;

architecture fsm of fsm_ram is	


signal qp, qn : std_logic_vector(3 downto 0);
signal reg_data_last_p, reg_data_last_n : std_logic_vector(14 downto 0);

begin  
	
	c1 : process(qp,pmt,data_last_n, data_c_n,end_sample, tlast_axi,reg_data_last_p)
	begin
		
		case(qp) is
		
		--s0
		when "0000" =>
		start_ram <= '0'; 
		rst_sample_c <= '0';
		ram_sample_c <= '0';
		data_last <= '0';
		
		if((((unsigned(data_last_n)) - (unsigned(data_c_n))) = 829) or ((pmt = '0') and ((unsigned(data_last_n) - unsigned(data_c_n)) > 1))) then
			qn <= "0001";
			reg_data_last_n <= data_last_n;
		else
			qn <= "0000";
			reg_data_last_n <= reg_data_last_p;
		end if;
		
		--s1
		when "0001" =>
		start_ram <= '1'; 
		rst_sample_c <= '0';
		ram_sample_c <= '0';
		data_last <= '0';
		
		if(end_sample = '1') then
			if( (unsigned(data_c_n) = (unsigned(reg_data_last_p) - 1))) then
				qn <= "0011";
				reg_data_last_n <= reg_data_last_p;
			else
				qn <= "0010";
				reg_data_last_n <= reg_data_last_p;
			end if;
		else
			qn <= "0001";
			reg_data_last_n <= reg_data_last_p;
		end if;
		
		--s2
		when "0010" =>
		start_ram <= '1'; 
		rst_sample_c <= '0';
		ram_sample_c <= '1';
		data_last <= '0';
		
		qn <= "0001";
		reg_data_last_n <= reg_data_last_p;
		
		
		--s3 
		when "0011" =>
		start_ram <= '1'; 
		rst_sample_c <= '0';
		ram_sample_c <= '1';
		data_last <= '1';
		
		qn <= "0100";
		reg_data_last_n <= reg_data_last_p;
		
		
		--s4
		when "0100" =>
		start_ram <= '1'; 
		rst_sample_c <= '0';
		ram_sample_c <= '0';
		data_last <= '1';
		
		if (end_sample = '1') then
			qn <= "0101";
			reg_data_last_n <= reg_data_last_p;
		else
			qn <= "0100";
			reg_data_last_n <= reg_data_last_p;
		end if;
		
		--s5 
		when "0101" =>
		start_ram <= '0'; 
		rst_sample_c <= '0'; 
		ram_sample_c <= '0';
		data_last <= '1';
		
		if (tlast_axi = '1') then
			if (pmt = '0') then
				qn <= "0111";
				reg_data_last_n <= (others => '0');
			else
				qn <= "0110";
				reg_data_last_n <= reg_data_last_p;
			end if;
		else
			qn <= "0101";
			reg_data_last_n <= reg_data_last_p;
		end if;
		
		--s6
		when "0110" =>
		start_ram <= '0'; 
		rst_sample_c <= '0';
		ram_sample_c <= '1';
		data_last <= '1';
	
		qn <= "0000";
		reg_data_last_n <= reg_data_last_p;
		
		
		--s7
		when others =>
		start_ram <= '0'; 
		rst_sample_c <= '1'; --reset counter
		ram_sample_c <= '0';
		data_last <= '1';
		
		reg_data_last_n <= reg_data_last_p;
		qn <= "0000";
		
	
		end case;
		
	end process;
	
	secuencial : process(RST,CLK)
	begin
		if(RST='0') then
			qp <= (others => '0');
			reg_data_last_p <= (others => '0');
		elsif(CLK'event and CLK='1') then
			qp <= qn;
			reg_data_last_p <= reg_data_last_n;
		end if;
	end process;
	
end fsm;