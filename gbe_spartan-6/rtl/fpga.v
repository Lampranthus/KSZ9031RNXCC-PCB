/*

Copyright (c) 2020 Alex Forencich

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

// Language: Verilog 2001

`resetall
`timescale 1ns / 1ps
`default_nettype none

/*
 * FPGA top-level module
 */
module fpga (
    /*
     * Clock: 125MHz
     */
    input  wire        clk, //50Mhz
	 input  wire        rst,

    /*
     * GPIO
     */
    input  wire [1:0]  push,
    input  wire [7:0]  sw,
    output wire [7:0]  led,
	 
	 /*
     * UART
     */
	 output wire txd,
	 input  wire rxd,
	 
	 /*
     * 1GbE PHY control (KSZ9031RNXCC) 
     */
	 output wire MDC,
	 inout  wire MDIO,
	 input  wire V33,
	 input  wire CLK_125MHZ,
	 input  wire INT_N,
	 output wire RST_N,

    /*
     * Ethernet: 1000BASE-T RGMII
     */
    output wire        ENET0_GTX_CLK,
    output wire [3:0]  ENET0_TX_DATA,
    output wire        ENET0_TX_EN,
    input  wire        ENET0_RX_CLK,
    input  wire [3:0]  ENET0_RX_DATA,
    input  wire        ENET0_RX_DV,
    output wire        ENET0_RST_N,
    input  wire        ENET0_INT_N
);

// Clock and reset

// Internal 125 MHz clock
wire clk_int;
wire rst_int;

assign led = sw;

assign MDIO = 1'bz;
assign MDC = 1'b0;

assign txd = 1'b0;
wire unused_rxd;
assign unused_rxd = rxd;

wire unused_INT_N;
assign unused_INT_N = INT_N;

wire unused_V33;
assign unused_V33 = V33;

wire unused_CLK_125MHZ;
assign unused_CLK_125MHZ = CLK_125MHZ;

assign RST_N = ~push[0] && ~push[1];
wire pll_rst = ~rst;
wire pll_locked;

wire clk90_int; //clock 90degre

PLL(// Clock in ports
  .CLK_IN1(clk),
  // Clock out ports
  .CLK_OUT1(clk_int),//125Mhz
  .CLK_OUT2(clk90_int),//125MHz 90Deg
  // Status and control signals
  .RESET(pll_rst),
  .LOCKED(pll_locked)
 );

sync_reset #(
    .N(4)
)
sync_reset_inst (
    .clk(clk_int),
    .rst(~pll_locked),
    .out(rst_int)
);

// GPIO
wire [1:0] btn_int;
wire [7:0] sw_int;

debounce_switch #(
    .WIDTH(4+18),
    .N(4),
    .RATE(125000)
)
debounce_switch_inst (
    .clk(clk_int),
    .rst(rst_int),
    .in({~push,
        sw}),
    .out({btn_int,
        sw_int})
);

fpga_core #(
    .TARGET("XILINX")
)
core_inst (
    /*
     * Clock: 125MHz
     * Synchronous reset
     */
    .clk(clk_int),
	 .clk90(clk90_int),
    .rst(rst_int),

    /*
     * GPIO
     */
    //.btn(btn_int),
    //.sw(sw_int),
    //.led(led),
	 
	 /*
     * UART
     */
	 //.txd(txd),
	 //.rxd(rxd),
	
    /*
     * Ethernet: 1000BASE-T RGMII
     */
    .phy0_rx_clk(ENET0_RX_CLK),
    .phy0_rxd(ENET0_RX_DATA),
    .phy0_rx_ctl(ENET0_RX_DV),
    .phy0_tx_clk(ENET0_GTX_CLK),
    .phy0_txd(ENET0_TX_DATA),
    .phy0_tx_ctl(ENET0_TX_EN),
    .phy0_reset_n(ENET0_RST_N),
    .phy0_int_n(ENET0_INT_N)
);

endmodule

`resetall
