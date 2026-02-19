library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;


entity AD9201 is

	port(
	
	--debug
	
	debug_1 : 		out std_logic;
	debug_2 : 		out std_logic;
	debug_3 : 		out std_logic;
	
	------------------------------------------
	
	RST : 			in std_logic;
	CLK : 			in std_logic;
	X	: 				in std_logic_vector(9 downto 0);
	D	: 				out std_logic_vector(9 downto 0);
	adc_clk : 		out std_logic;
	start : 	in std_logic;
	stop : 	in std_logic;
	int_rst : 		out std_logic;
	
	sw0 : 	in std_logic;
	trigg_sw0 : 	in std_logic;
	
	int_dt	: 	in std_logic_vector(23 downto 0);
	t_sample	: 	in std_logic_vector(23 downto 0);
	
	--rx_reg : in std_logic_vector(39 downto 0);
	
	tx_adc_axis_tdata	: 	out std_logic_vector(7 downto 0);
	tx_adc_axis_tvalid : 	out std_logic;
	tx_adc_axis_tready : 	in std_logic;
	tx_adc_axis_tlast : 	out std_logic;
	tx_adc_axis_tuser : 	out std_logic
	);	
	
end AD9201;

architecture fsm of AD9201 is 

--------------------------------------------------------------------------------------

component contador_bt_sample is
	
	port(
	
	RST,CLK : in std_logic;
	
	t_sample 	: 	in std_logic_vector(23 downto 0);
	
	CLR : in std_logic;
	
	BT : out std_logic
	
	);
	
	
end component;


component contador_bt_int is
	
	port(
	
	RST,CLK : in std_logic;
	
	int_dt	: 	in std_logic_vector(23 downto 0);
	
	CLR : in std_logic;
	
	BT : out std_logic
	
	);
	
end component;



component fsm_time is

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
	
end component;

component parallel_reg_10 is
	
	port(
	
	Din : in std_logic_vector(9 downto 0);   
	
	OPR : in std_logic_vector(1 downto 0);
	
	RST,CLK : in std_logic; 
	
	Qout : out std_logic_vector(9 downto 0)	
	
	);
	
end component;

component contador_ahb_16 is

	port(
		RST,CLK : in std_logic;
		opc : in std_logic_vector(1 downto 0);
		Q : out std_logic_vector(14 downto 0)
	);
	
end component;

component fsm_pmt	is
	
	port(
	
	RST, CLK : in std_logic;
	
	start_sync : in std_logic;
	stop_sync : in std_logic;
	pmt : out std_logic
	
	);
	
end component;

component fsm_axis is

	port(
	
	RST,CLK : in std_logic;
	
	data_valid : in std_logic;
	data_last : in std_logic;
	tready : in std_logic;

	
	tvalid : out std_logic;
	tlast : out std_logic;
	tuser : out std_logic;
	d_mux : out std_logic_vector(2 downto 0);
	
	end_sample : out std_logic
	
	);
	
end component;

component mux_6a1_8 is

	port(
	x1,x2,x3,x4,x5	: in std_logic_vector(7 downto 0);
	s			: in std_logic_vector(2 downto 0);
	y			: out std_logic_vector(7 downto 0)
	);
end component;

component ram_dual IS
   GENERIC (
      ram_width : INTEGER := 40;
      ram_depth : INTEGER := 2048
   );
   PORT (
      clock1 : IN   std_logic;
      clock2 : IN   std_logic;
      data   : IN   std_logic_vector(ram_width - 1 DOWNTO 0);
      write_address : IN  std_logic_vector(10 DOWNTO 0);
      read_address  : IN  std_logic_vector(10 DOWNTO 0);
      we     : IN   std_logic;
      q      : OUT  std_logic_vector(ram_width - 1 DOWNTO 0)
   );
	
end component;

component fsm_ram is

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
	
end component;

component mux_2a1_8 is

	port(
	x1,x2	: in std_logic_vector(7 downto 0);
	s			: in std_logic;
	y			: out std_logic_vector(7 downto 0)
	);
	
end component;

component fsm_trigg is

	port(
	
	RST,CLK : in std_logic;
	
	trigg_sw0 : in std_logic;
	sw0 : in std_logic;
	end_sample : in std_logic;
	
	op_wr : out std_logic;
	start_ram : out std_logic;
	data_last : out std_logic
	
	);
	
end component;


component one_shot	is
	
	port(
	
	RST, CLK : in std_logic;
	
	x : in std_logic;
	y : out std_logic
	
	);
	
end component;

--------------------------------------------------------------------------------------

signal  s_int_rst, s_adc_clk, s_data_valid, clr_sample, bt_sample, clr_int, bt_int, sample_c, pmt, data_last, rst_sample_c, start_ram, end_sample, ram_sample_c, s_tx_adc_axis_tlast : std_logic;

signal s_datos : std_logic_vector(9 downto 0);
signal n_sample : std_logic_vector(14 downto 0);
signal n_pmt : std_logic_vector(14 downto 0);
signal d_mux : std_logic_vector(2 downto 0);
signal data_ram : std_logic_vector(39 downto 0);
signal data_ram_in : std_logic_vector(39 downto 0);
signal ram_n_sample : std_logic_vector(14 downto 0);
signal s_tx_adc_axis_tdata, trigger_axis_tdata, ram_axis_tdata : 	std_logic_vector(7 downto 0);

signal s_sw0 : std_logic;
signal s_start : std_logic;
signal op_wr : std_logic;

signal send_trigg, trigg_last : std_logic;
signal s_trigg_sw0  : std_logic;

begin 
	
	int_rst <= s_int_rst;
	adc_clk <= s_adc_clk;
	
	D <= s_datos;
	
	debug_1 <= s_int_rst;
	debug_2 <= s_adc_clk;
	debug_3 <= pmt;
	
	data_ram_in <= (n_pmt-1) & n_sample & s_datos;
	
	tx_adc_axis_tlast <= s_tx_adc_axis_tlast;
	
	s_sw0 <= sw0;
	
	s_start <= start;
	
	tx_adc_axis_tdata <= s_tx_adc_axis_tdata;
	
	sc0 : contador_bt_sample port map(RST, CLK, t_sample,clr_sample, bt_sample);
	sc1 : contador_bt_int port map(RST, CLK, int_dt ,clr_int, bt_int);
	sc2 : fsm_time port map(RST, CLK, pmt, bt_sample, bt_int, clr_sample, clr_int, s_adc_clk, s_int_rst,s_data_valid,sample_c);
	sc3 : contador_ahb_16 port map(RST, CLK, (rst_sample_c) & sample_c,n_sample);
	sc4 : contador_ahb_16 port map(RST and s_sw0, CLK, '0' & s_start,n_pmt);
	sc5 : parallel_reg_10 port map (X,"00", RST, CLK, s_datos);
	sc6 : fsm_pmt port map (RST and s_sw0,CLK,s_start,stop,pmt);
	sc8 : fsm_axis port map(RST, CLK, (start_ram) or (send_trigg), (data_last) or (trigg_last), tx_adc_axis_tready, tx_adc_axis_tvalid, s_tx_adc_axis_tlast, tx_adc_axis_tuser, d_mux, end_sample);
	sc9 : mux_6a1_8 port map(data_ram(39 downto 32), data_ram(31 downto 24), data_ram(23 downto 16), data_ram(15 downto 8), data_ram(7 downto 0), d_mux,ram_axis_tdata);
	sc10 : ram_dual port map(CLK, CLK, data_ram_in, n_sample(10 downto 0),ram_n_sample(10 downto 0),s_data_valid,data_ram);
	sc11 : contador_ahb_16 port map(RST, CLK, (rst_sample_c) & ram_sample_c,ram_n_sample);
	sc12 : fsm_ram port map(RST, CLK, pmt,n_sample, ram_n_sample, end_sample, start_ram, rst_sample_c, ram_sample_c, data_last, s_tx_adc_axis_tlast);
	sc13 : mux_6a1_8 port map("01010100", "01010010", "01001001", "01000111", "01000111", d_mux,trigger_axis_tdata);
	--sc13 : mux_6a1_8 port map(rx_reg(39 downto 32), rx_reg(31 downto 24), rx_reg(23 downto 16), rx_reg(15 downto 8), rx_reg(7 downto 0), d_mux,trigger_axis_tdata);
	sc14 : mux_2a1_8 port map(trigger_axis_tdata, ram_axis_tdata, op_wr, s_tx_adc_axis_tdata);
	sc15 : fsm_trigg port map(RST,CLK, s_trigg_sw0, s_sw0,end_sample, op_wr,send_trigg,trigg_last);
	sc16 : one_shot port map(RST, CLK, trigg_sw0, s_trigg_sw0);
	
	
end fsm;