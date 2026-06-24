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
 * FPGA core logic
 */
module fpga_core #
(
    parameter TARGET = "GENERIC"
)
(
    /*
     * Clock: 125MHz
     * Synchronous reset
     */
    input  wire       clk,
	 input  wire       clk90,
    input  wire       rst,

    /*
     * GPIO
     */
    input  wire [1:0]  push,
    input  wire [7:0]  sw,
    output wire [7:0]  led,
	 //output wire [1:0]  molex,
	 
	 /*
     * 1GbE PHY control (KSZ9031RNXCC) 
     */
	 output wire MDC,
	 inout  wire MDIO,
	 input  wire V3_3,
	 input  wire CLK_125MHZ,
	 
	 
	 /*
     * UART
     */
	 output wire txd,
	 input  wire rxd,

    /*
     * Ethernet: 1000BASE-T RGMII
     */
    input  wire       phy0_rx_clk,
    input  wire [3:0] phy0_rxd,
    input  wire       phy0_rx_ctl,
    output wire       phy0_tx_clk,
    output wire [3:0] phy0_txd,
    output wire       phy0_tx_ctl,
    output wire       phy0_reset_n,
    input  wire       phy0_int_n
);

// AXI between MAC and Ethernet modules
wire [7:0] rx_axis_tdata;
wire rx_axis_tvalid;
wire rx_axis_tready;
wire rx_axis_tlast;
wire rx_axis_tuser;

wire [7:0] tx_axis_tdata;
wire tx_axis_tvalid;
wire tx_axis_tready;
wire tx_axis_tlast;
wire tx_axis_tuser;

// Ethernet frame between Ethernet modules and UDP stack
wire rx_eth_hdr_ready;
wire rx_eth_hdr_valid;
wire [47:0] rx_eth_dest_mac;
wire [47:0] rx_eth_src_mac;
wire [15:0] rx_eth_type;
wire [7:0] rx_eth_payload_axis_tdata;
wire rx_eth_payload_axis_tvalid;
wire rx_eth_payload_axis_tready;
wire rx_eth_payload_axis_tlast;
wire rx_eth_payload_axis_tuser;

wire tx_eth_hdr_ready;
wire tx_eth_hdr_valid;
wire [47:0] tx_eth_dest_mac;
wire [47:0] tx_eth_src_mac;
wire [15:0] tx_eth_type;
wire [7:0] tx_eth_payload_axis_tdata;
wire tx_eth_payload_axis_tvalid;
wire tx_eth_payload_axis_tready;
wire tx_eth_payload_axis_tlast;
wire tx_eth_payload_axis_tuser;

// IP frame connections
wire rx_ip_hdr_valid;
wire rx_ip_hdr_ready;
wire [47:0] rx_ip_eth_dest_mac;
wire [47:0] rx_ip_eth_src_mac;
wire [15:0] rx_ip_eth_type;
wire [3:0] rx_ip_version;
wire [3:0] rx_ip_ihl;
wire [5:0] rx_ip_dscp;
wire [1:0] rx_ip_ecn;
wire [15:0] rx_ip_length;
wire [15:0] rx_ip_identification;
wire [2:0] rx_ip_flags;
wire [12:0] rx_ip_fragment_offset;
wire [7:0] rx_ip_ttl;
wire [7:0] rx_ip_protocol;
wire [15:0] rx_ip_header_checksum;
wire [31:0] rx_ip_source_ip;
wire [31:0] rx_ip_dest_ip;
wire [7:0] rx_ip_payload_axis_tdata;
wire rx_ip_payload_axis_tvalid;
wire rx_ip_payload_axis_tready;
wire rx_ip_payload_axis_tlast;
wire rx_ip_payload_axis_tuser;

wire tx_ip_hdr_valid;
wire tx_ip_hdr_ready;
wire [5:0] tx_ip_dscp;
wire [1:0] tx_ip_ecn;
wire [15:0] tx_ip_length;
wire [7:0] tx_ip_ttl;
wire [7:0] tx_ip_protocol;
wire [31:0] tx_ip_source_ip;
wire [31:0] tx_ip_dest_ip;
wire [7:0] tx_ip_payload_axis_tdata;
wire tx_ip_payload_axis_tvalid;
wire tx_ip_payload_axis_tready;
wire tx_ip_payload_axis_tlast;
wire tx_ip_payload_axis_tuser;

// UDP frame connections
wire rx_udp_hdr_valid;
wire rx_udp_hdr_ready;
wire [47:0] rx_udp_eth_dest_mac;
wire [47:0] rx_udp_eth_src_mac;
wire [15:0] rx_udp_eth_type;
wire [3:0] rx_udp_ip_version;
wire [3:0] rx_udp_ip_ihl;
wire [5:0] rx_udp_ip_dscp;
wire [1:0] rx_udp_ip_ecn;
wire [15:0] rx_udp_ip_length;
wire [15:0] rx_udp_ip_identification;
wire [2:0] rx_udp_ip_flags;
wire [12:0] rx_udp_ip_fragment_offset;
wire [7:0] rx_udp_ip_ttl;
wire [7:0] rx_udp_ip_protocol;
wire [15:0] rx_udp_ip_header_checksum;
wire [31:0] rx_udp_ip_source_ip;
wire [31:0] rx_udp_ip_dest_ip;
wire [15:0] rx_udp_source_port;
wire [15:0] rx_udp_dest_port;
wire [15:0] rx_udp_length;
wire [15:0] rx_udp_checksum;
wire [7:0] rx_udp_payload_axis_tdata;
wire rx_udp_payload_axis_tvalid;
wire rx_udp_payload_axis_tready;
wire rx_udp_payload_axis_tlast;
wire rx_udp_payload_axis_tuser;

wire tx_udp_hdr_valid;
wire tx_udp_hdr_ready;
wire [5:0] tx_udp_ip_dscp;
wire [1:0] tx_udp_ip_ecn;
wire [7:0] tx_udp_ip_ttl;
wire [31:0] tx_udp_ip_source_ip;
wire [31:0] tx_udp_ip_dest_ip;
wire [15:0] tx_udp_source_port;
wire [15:0] tx_udp_dest_port;
wire [15:0] tx_udp_length;
wire [15:0] tx_udp_checksum;
wire [7:0] tx_udp_payload_axis_tdata;
wire tx_udp_payload_axis_tvalid;
wire tx_udp_payload_axis_tready;
wire tx_udp_payload_axis_tlast;
wire tx_udp_payload_axis_tuser;

wire [7:0] rx_fifo_udp_payload_axis_tdata;
wire rx_fifo_udp_payload_axis_tvalid;
wire rx_fifo_udp_payload_axis_tready;
wire rx_fifo_udp_payload_axis_tlast;
wire rx_fifo_udp_payload_axis_tuser;

wire [7:0] tx_fifo_udp_payload_axis_tdata;
wire tx_fifo_udp_payload_axis_tvalid;
wire tx_fifo_udp_payload_axis_tready;
wire tx_fifo_udp_payload_axis_tlast;
wire tx_fifo_udp_payload_axis_tuser;

// IP ports not used
assign rx_ip_hdr_ready = 1;
assign rx_ip_payload_axis_tready = 1;

assign tx_ip_hdr_valid = 0;
assign tx_ip_dscp = 0;
assign tx_ip_ecn = 0;
assign tx_ip_length = 0;
assign tx_ip_ttl = 0;
assign tx_ip_protocol = 0;
assign tx_ip_source_ip = 0;
assign tx_ip_dest_ip = 0;
assign tx_ip_payload_axis_tdata = 0;
assign tx_ip_payload_axis_tvalid = 0;
assign tx_ip_payload_axis_tlast = 0;
assign tx_ip_payload_axis_tuser = 0;

//transmision de paquetes de bytes

reg [15:0] cont_reg;
reg [7:0] tx_fifo_axis_tdata;
reg [15:0] tx_fifo_axis_tdata_reg; // sequential data
reg word_flag;
reg [7:0] tx_axis_tdata_test = "X"; //"X" constant data
reg tx_fifo_axis_tvalid;
wire tx_fifo_axis_tready;
reg tx_fifo_axis_tlast;
reg tx_fifo_axis_tuser = 0; 
reg [31:0] pkt_n_reg;
reg [2:0] state;
reg ocupado;
reg send_regs;
reg [15:0] udp_bit_regs;

reg send_mdio;

reg [7:0] random_data; //random_data
// Linear-feedback shift register
reg [7:0] lfsr;

wire feedback;

// Feedback
assign feedback = lfsr[7] ^ lfsr[5] ^ lfsr[4] ^ lfsr[3];

// maquina de estados para trasnmision 
always @(posedge clk) begin

    if (~rx_random) begin
        lfsr <= 8'hAB; // Semilla inicial (no todos deben ser ceros)
    end else begin
        // Generar nuevo valor cada ciclo de reloj cuando rx_random esta en alto
        lfsr[7:0] <= {lfsr[6:0], feedback};
        random_data <= lfsr;
    end

    if (rst) begin
        state <=  3'd0;
        tx_fifo_axis_tdata <= 8'd0;
        tx_fifo_axis_tdata_reg <= 16'd0;
		  word_flag <= 0;
        tx_fifo_axis_tvalid <= 0;
        cont_reg <= 16'd0;
        tx_fifo_axis_tlast <= 0;
        pkt_n_reg <= 32'd0;
        ocupado <= 0;
		  send_regs <= 0;
		  udp_bit_regs <= 0;
		  send_mdio <= 0;
		  
		  
    end else begin
       // Estado 0: Esperando trigger o flood sin modo loopback
        if (state == 3'd0) begin
        
            if ((rx_trigger || flood) && ~rx_loopb) begin
                ocupado <= 1; //empieza el envio de los paquetes
                state <= 3'd1;
                tx_fifo_axis_tvalid <= 1; //tvalid 1 en el siguiente ciclo
                // primera palabra del mensaje
					 if(rx_random) begin
                    tx_fifo_axis_tdata <= random_data;
                end else if(rx_constante)begin
						  tx_fifo_axis_tdata <= tx_axis_tdata_test;
					 end else begin
						  if (word_flag) begin //if word flag send the lsB increase the sequense and reset word flag else send msB and rise word flag
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[7:0];
							tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 16'd1;
							word_flag <= 0;
						  end else begin
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[15:8];
							word_flag <= 1;
						  end   
                end
            end else if (full_reg_flag) begin
					 ocupado <= 1;
					 send_regs <= 1;
					 tx_fifo_axis_tvalid <= 1; //tvalid 1 en el siguiente ciclo
					 tx_fifo_axis_tdata <= full_registro[FRAME_BITS-1:FRAME_BITS-8];
					 state <= 3'd1;
				end else if (mdio_read_ready) begin
					 ocupado <= 1;
					 send_mdio <= 1;
					 tx_fifo_axis_tvalid <= 1;
					 tx_fifo_axis_tdata <= {3'd0,mdio_reg};
					 state <= 3'd1;
				end
				
        end 
        // Estado 1: Enviando primera palabra del mensaje
        else if (state == 3'd1) begin
 
            if (tx_fifo_axis_tready) begin
                state <= 3'd2;
                // Primer dato aceptado y eligiendo segunda palabra
					 if(send_regs) begin
						  tx_fifo_axis_tdata <= full_registro[FRAME_BITS-9:FRAME_BITS-16];
					 end else if(send_mdio) begin
						tx_fifo_axis_tdata <= mdio_rdata_reg[15:8];
                end else if(rx_random) begin
                    tx_fifo_axis_tdata <= random_data;
                end else if(rx_constante)begin
						  tx_fifo_axis_tdata <= tx_axis_tdata_test;
					 end else begin
						  if (word_flag) begin //if word flag send the lsB increase the sequense and reset word flag else send msB and rise word flag
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[7:0];
							tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 16'd1;
							word_flag <= 0;
						  end else begin
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[15:8];
							word_flag <= 1;
						  end ;
                end
                cont_reg <= cont_reg + 1;
            end

        end 
        // Estado 2: Enviando segunda palabra y el resto
        else if (state == 3'd2) begin
        
            if (tx_fifo_axis_tready) begin
                cont_reg <= cont_reg + 1;
                if ((~send_regs && (cont_reg == (n_bytes - 2))) || (cont_reg == (FRAME_BYTES-2) && send_regs) || send_mdio) begin // si se llego a la penultima palabra elegir el ultimo dato y enviarlo en el estado 3
                    state <= 3'd3;
                    tx_fifo_axis_tlast <= 1;
						  
						  if(flood) begin
								pkt_n_reg <= pkt_n; // si se esta en flood igualar a pkt_n para que cuando se desacative flood se dejen de enviar paketes en el siguient estado
						  end else begin
								pkt_n_reg <= pkt_n_reg + 1; // contar numero de paquete si no se esta en flood
						  end
                    
						  if(send_regs) begin
						      tx_fifo_axis_tdata <= full_registro[7:0];
						  end else if(send_mdio) begin
								tx_fifo_axis_tdata <= mdio_rdata_reg[7:0];
						  end else if(rx_random) begin
								tx_fifo_axis_tdata <= random_data;
						  end else if(rx_constante)begin
								tx_fifo_axis_tdata <= tx_axis_tdata_test;
						  end else begin
							  if (word_flag) begin //if word flag send the lsB increase the sequense and reset word flag else send msB and rise word flag
								tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[7:0];
								tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 16'd1;
								word_flag <= 0;
							  end else begin
								tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[15:8];
								word_flag <= 1;
							  end 
						  end
					 // si no se ha lleado elegir la siguiente palabra del paquete y no salir del estado 2
                end else if(send_regs) begin
						  tx_fifo_axis_tdata <= full_registro[(FRAME_BITS - 17 - udp_bit_regs) -: 8];
						  udp_bit_regs <= udp_bit_regs + 8;
                end else if(rx_random) begin
                    tx_fifo_axis_tdata <= random_data;
                end else if(rx_constante)begin
						  tx_fifo_axis_tdata <= tx_axis_tdata_test;
					 end else begin
						  if (word_flag) begin //if word flag send the lsB increase the sequense and reset word flag else send msB and rise word flag
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[7:0];
							tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 16'd1;
							word_flag <= 0;
						  end else begin
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[15:8];
							word_flag <= 1;
						  end 
                end
            end

        end
        // Estado 3: ciclo donde se envia el ultimo dato del paquete, y se decide si seguir enviado o parar de enviar
        else begin
        
            if (flood) begin //modo flood, envio sin parar
					 state <= 3'd1; //si modo flood entonjces ir al estado 1 para enviar otro paquete
                tx_fifo_axis_tlast <= 0;//bajar last en el siguiente ciclo
                cont_reg <= 0; //resetear cont_reg
					 //seleccionar la siguiente palabra para ir a estado 1
					 if(rx_random) begin
							tx_fifo_axis_tdata <= random_data;
					 end else if(rx_constante)begin
							tx_fifo_axis_tdata <= tx_axis_tdata_test;
					 end else begin
						  if (word_flag) begin //if word flag send the lsB increase the sequense and reset word flag else send msB and rise word flag
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[7:0];
							tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 16'd1;
							word_flag <= 0;
						  end else begin
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[15:8];
							word_flag <= 1;
						  end 
					 end
				end else if (pkt_n_reg >= pkt_n || send_regs || send_mdio) begin // si se llego a la ultimo paquete bajar valid y regresar a estado 0
                cont_reg <= 0;
					 udp_bit_regs <= 0;
					 send_regs <= 0;
					 send_mdio <= 0;
                pkt_n_reg <= 0;
                ocupado <= 0; //fin ocupado para volver a estado 0 y esperar otro triger
                state <= 3'd0; //volver a estado 0
					 tx_fifo_axis_tdata_reg <= 16'd0;//reset contador data
					 word_flag <= 0;//reset flag
                tx_fifo_axis_tlast <= 0;//bajar last en el siguiente ciclo
                tx_fifo_axis_tvalid <= 0;//bajar tvalid
            end else begin //si no se llego a ultimo paquete elegir un dato para seguir enviando paquetes desde el estado 1
                state <= 3'd1; //si no se llego al numero de mensaje ir al estado 1 para enviar otro paquete
                tx_fifo_axis_tlast <= 0;//bajar last en el siguiente ciclo
                cont_reg <= 0; //resetear cont_reg
					 //seleccionar la siguiente palabra para ir a estado 1
					 if(rx_random) begin
							tx_fifo_axis_tdata <= random_data;
					 end else if(rx_constante)begin
							tx_fifo_axis_tdata <= tx_axis_tdata_test;
					 end else begin
						  if (word_flag) begin //if word flag send the lsB increase the sequense and reset word flag else send msB and rise word flag
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[7:0];
							tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 16'd1;
							word_flag <= 0;
						  end else begin
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg[15:8];
							word_flag <= 1;
						  end 
					 end
            end
        end
    end
end

wire [7:0] reg_fifo_udp_payload_axis_tdata;
wire reg_fifo_udp_payload_axis_tkeep;
wire reg_fifo_udp_payload_axis_tvalid;
wire reg_fifo_udp_payload_axis_tready;
wire reg_fifo_udp_payload_axis_tlast;
wire reg_fifo_udp_payload_axis_tuser;

// Reception ////////////////////////////////////////////////////////////////////////////

//Port Control UDP
wire match_cond_control = rx_udp_dest_port == 55555; // puerto 55555 para control
wire no_match_control = !match_cond_control;
reg match_cond_reg_control = 0;
reg no_match_reg_control = 0;

// Port Loopback UDP
wire match_cond = rx_udp_dest_port == 1234; // solo se escucha el puerto 1234 en el loopback
wire no_match = !match_cond;
reg match_cond_reg = 0;
reg no_match_reg = 0;

always @(posedge clk) begin
    if (rst) begin
        match_cond_reg_control <= 0;
        no_match_reg_control <= 0;
		  match_cond_reg <= 0;
        no_match_reg <= 0;
    end else begin
        if (rx_udp_payload_axis_tvalid) begin
            if ((!match_cond_reg_control && !no_match_reg_control) || (!match_cond_reg && !no_match_reg) ||
                (rx_udp_payload_axis_tvalid && rx_udp_payload_axis_tready && rx_udp_payload_axis_tlast)) begin
                match_cond_reg_control <= match_cond_control;
                no_match_reg_control <= no_match_control;
					 match_cond_reg <= match_cond;
                no_match_reg <= no_match;
            end
        end else begin
				match_cond_reg_control <= 0;
            no_match_reg_control <= 0;
				match_cond_reg <= 0;
            no_match_reg <= 0;
        end
    end
end

assign tx_udp_hdr_valid = (rx_loopb && ~send_regs) ? (rx_udp_hdr_valid && match_cond) : (tx_udp_payload_axis_tvalid && tx_udp_hdr_ready);
assign rx_udp_hdr_ready = (rx_loopb && ~send_regs) ? ((tx_udp_hdr_ready && match_cond) || no_match) : 1'b1;

//assign tx_udp_hdr_valid = rx_udp_hdr_valid && match_cond;
//assign rx_udp_hdr_ready = (tx_eth_hdr_ready && match_cond) || no_match;

assign tx_udp_ip_dscp = 0;
assign tx_udp_ip_ecn = 0;
assign tx_udp_ip_ttl = 64;
assign tx_udp_ip_source_ip = local_ip;

assign tx_udp_ip_dest_ip = (rx_loopb && ~send_regs) ? rx_udp_ip_source_ip : tx_udp_ip_dest_ip_reg;
assign tx_udp_source_port = (rx_loopb && ~send_regs) ? rx_udp_dest_port : tx_udp_source_port_reg;
assign tx_udp_dest_port = (rx_loopb && ~send_regs) ? rx_udp_source_port : tx_udp_dest_port_reg;

//assign tx_udp_ip_dest_ip = rx_udp_ip_source_ip;
//assign tx_udp_source_port = rx_udp_dest_port;
//assign tx_udp_dest_port = rx_udp_source_port;

assign tx_udp_length = send_regs ? (FRAME_BYTES + 16'd8) : (rx_loopb ? rx_udp_length : (n_bytes + 16'd8));
assign tx_udp_checksum = 0;

assign tx_udp_payload_axis_tdata = (rx_loopb && ~send_regs) ? reg_fifo_udp_payload_axis_tdata : tx_fifo_axis_tdata;
assign tx_udp_payload_axis_tvalid = (rx_loopb && ~send_regs) ? reg_fifo_udp_payload_axis_tvalid : tx_fifo_axis_tvalid;
assign tx_fifo_axis_tready = tx_udp_payload_axis_tready;
assign reg_fifo_udp_payload_axis_tready = (rx_loopb && ~send_regs) ? tx_udp_payload_axis_tready : 1'b1;
assign tx_udp_payload_axis_tlast = (rx_loopb && ~send_regs) ? reg_fifo_udp_payload_axis_tlast : tx_fifo_axis_tlast;
assign tx_udp_payload_axis_tuser = (rx_loopb && ~send_regs) ? reg_fifo_udp_payload_axis_tuser : tx_fifo_axis_tuser;

//assign tx_udp_payload_axis_tdata = tx_fifo_udp_payload_axis_tdata;
//assign tx_udp_payload_axis_tvalid = tx_fifo_udp_payload_axis_tvalid;
//assign tx_fifo_udp_payload_axis_tready = tx_udp_payload_axis_tready;
//assign tx_udp_payload_axis_tlast  = tx_fifo_udp_payload_axis_tlast;
//assign tx_udp_payload_axis_tuser = tx_fifo_udp_payload_axis_tuser;

assign rx_fifo_udp_payload_axis_tdata = rx_udp_payload_axis_tdata;
assign rx_fifo_udp_payload_axis_tvalid = rx_udp_payload_axis_tvalid && match_cond_reg;
assign rx_udp_payload_axis_tready = (rx_fifo_udp_payload_axis_tready && match_cond_reg) || no_match_reg;
assign rx_fifo_udp_payload_axis_tlast = rx_udp_payload_axis_tlast;
assign rx_fifo_udp_payload_axis_tuser = rx_udp_payload_axis_tuser;


assign phy0_reset_n = ~rst && ~push[0] && sw[0]; // desactivar phy con sw[0], reset con push[0]

eth_mac_1g_rgmii_fifo #(
    .TARGET(TARGET),
    .USE_CLK90("TRUE"),
    .ENABLE_PADDING(1),
    .MIN_FRAME_LENGTH(64),
    .TX_FIFO_DEPTH(2048),
    .TX_FRAME_FIFO(1),
    .RX_FIFO_DEPTH(2048),
    .RX_FRAME_FIFO(1)
)
eth_mac_inst (
    .gtx_clk(clk),
    .gtx_clk90(clk90),
    .gtx_rst(rst),
    .logic_clk(clk),
    .logic_rst(rst),

    .tx_axis_tdata(tx_axis_tdata),
    .tx_axis_tvalid(tx_axis_tvalid),
    .tx_axis_tready(tx_axis_tready),
    .tx_axis_tlast(tx_axis_tlast),
    .tx_axis_tuser(tx_axis_tuser),

    .rx_axis_tdata(rx_axis_tdata),
    .rx_axis_tvalid(rx_axis_tvalid),
    .rx_axis_tready(rx_axis_tready),
    .rx_axis_tlast(rx_axis_tlast),
    .rx_axis_tuser(rx_axis_tuser),

    .rgmii_rx_clk(phy0_rx_clk),
    .rgmii_rxd(phy0_rxd),
    .rgmii_rx_ctl(phy0_rx_ctl),
    .rgmii_tx_clk(phy0_tx_clk),
    .rgmii_txd(phy0_txd),
    .rgmii_tx_ctl(phy0_tx_ctl),
    
    .tx_fifo_overflow(tx_fifo_overflow),
    .tx_fifo_bad_frame(tx_fifo_bad_frame),
    .tx_fifo_good_frame(tx_fifo_good_frame),
    .rx_error_bad_frame(rx_error_bad_frame),
    .rx_error_bad_fcs(rx_error_bad_fcs),
    .rx_fifo_overflow(rx_fifo_overflow),
    .rx_fifo_bad_frame(rx_fifo_bad_frame),
    .rx_fifo_good_frame(rx_fifo_good_frame),
    .speed(speed),

    .cfg_ifg(8'd12),
    .cfg_tx_enable(1'b1),
    .cfg_rx_enable(1'b1)
);

//ETH status signals
wire tx_fifo_overflow;
wire tx_fifo_bad_frame;
wire tx_fifo_good_frame;
wire rx_error_bad_frame;
wire rx_error_bad_fcs;
wire rx_fifo_overflow;
wire rx_fifo_bad_frame;
wire rx_fifo_good_frame;
wire eth_rx_error_header_early_termination;

//UDP, IP, ARP status, signals
wire ip_rx_error_header_early_termination;
wire ip_rx_error_payload_early_termination;
wire ip_rx_error_invalid_header;
wire ip_rx_error_invalid_checksum;
wire ip_tx_error_payload_early_termination;
wire ip_tx_error_arp_failed;
wire udp_rx_error_header_early_termination;
wire udp_rx_error_payload_early_termination;
wire udp_tx_error_payload_early_termination;

//contadores eth 304b 38Bytes
reg [31:0] tx_fifo_overflow_reg; 
reg [31:0] tx_fifo_bad_frame_reg;
reg [39:0] tx_fifo_good_frame_reg;
reg [31:0] rx_error_bad_frame_reg;
reg [31:0] rx_error_bad_fcs_reg;
reg [31:0] rx_fifo_overflow_reg;
reg [31:0] rx_fifo_bad_frame_reg;
reg [39:0] rx_fifo_good_frame_reg;
reg [31:0] eth_rx_error_header_early_termination_reg;

//contadores udp, ip, arp //288b 36Bytes
reg [31:0] ip_rx_error_header_early_termination_reg;
reg [31:0] ip_rx_error_payload_early_termination_reg;
reg [31:0] ip_rx_error_invalid_header_reg;
reg [31:0] ip_rx_error_invalid_checksum_reg;
reg [31:0] ip_tx_error_payload_early_termination_reg;
reg [31:0] ip_tx_error_arp_failed_reg;
reg [31:0] udp_rx_error_header_early_termination_reg;
reg [31:0] udp_rx_error_payload_early_termination_reg;
reg [31:0] udp_tx_error_payload_early_termination_reg;

wire [1:0] speed;

// 74Bytes for counters 592bits, 2bits for speed, 

always @(posedge clk) begin
    if (rst) begin
		  tx_fifo_overflow_reg <= 0;
		  tx_fifo_bad_frame_reg <= 0;
		  tx_fifo_good_frame_reg <= 0;
		  rx_error_bad_frame_reg <= 0;
		  rx_error_bad_fcs_reg <= 0;
		  rx_fifo_overflow_reg <= 0;
		  rx_fifo_bad_frame_reg <= 0;
		  rx_fifo_good_frame_reg <= 0;
		  eth_rx_error_header_early_termination_reg <= 0;
		  
		  ip_rx_error_header_early_termination_reg <= 0;
		  ip_rx_error_payload_early_termination_reg <= 0;
		  ip_rx_error_invalid_header_reg <= 0;
		  ip_rx_error_invalid_checksum_reg <= 0;
		  ip_tx_error_payload_early_termination_reg <= 0;
		  ip_tx_error_arp_failed_reg <= 0;
		  udp_rx_error_header_early_termination_reg <= 0;
		  udp_rx_error_payload_early_termination_reg <= 0;
		  udp_tx_error_payload_early_termination_reg <= 0;
		  
    end else begin
        if (tx_fifo_overflow) begin 
				tx_fifo_overflow_reg <= tx_fifo_overflow_reg + 1;
			end
			
			if (tx_fifo_bad_frame) begin
				tx_fifo_bad_frame_reg <= tx_fifo_bad_frame_reg + 1;
			end
			
			if (tx_fifo_good_frame) begin
				tx_fifo_good_frame_reg <= tx_fifo_good_frame_reg + 1;
			end
			
			if (rx_error_bad_frame) begin
				rx_error_bad_frame_reg <= rx_error_bad_frame_reg + 1;
			end
			
			if (rx_error_bad_fcs) begin
				rx_error_bad_fcs_reg <= rx_error_bad_fcs_reg + 1;
			end
			
			if (rx_fifo_overflow) begin
				rx_fifo_overflow_reg <= rx_fifo_overflow_reg + 1;
			end
			
			if (rx_fifo_bad_frame) begin
				rx_fifo_bad_frame_reg <= rx_fifo_bad_frame_reg + 1;
			end
			
			if (rx_fifo_good_frame) begin
				rx_fifo_good_frame_reg <= rx_fifo_good_frame_reg + 1;
			end
			
			if (eth_rx_error_header_early_termination) begin
				eth_rx_error_header_early_termination_reg <= eth_rx_error_header_early_termination_reg + 1;
			end
        if (ip_rx_error_header_early_termination) begin 
				ip_rx_error_header_early_termination_reg <= ip_rx_error_header_early_termination_reg + 1;
			end
			
			if (ip_rx_error_payload_early_termination) begin
				ip_rx_error_payload_early_termination_reg <= ip_rx_error_payload_early_termination_reg + 1;
			end
			
			if (ip_rx_error_invalid_header) begin
				ip_rx_error_invalid_header_reg <= ip_rx_error_invalid_header_reg + 1;
			end
			
			if (ip_rx_error_invalid_checksum) begin
				ip_rx_error_invalid_checksum_reg <= ip_rx_error_invalid_checksum_reg + 1;
			end
			
			if (ip_tx_error_payload_early_termination) begin
				ip_tx_error_payload_early_termination_reg <= ip_tx_error_payload_early_termination_reg + 1;
			end
			
			if (ip_tx_error_arp_failed) begin
				ip_tx_error_arp_failed_reg <= ip_tx_error_arp_failed_reg + 1;
			end
			
			if (udp_rx_error_header_early_termination) begin
				udp_rx_error_header_early_termination_reg <= udp_rx_error_header_early_termination_reg + 1;
			end
			
			if (udp_rx_error_payload_early_termination) begin
				udp_rx_error_payload_early_termination_reg <= udp_rx_error_payload_early_termination_reg + 1;
			end
			
			if (udp_tx_error_payload_early_termination) begin
				udp_tx_error_payload_early_termination_reg <= udp_tx_error_payload_early_termination_reg + 1;
			end
    end
end

////////////////////////////////////////////////
eth_axis_rx
eth_axis_rx_inst (
    .clk(clk),
    .rst(rst),
    // AXI input
    .s_axis_tdata(rx_axis_tdata),
    .s_axis_tvalid(rx_axis_tvalid),
    .s_axis_tready(rx_axis_tready),
    .s_axis_tlast(rx_axis_tlast),
    .s_axis_tuser(rx_axis_tuser),
    // Ethernet frame output
    .m_eth_hdr_valid(rx_eth_hdr_valid),
    .m_eth_hdr_ready(rx_eth_hdr_ready),
    .m_eth_dest_mac(rx_eth_dest_mac),
    .m_eth_src_mac(rx_eth_src_mac),
    .m_eth_type(rx_eth_type),
    .m_eth_payload_axis_tdata(rx_eth_payload_axis_tdata),
    .m_eth_payload_axis_tvalid(rx_eth_payload_axis_tvalid),
    .m_eth_payload_axis_tready(rx_eth_payload_axis_tready),
    .m_eth_payload_axis_tlast(rx_eth_payload_axis_tlast),
    .m_eth_payload_axis_tuser(rx_eth_payload_axis_tuser),
    // Status signals
    .busy(),
    .error_header_early_termination(eth_rx_error_header_early_termination)
);


eth_axis_tx
eth_axis_tx_inst (
    .clk(clk),
    .rst(rst),
    // Ethernet frame input
    .s_eth_hdr_valid(tx_eth_hdr_valid),
    .s_eth_hdr_ready(tx_eth_hdr_ready),
    .s_eth_dest_mac(tx_eth_dest_mac),
    .s_eth_src_mac(tx_eth_src_mac),
    .s_eth_type(tx_eth_type),
    .s_eth_payload_axis_tdata(tx_eth_payload_axis_tdata),
    .s_eth_payload_axis_tvalid(tx_eth_payload_axis_tvalid),
    .s_eth_payload_axis_tready(tx_eth_payload_axis_tready),
    .s_eth_payload_axis_tlast(tx_eth_payload_axis_tlast),
    .s_eth_payload_axis_tuser(tx_eth_payload_axis_tuser),
    // AXI output
    .m_axis_tdata(tx_axis_tdata),
    .m_axis_tvalid(tx_axis_tvalid),
    .m_axis_tready(tx_axis_tready),
    .m_axis_tlast(tx_axis_tlast),
    .m_axis_tuser(tx_axis_tuser),
    // Status signals
    .busy()
);

udp_complete
udp_complete_inst (
    .clk(clk),
    .rst(rst),
    // Ethernet frame input
    .s_eth_hdr_valid(rx_eth_hdr_valid),
    .s_eth_hdr_ready(rx_eth_hdr_ready),
    .s_eth_dest_mac(rx_eth_dest_mac),
    .s_eth_src_mac(rx_eth_src_mac),
    .s_eth_type(rx_eth_type),
    .s_eth_payload_axis_tdata(rx_eth_payload_axis_tdata),
    .s_eth_payload_axis_tvalid(rx_eth_payload_axis_tvalid),
    .s_eth_payload_axis_tready(rx_eth_payload_axis_tready),
    .s_eth_payload_axis_tlast(rx_eth_payload_axis_tlast),
    .s_eth_payload_axis_tuser(rx_eth_payload_axis_tuser),
    // Ethernet frame output
    .m_eth_hdr_valid(tx_eth_hdr_valid),
    .m_eth_hdr_ready(tx_eth_hdr_ready),
    .m_eth_dest_mac(tx_eth_dest_mac),
    .m_eth_src_mac(tx_eth_src_mac),
    .m_eth_type(tx_eth_type),
    .m_eth_payload_axis_tdata(tx_eth_payload_axis_tdata),
    .m_eth_payload_axis_tvalid(tx_eth_payload_axis_tvalid),
    .m_eth_payload_axis_tready(tx_eth_payload_axis_tready),
    .m_eth_payload_axis_tlast(tx_eth_payload_axis_tlast),
    .m_eth_payload_axis_tuser(tx_eth_payload_axis_tuser),
    // IP frame input
    .s_ip_hdr_valid(tx_ip_hdr_valid),
    .s_ip_hdr_ready(tx_ip_hdr_ready),
    .s_ip_dscp(tx_ip_dscp),
    .s_ip_ecn(tx_ip_ecn),
    .s_ip_length(tx_ip_length),
    .s_ip_ttl(tx_ip_ttl),
    .s_ip_protocol(tx_ip_protocol),
    .s_ip_source_ip(tx_ip_source_ip),
    .s_ip_dest_ip(tx_ip_dest_ip),
    .s_ip_payload_axis_tdata(tx_ip_payload_axis_tdata),
    .s_ip_payload_axis_tvalid(tx_ip_payload_axis_tvalid),
    .s_ip_payload_axis_tready(tx_ip_payload_axis_tready),
    .s_ip_payload_axis_tlast(tx_ip_payload_axis_tlast),
    .s_ip_payload_axis_tuser(tx_ip_payload_axis_tuser),
    // IP frame output
    .m_ip_hdr_valid(rx_ip_hdr_valid),
    .m_ip_hdr_ready(rx_ip_hdr_ready),
    .m_ip_eth_dest_mac(rx_ip_eth_dest_mac),
    .m_ip_eth_src_mac(rx_ip_eth_src_mac),
    .m_ip_eth_type(rx_ip_eth_type),
    .m_ip_version(rx_ip_version),
    .m_ip_ihl(rx_ip_ihl),
    .m_ip_dscp(rx_ip_dscp),
    .m_ip_ecn(rx_ip_ecn),
    .m_ip_length(rx_ip_length),
    .m_ip_identification(rx_ip_identification),
    .m_ip_flags(rx_ip_flags),
    .m_ip_fragment_offset(rx_ip_fragment_offset),
    .m_ip_ttl(rx_ip_ttl),
    .m_ip_protocol(rx_ip_protocol),
    .m_ip_header_checksum(rx_ip_header_checksum),
    .m_ip_source_ip(rx_ip_source_ip),
    .m_ip_dest_ip(rx_ip_dest_ip),
    .m_ip_payload_axis_tdata(rx_ip_payload_axis_tdata),
    .m_ip_payload_axis_tvalid(rx_ip_payload_axis_tvalid),
    .m_ip_payload_axis_tready(rx_ip_payload_axis_tready),
    .m_ip_payload_axis_tlast(rx_ip_payload_axis_tlast),
    .m_ip_payload_axis_tuser(rx_ip_payload_axis_tuser),
    // UDP frame input
    .s_udp_hdr_valid(tx_udp_hdr_valid),
    .s_udp_hdr_ready(tx_udp_hdr_ready),
    .s_udp_ip_dscp(tx_udp_ip_dscp),
    .s_udp_ip_ecn(tx_udp_ip_ecn),
    .s_udp_ip_ttl(tx_udp_ip_ttl),
    .s_udp_ip_source_ip(local_ip),
    .s_udp_ip_dest_ip(tx_udp_ip_dest_ip),
    .s_udp_source_port(tx_udp_source_port),
    .s_udp_dest_port(tx_udp_dest_port),
    .s_udp_length(tx_udp_length),
    .s_udp_checksum(tx_udp_checksum),
    .s_udp_payload_axis_tdata(tx_udp_payload_axis_tdata),
    .s_udp_payload_axis_tvalid(tx_udp_payload_axis_tvalid),
    .s_udp_payload_axis_tready(tx_udp_payload_axis_tready),
    .s_udp_payload_axis_tlast(tx_udp_payload_axis_tlast),
    .s_udp_payload_axis_tuser(tx_udp_payload_axis_tuser),
    // UDP frame output
    .m_udp_hdr_valid(rx_udp_hdr_valid),
    .m_udp_hdr_ready(rx_udp_hdr_ready),
    .m_udp_eth_dest_mac(rx_udp_eth_dest_mac),
    .m_udp_eth_src_mac(rx_udp_eth_src_mac),
    .m_udp_eth_type(rx_udp_eth_type),
    .m_udp_ip_version(rx_udp_ip_version),
    .m_udp_ip_ihl(rx_udp_ip_ihl),
    .m_udp_ip_dscp(rx_udp_ip_dscp),
    .m_udp_ip_ecn(rx_udp_ip_ecn),
    .m_udp_ip_length(rx_udp_ip_length),
    .m_udp_ip_identification(rx_udp_ip_identification),
    .m_udp_ip_flags(rx_udp_ip_flags),
    .m_udp_ip_fragment_offset(rx_udp_ip_fragment_offset),
    .m_udp_ip_ttl(rx_udp_ip_ttl),
    .m_udp_ip_protocol(rx_udp_ip_protocol),
    .m_udp_ip_header_checksum(rx_udp_ip_header_checksum),
    .m_udp_ip_source_ip(rx_udp_ip_source_ip),
    .m_udp_ip_dest_ip(rx_udp_ip_dest_ip),
    .m_udp_source_port(rx_udp_source_port),
    .m_udp_dest_port(rx_udp_dest_port),
    .m_udp_length(rx_udp_length),
    .m_udp_checksum(rx_udp_checksum),
    .m_udp_payload_axis_tdata(rx_udp_payload_axis_tdata),
    .m_udp_payload_axis_tvalid(rx_udp_payload_axis_tvalid),
    .m_udp_payload_axis_tready(rx_udp_payload_axis_tready),
    .m_udp_payload_axis_tlast(rx_udp_payload_axis_tlast),
    .m_udp_payload_axis_tuser(rx_udp_payload_axis_tuser),
    // Status signals
    .ip_rx_busy(),
    .ip_tx_busy(),
    .udp_rx_busy(),
    .udp_tx_busy(),
    .ip_rx_error_header_early_termination(ip_rx_error_header_early_termination),
    .ip_rx_error_payload_early_termination(ip_rx_error_payload_early_termination),
    .ip_rx_error_invalid_header(ip_rx_error_invalid_header),
    .ip_rx_error_invalid_checksum(ip_rx_error_invalid_checksum),
    .ip_tx_error_payload_early_termination(ip_tx_error_payload_early_termination),
    .ip_tx_error_arp_failed(ip_tx_error_arp_failed),
    .udp_rx_error_header_early_termination(udp_rx_error_header_early_termination),
    .udp_rx_error_payload_early_termination(udp_rx_error_payload_early_termination),
    .udp_tx_error_payload_early_termination(udp_tx_error_payload_early_termination),
    // Configuration
    .local_mac(local_mac),
    .local_ip(local_ip),
    .gateway_ip(gateway_ip),
    .subnet_mask(subnet_mask),
    .clear_arp_cache(0)
);

axis_fifo #(
    .DEPTH(2048),
    .DATA_WIDTH(8),
    .KEEP_ENABLE(0),
    .ID_ENABLE(0),
    .DEST_ENABLE(0),
    .USER_ENABLE(1),
    .USER_WIDTH(1),
    .FRAME_FIFO(1)
)
udp_payload_fifo (
    .clk(clk),
    .rst(rst),

    // AXI input
    .s_axis_tdata(rx_fifo_udp_payload_axis_tdata),
    .s_axis_tkeep(0),
    .s_axis_tvalid(rx_fifo_udp_payload_axis_tvalid),
    .s_axis_tready(rx_fifo_udp_payload_axis_tready),
    .s_axis_tlast(rx_fifo_udp_payload_axis_tlast),
    .s_axis_tid(0),
    .s_axis_tdest(0),
    .s_axis_tuser(rx_fifo_udp_payload_axis_tuser),

    // AXI output
    .m_axis_tdata(reg_fifo_udp_payload_axis_tdata),
    .m_axis_tkeep(),
    .m_axis_tvalid(reg_fifo_udp_payload_axis_tvalid),
    .m_axis_tready(reg_fifo_udp_payload_axis_tready),
    .m_axis_tlast(reg_fifo_udp_payload_axis_tlast),
    .m_axis_tid(),
    .m_axis_tdest(),
    .m_axis_tuser(reg_fifo_udp_payload_axis_tuser),

    // Status
    .status_overflow(),
    .status_bad_frame(),
    .status_good_frame()
);

//LED RUN STATUS////////////////////////////////////////////////////////////

assign led[0] = ~rst && sw[1]; //reset_n global encendido cuando run
assign led[1] = phy0_reset_n && sw[1]; //reset_n phy encendido cuando run
assign led[2] = CLK_125MHZ && sw[2];
assign led[3] = ~phy0_int_n && sw[3];
assign led[4] = (rx_loopb && ~send_regs) && sw[4]; //decarctivar indicador con sw
assign led[5] = (rx_random || rx_constante) && sw[5];
assign led[6]= ocupado && sw[6]; //desactivar indicador con sw
assign led[7]= mdio_busy && sw[7];

//UART/////////////////////////////////////////////////////////
wire rx_busy;
wire tx_busy;

uart
uart_inst(
	  .clk(clk),
	  .reset_n(rst || push[1]),
	  .tx_ena(tx_ena),
	  .tx_data(tx_data),
	  .rx(rxd),
	  .rx_busy(rx_busy),
	  .rx_error(),
	  .rx_data(rx_data_s),
	  .tx_busy(tx_busy),
	  .tx(txd)
);
///////UART RX////////////////////////////////////////////////////
wire [7:0] rx_data_s;
reg [1:0] state_uart = 2'd0;
reg [7:0] rx_data_s_reg;
reg rx_valid; // pulso para leer rx data
//valid rx fsm------------------
always @(posedge clk) begin
    if (rst) begin
        rx_valid <= 0;
		  state_uart <= 2'd0;
		  rx_data_s_reg <= 8'd0;
    end else begin
			//estado 0: esperando rx busy
        if (state_uart == 2'd0) begin 
				rx_data_s_reg <= rx_data_s_reg;
				if (rx_busy) begin
					state_uart <= 2'd1; //pasando a estado 1 cuando rx_busy suba
				end
        end
			//estado 1: esperando a que baje rx_busy
		  else if (state_uart == 2'd1) begin
				rx_data_s_reg <= rx_data_s_reg;
				if (~rx_busy) begin
					rx_valid <= 1; //subir valid cuando rx_busy baje
					rx_data_s_reg <= rx_data_s;
					state_uart <= 2'd2; // pasar a estado 2
				end
        end 
		  else begin
				rx_data_s_reg <= rx_data_s_reg;
				rx_valid <= 0; //bajar valid 
				state_uart <= 2'd0; // volver a estado 0 a esperar otro rx_busy
		  end
    end
end

//uart buffer 8 bytes------------------------
reg [63:0] rx_uart_buff;
reg [3:0] nbyte_buff;
always @(posedge clk) begin
    if (rst) begin
        rx_uart_buff <= 64'd0;
		  nbyte_buff <= 4'd0;
    end else begin
			//esperando valid registrar hasta 8 Bytes y borrar
        if (rx_valid) begin 
				rx_uart_buff <= {rx_uart_buff[55:0],rx_data_s_reg};
				nbyte_buff <= nbyte_buff + 4'd1;
			end else if (nbyte_buff == 4'd8) begin
				rx_uart_buff <= 64'd0;
				nbyte_buff <= 4'd0;
			end else begin
				nbyte_buff <= nbyte_buff;
				rx_uart_buff <= rx_uart_buff;
			end
    end
end

//udp buffer 8 bytes
reg [63:0] rx_udp_buff = 64'd0;
reg rx_udp_cmd = 0;

always @ (posedge clk) begin
	if (rst) begin
	rx_udp_buff <= 64'd0;
	rx_udp_cmd <= 0;
	end else begin
		if (rx_udp_payload_axis_tvalid && match_cond_reg_control) begin
			rx_udp_cmd <= 1;
			rx_udp_buff <= {rx_udp_buff[55:0],rx_udp_payload_axis_tdata};
		end else begin
			rx_udp_cmd <= 0;
			rx_udp_buff <= 64'd0;
		end	
	end
end


////////////////////////////////////////////////////////////
reg flood;
reg rx_loopb;
reg rx_trigger;
reg rx_random;
reg rx_constante;

//5 bits for mode trasimtion

reg mdio_op;
reg [4:0] mdio_phy;
reg [4:0] mdio_reg;
reg [15:0] mdio_wdata;
reg mdio_start;


reg [15:0] n_bytes; 
reg [31:0] pkt_n;
//48 bits for trasmition configurarion


// Configuration
reg [47:0] local_mac = 48'h66_70_67_61_3A_30; //direccion fisica de la fpga "fpga:0"

reg [31:0] local_ip;
reg [31:0] gateway_ip;
reg [31:0] subnet_mask;

reg [31:0] tx_udp_ip_dest_ip_reg;
reg [15:0] tx_udp_source_port_reg;
reg [15:0] tx_udp_dest_port_reg;

//208 bits for network config

reg trigger_send;

always @(posedge clk) begin
    if (rst) begin
        flood <= 0;
		  rx_loopb <= 0;
		  rx_trigger <= 0;
		  rx_random <= 0;
		  rx_constante <= 0;
		  
		  mdio_op <= 1; //default read
		  mdio_phy <= 5'b00111; // default 7
		  mdio_reg <= 5'd0; // default 0
		  mdio_wdata <= 16'd0;
		  mdio_start <= 0;
		  
		  n_bytes <= 16'd1440;  //1440 bytes por paquete default;
		  pkt_n <= 32'd1;//por defecto 1 mensaje
		  
		  gateway_ip  <= {8'd192, 8'd168, 8'd1,   8'd1};
		  local_ip    <= {8'd192, 8'd168, 8'd1,   8'd12};
		  tx_udp_ip_dest_ip_reg <= {8'd192, 8'd168, 8'd1,   8'd11};
		  
        subnet_mask <= {8'd255, 8'd255, 8'd255, 8'd0};
        tx_udp_source_port_reg <= 16'd1234; //puerto por defecto para envio, source, desde la fpga
        tx_udp_dest_port_reg <= 16'd9999; //puerto por defecto para envio, destination hacia la pc
		  
		  trigger_send  <= 0;
		  
    end else begin
			//UDP CONTROL/////////////////////////////
        if ((rx_uart_buff == "...flood") || (rx_udp_buff == "...flood")) begin //"...flood"
				flood <= ~flood;
        end else if ((rx_uart_buff == "loopback") || (rx_udp_buff == "loopback")) begin //"loopback"
				rx_loopb <= ~rx_loopb;
		  end else if ((rx_uart_buff == ".trigger") || (rx_udp_buff == ".trigger")) begin //".trigger"
				rx_trigger <= 1;
		  end else if ((rx_uart_buff == "..random") || (rx_udp_buff == "..random")) begin //"..random"
				rx_random <= ~rx_random;
		  end else if ((rx_uart_buff == "constant") || (rx_udp_buff == "constant")) begin //"constant"
				rx_constante <= ~rx_constante;
				// PHY CONTROLLER/*------------------*//
		  end else if ((rx_uart_buff == "..mdio_r") || (rx_udp_buff == "..mdio_r")) begin //"..mdio_r"
				mdio_op <= 1;
		  end else if ((rx_uart_buff == "..mdio_w") || (rx_udp_buff == "..mdio_w")) begin //"..mdio_w"
				mdio_op <= 0;
		  end else if ((rx_uart_buff[63:8] == "phyaddr") || (rx_udp_buff[63:8] == "phyaddr")) begin //"phyaddr"8'bXXXAAAAA
				mdio_phy <= rx_udp_cmd ? rx_udp_buff[4:0] : rx_uart_buff[4:0];
		  end else if ((rx_uart_buff[63:8] == "regaddr") || (rx_udp_buff[63:8] == "regaddr")) begin //"regaddr"8'bXXXRRRRR
				mdio_reg <= rx_udp_cmd ? rx_udp_buff[4:0] : rx_uart_buff[4:0];
		  end else if ((rx_uart_buff[63:16] == "mdio_d") || (rx_udp_buff[63:16] == "mdio_d")) begin //"mdio_d"16'hDDDD
				mdio_wdata <= rx_udp_cmd ? rx_udp_buff[15:0] : rx_uart_buff[15:0];
		  end else if ((rx_uart_buff == "mdio_sta") || (rx_udp_buff == "mdio_sta")) begin //"mdio_sta"
				mdio_start <= 1;
				// UDP Mesagge configurations/*------------------*/
		  end else if ((rx_uart_buff[63:16] == "udpmtu") || (rx_udp_buff[63:16] == "udpmtu")) begin //"udpmtu"16'hBBBB
				n_bytes <= rx_udp_cmd ? rx_udp_buff[15:0] : rx_uart_buff[15:0];
		  end else if ((rx_uart_buff[63:32] == "pktn") || (rx_udp_buff[63:32] == "pktn")) begin //"pktn"32'hPPPPPPPP
				pkt_n <= rx_udp_cmd ? rx_udp_buff[31:0] : rx_uart_buff[31:0];
		  // ip configuration/*------------------*
		  end else if ((rx_uart_buff[63:32] == "ip_g") || (rx_udp_buff[63:32] == "ip_g")) begin //"ip_g"32'hIIIIIIII
		      gateway_ip <= rx_udp_cmd ? rx_udp_buff[31:0] : rx_uart_buff[31:0];
		  end else if ((rx_uart_buff[63:32] == "ip_s") || (rx_udp_buff[63:32] == "ip_s")) begin //"ip_s"32'hIIIIIIII
		      local_ip <= rx_udp_cmd ? rx_udp_buff[31:0] : rx_uart_buff[31:0];
		  end else if ((rx_uart_buff[63:32] == "ip_d") || (rx_udp_buff[63:32] == "ip_d")) begin //"ip_d"32'hIIIIIIII
		      tx_udp_ip_dest_ip_reg <= rx_udp_cmd ? rx_udp_buff[31:0] : rx_uart_buff[31:0];
		  end else if ((rx_uart_buff[63:32] == "subm") || (rx_udp_buff[63:32] == "subm")) begin //"subm"32'hMMMMMMMM
		      subnet_mask <= rx_udp_cmd ? rx_udp_buff[31:0] : rx_uart_buff[31:0];
	     end else if ((rx_uart_buff[63:16] == "srport") || (rx_udp_buff[63:16] == "srport")) begin //"srport"16'hPPPP
		      tx_udp_source_port_reg <= rx_udp_cmd ? rx_udp_buff[15:0] : rx_uart_buff[15:0];
		  end else if ((rx_uart_buff[63:16] == "dsport") || (rx_udp_buff[63:16] == "dsport")) begin //"dsport"16'hPPPP
		      tx_udp_dest_port_reg <= rx_udp_cmd ? rx_udp_buff[15:0] : rx_uart_buff[15:0];
		   // uart register log/*------------------*
		  end else if ((rx_uart_buff[63:0] == "regstats") ||(rx_udp_buff[63:0] == "regstats") ) begin //"regstats" pulse for log registers
		      trigger_send <= 1;
		  end else begin
				flood <= flood;
				rx_loopb <= rx_loopb;
				rx_trigger <= 0;
				rx_random <= rx_random;
				
				mdio_op <= mdio_op;
				mdio_phy <= mdio_phy;
				mdio_reg <= mdio_reg;
				mdio_wdata <= mdio_wdata;
				mdio_start <= 0;
				
				n_bytes <= n_bytes;
				pkt_n <= pkt_n;
				
			  gateway_ip  <= gateway_ip;
			  local_ip    <= local_ip;
			  tx_udp_ip_dest_ip_reg <= tx_udp_ip_dest_ip_reg;
			  
			  subnet_mask <= subnet_mask;
			  tx_udp_source_port_reg <= tx_udp_source_port_reg;
			  tx_udp_dest_port_reg <= tx_udp_dest_port_reg;
			  
			  trigger_send <= 0;

		  end
    end
end

//MDIO CONTROLLER//////////////////////////////////////////////////////////
wire mdio_busy;

mdio_controller
mdio_controller_inst(
    // System Signals
    .clk(clk),
    .rst_n(~rst && ~push[1]),

    // User Interface - Inputs
    .start(mdio_start),      // Start transaction
    .rw(mdio_op),         // 1 for read, 0 for write
    .phy_addr(mdio_phy),   // PHY Address 5b "00AAA"
    .reg_addr(mdio_reg),   // Register Address 5b "RRRRR"
    .wdata(mdio_wdata),      // Data to write 16b

    // User Interface - Outputs
    .rdata(mdio_rdata),      // Data read from PHY 16b
    .busy(mdio_busy),       // Controller is busy
    .rvalid(mdio_rvalid),     // Read data is valid

    // PHY Interface
    .mdc(MDC),        // MDIO Clock
    .mdio(MDIO)        // MDIO Data
);

//SEND READ DATA REGISTERS//////////////////////////////////////
wire [15:0] mdio_rdata;
reg [15:0] mdio_rdata_reg;
wire mdio_rvalid;
reg mdio_read_ready;

always @(posedge clk) begin
    if (rst) begin
        mdio_rdata_reg <= 16'd0;
		  mdio_read_ready <= 0;
    end else begin
        if (mdio_rvalid) begin //si mdio valid
				mdio_rdata_reg <= mdio_rdata; //guardar registro
				mdio_read_ready <= 1;
		  end else begin
				mdio_rdata_reg <= mdio_rdata_reg;
				mdio_read_ready <= 0;
		  end
    end
end

//UART TX////////////////////////////////////
reg tx_ena;
reg [7:0] tx_data;
reg [2:0] state_uart_tx = 3'd0;

reg [6:0] tx_byte_count; // Contador para saber cuántos bytes llevamos (hasta 115)

always @(posedge clk) begin
    if (rst) begin
		  tx_ena <= 0;
		  tx_data <= 8'd0;
		  state_uart_tx <= 3'd0;
    end else begin
			//estado 0: esperando mdio_read_ready
        if (state_uart_tx == 3'd0) begin
				if (mdio_read_ready) begin
					tx_data <= mdio_rdata_reg[15:8];
					tx_ena <= 1;
					state_uart_tx <= 3'd1;
				end else if(trigger_send) begin
					state_uart_tx <= 3'd4;
				end
        end
			//estado 1
		  else if (state_uart_tx == 3'd1) begin
				tx_ena <= 0;
				state_uart_tx <= 3'd2; // pasar a estado 2
        end 
		  //estado 2: esperando a que se envie primero 8 bits
		  else if (state_uart_tx == 3'd2) begin
				if (~tx_busy) begin
					tx_data <= mdio_rdata_reg[7:0];
					tx_ena <= 1;
					state_uart_tx <= 3'd3; // pasar a estado 3
				end
		  end
		  //estado 3: esperar a que se envie segunda palabra para volver a estado 0
		  else if (state_uart_tx == 3'd3) begin
				tx_ena <= 0; 
				if (~tx_busy) begin
				state_uart_tx <= 3'd0; // pasar a estado 0
				end
		  // estado 4: Inicializar contador.
		  end else if (state_uart_tx == 3'd4) begin
            tx_byte_count <= 115; // Total de bytes a enviar (920 bits / 8)
            state_uart_tx <= 3'd5;
        end
		  // estado 5: Iniciar transmisión del byte actual.
		  else if (state_uart_tx == 3'd5) begin
            // Tomamos siempre los 8 bits de la extrema izquierda
            tx_data <= full_registro[ (tx_byte_count * 8) - 1 -: 8 ];
            tx_ena <= 1;
				if(tx_busy) begin // esperando al que el tx_busy suba
					state_uart_tx <= 3'd6;
				end
        end
		  // ESTADO 6: Esperar a que el UART envíe y recorrer
		  else if (state_uart_tx == 3'd6) begin
            tx_ena <= 0;
            // Esperar a que tx_busy baje (UART terminó)
				if (~tx_busy) begin
                tx_byte_count <= tx_byte_count - 1;
                
                // Si aún quedan bytes, recorremos el registro y repetimos
                if (tx_byte_count > 1) begin
                    state_uart_tx <= 3'd5; // Regresa al estado 5 para el siguiente byte
                end else begin
                    // Ya terminamos, volvemos al inicio
                    state_uart_tx <= 3'd0;
					 end
            end
        end
    end
end

// 115 Bytes en total = 920 Bits
parameter FRAME_BITS = 920;
parameter FRAME_BYTES = FRAME_BITS/8; 
reg [FRAME_BITS-1:0] full_registro;
reg [31:0] start_frame = 32'hAA_55_AA_55;
reg [31:0] end_frame = 32'hEE_FF_EE_FF;
reg full_reg_flag;

always @(posedge clk) begin
    if (rst) begin
		  full_registro <= 920'd0;
		  full_reg_flag <= 0;
    end else begin
        if (trigger_send) begin
			 full_registro <= {
			 // 1. CABECERA (4 Bytes)
			 start_frame,
			 
			 // 2. CONTADORES ETH MAC (38 Bytes / 304 bits)
			 tx_fifo_overflow_reg,
			 tx_fifo_bad_frame_reg,
			 tx_fifo_good_frame_reg,
			 rx_error_bad_frame_reg,
			 rx_error_bad_fcs_reg,
			 rx_fifo_overflow_reg,
			 rx_fifo_bad_frame_reg,
			 rx_fifo_good_frame_reg,
			 eth_rx_error_header_early_termination_reg,
			 
			 // 3. CONTADORES UDP/IP/ARP (36 Bytes / 288 bits)
			 ip_rx_error_header_early_termination_reg,
			 ip_rx_error_payload_early_termination_reg,
			 ip_rx_error_invalid_header_reg,
			 ip_rx_error_invalid_checksum_reg,
			 ip_tx_error_payload_early_termination_reg,
			 ip_tx_error_arp_failed_reg,
			 udp_rx_error_header_early_termination_reg,
			 udp_rx_error_payload_early_termination_reg,
			 udp_tx_error_payload_early_termination_reg,
			 
			 // 4. MODO Y BANDERAS (Acomodados en 1 Byte / 8 bits)
			 // Juntamos todo rellenando con un '0' al principio para cuadrar los 8 bits
			 {1'b0, speed, flood, rx_loopb, ocupado, rx_random, rx_constante},

			 // 5. CONFIGURACIÓN DE TRANSMISIÓN (6 Bytes / 48 bits)
			 n_bytes,
			 pkt_n,

			 // 6. CONFIGURACIÓN DE RED (26 Bytes / 208 bits)
			 local_mac,
			 local_ip,
			 gateway_ip,
			 subnet_mask,tx_udp_ip_dest_ip_reg,
			 tx_udp_source_port_reg,
			 tx_udp_dest_port_reg,

			 // 7. PIE DE TRAMA / FOOTER (4 Bytes) - Indica el final del mensaje
			 end_frame};
			 full_reg_flag <= 1;
        end else begin
			 full_registro <= full_registro;
			 full_reg_flag <= 0;
        end 
    end
end

endmodule
`resetall
