library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity trigger_start is	
	
	port(
	
	RST,CLK : in std_logic;
	start_time	: 	in std_logic_vector(23 downto 0);
	stop_time	: 	in std_logic_vector(23 downto 0);
	delay_start_time	: 	in std_logic_vector(23 downto 0);
	delay_stop_time	: 	in std_logic_vector(23 downto 0);
	start_ext : in std_logic;
	stop_ext : in std_logic;
	s_trigger : in std_logic_vector(1 downto 0);
	s_ext_oneshot : in std_logic_vector(1 downto 0);
	s_ext_delay : in std_logic_vector(1 downto 0);
	start : out std_logic;
	stop : out std_logic
	
	);	
	
end trigger_start;

architecture fsm of trigger_start is	


component contador_bt_trigger_start is
	
	port(
	
	RST,CLK : in std_logic;
	
	stop_time	: 	in std_logic_vector(23 downto 0);
	
	CLR : in std_logic;
	
	BT : out std_logic
	
	); 
	
end component; 

component fsm_trigger_start is

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
	
end component;	

component mux_2to1_1 is
	port(
	x0,x1,x2,x3	: in std_logic;
	s			: in std_logic_vector(1 downto 0);
	y			: out std_logic
	);
	
end component;

component one_shot	is
	
	port(
	
	RST, CLK : in std_logic;
	
	x : in std_logic;
	y : out std_logic
	
	);
	
end component;


component fsm_toggle is
	port(
	
	RST,CLK : in std_logic;
	bt : in std_logic;
	bt_stop : in std_logic;
	y : out std_logic
	
	);
	
end component;

signal bt_stop, CLR_stop, bt_start, CLR_start, one_shot_start, one_shot_stop, s_start_ext, s_stop_ext : std_logic;	
signal op_start, op_stop : std_logic_vector(1 downto 0);
signal oneshot_start, oneshot_stop : std_logic;
signal delay_start, delay_stop : std_logic;
signal clr_delay_start, clr_delay_stop : std_logic;
signal toggle_delay_start, toggle_delay_stop : std_logic;
signal clr_stop_toggle : std_logic;

begin 

s_start_ext <= start_ext;
s_stop_ext <= stop_ext;
	
	sc0 : contador_bt_trigger_start port map(RST,CLK,stop_time,CLR_stop or clr_stop_toggle,bt_stop);
	
	sc1 : contador_bt_trigger_start port map(RST,CLK,start_time,CLR_start,bt_start);
	
	sc2 : mux_2to1_1 port map(bt_stop, s_stop_ext, oneshot_stop, delay_stop, op_stop, stop);
	
	sc3 : mux_2to1_1 port map(bt_start, s_start_ext, oneshot_start, delay_start, op_start, start);
	
	sc4 : fsm_trigger_start port map(RST,CLK, s_trigger, s_ext_oneshot, s_ext_delay, CLR_start, CLR_stop, clr_delay_start, clr_delay_stop, op_start, op_stop);
	
	sc5 : one_shot port map(RST, CLK, s_start_ext, oneshot_start);
	
	sc6 : one_shot port map(RST, CLK, s_stop_ext, oneshot_stop);
	
	sc7 : contador_bt_trigger_start port map(RST,CLK,delay_start_time,clr_delay_start or toggle_delay_start,delay_start);
	
	sc8 : contador_bt_trigger_start port map(RST,CLK,delay_stop_time,clr_delay_stop or toggle_delay_stop,delay_stop); 
	
	sc9 : fsm_toggle port map(RST,CLK,oneshot_start,delay_start,toggle_delay_start);
	
	sc10 : fsm_toggle port map(RST,CLK,oneshot_stop,delay_stop,toggle_delay_stop);
	
	sc11 : fsm_toggle port map(RST,CLK,(((s_trigger(1) and oneshot_start) or (bt_start and (not s_trigger(1)))) and (not s_ext_delay(1))) or (delay_start and s_ext_delay(1)),bt_stop,clr_stop_toggle);
	
	
end fsm;