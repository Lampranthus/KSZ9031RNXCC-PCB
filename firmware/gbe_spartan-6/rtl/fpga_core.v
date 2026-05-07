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
reg [7:0] tx_fifo_axis_tdata_reg;
reg [7:0] tx_axis_tdata_test = 8'h58; //"X"
reg tx_fifo_axis_tvalid;
wire tx_fifo_axis_tready;
reg tx_fifo_axis_tlast;
reg tx_fifo_axis_tuser = 0; 
reg [31:0] pkt_n_reg;
reg [2:0] state;
reg ocupado;

reg [7:0] random_data;
// Linear-feedback shift register
reg [7:0] lfsr;

wire feedback;

// Feedback
assign feedback = lfsr[7] ^ lfsr[5] ^ lfsr[4] ^ lfsr[3];

// maquina de estados para trasnmision 
always @(posedge clk) begin

    if (rst) begin
        lfsr <= 8'hAB; // Semilla inicial (no todos deben ser ceros)
    end else begin
        // Generar nuevo valor cada ciclo de reloj
        lfsr[7:0] <= {lfsr[6:0], feedback};
        random_data <= lfsr;
    end

    if (rst) begin
        state <=  3'd0;
        tx_fifo_axis_tdata <= 8'd0;
        tx_fifo_axis_tdata_reg <= 8'd0;
        tx_fifo_axis_tvalid <= 0;
        cont_reg <= 16'd0;
        tx_fifo_axis_tlast <= 0;
        pkt_n_reg <= 32'd0;
        ocupado <= 0;
		  
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
                    tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg;
                    tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 8'd1;
                end
            end
        end 
        // Estado 1: Enviando primera palabra del mensaje
        else if (state == 3'd1) begin
 
            if (tx_fifo_axis_tready) begin
                state <= 3'd2;
                // Primer dato aceptado y ligiendo segunda palabra
                if(rx_random) begin
                    tx_fifo_axis_tdata <= random_data;
                end else if(rx_constante)begin
						  tx_fifo_axis_tdata <= tx_axis_tdata_test;
					 end else begin
                    tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg;
                    tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 8'd1;
                end
                cont_reg <= cont_reg + 1;
            end

        end 
        // Estado 2: Enviando segunda palabra y el resto
        else if (state == 3'd2) begin
        
            if (tx_fifo_axis_tready) begin
                cont_reg <= cont_reg + 1;
                if (cont_reg == (n_bytes - 2)) begin // si se llego a la penultima palabra elegir el ultimo dato y enviarlo en el estado 3
                    state <= 3'd3;
                    tx_fifo_axis_tlast <= 1;
						  
						  if(flood) begin
								pkt_n_reg <= pkt_n; // si se esta en flood igualar a pkt_n para que cuando se desacative flood se dejen de enviar paketes en el siguient estado
						  end else begin
								pkt_n_reg <= pkt_n_reg + 1; // contar numero de paquete si no se esta en flood
						  end
                    
						  if(rx_random) begin
								tx_fifo_axis_tdata <= random_data;
						  end else if(rx_constante)begin
								tx_fifo_axis_tdata <= tx_axis_tdata_test;
						  end else begin
								tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg;
								tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 8'd1;
						  end
					 // si no se ha lleado elegir la siguiente palabra del paquete y no salir del estado 2
                end else if(rx_random) begin
                    tx_fifo_axis_tdata <= random_data;
                end else if(rx_constante)begin
						  tx_fifo_axis_tdata <= tx_axis_tdata_test;
					 end else begin
                    tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg;
                    tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 8'd1;
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
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg;
							tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 8'd1;
					 end
				end else if (pkt_n_reg >= pkt_n) begin // si se llego a la ultimo paquete bajar valid y regresar a estado 0
                cont_reg <= 0;
                pkt_n_reg <= 0;
                ocupado <= 0; //fin ocupado para volver a estado 0 y esperar otro triger
                state <= 3'd0; //volver a estado 0
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
							tx_fifo_axis_tdata <= tx_fifo_axis_tdata_reg;
							tx_fifo_axis_tdata_reg <= tx_fifo_axis_tdata_reg + 8'd1;
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

// Loop back UDP
wire match_cond = rx_udp_dest_port == 1234; // solo se escucha el puerto 1234 en el loopback
wire no_match = !match_cond;

reg match_cond_reg = 0;
reg no_match_reg = 0;

always @(posedge clk) begin
    if (rst) begin
        match_cond_reg <= 0;
        no_match_reg <= 0;
    end else begin
        if (rx_udp_payload_axis_tvalid) begin
            if ((!match_cond_reg && !no_match_reg) ||
                (rx_udp_payload_axis_tvalid && rx_udp_payload_axis_tready && rx_udp_payload_axis_tlast)) begin
                match_cond_reg <= match_cond;
                no_match_reg <= no_match;
            end
        end else begin
				match_cond_reg <= 0;
            no_match_reg <= 0;
        end
    end
end

assign tx_udp_hdr_valid = rx_loopb ? (rx_udp_hdr_valid & match_cond) : (tx_udp_payload_axis_tvalid && tx_udp_hdr_ready);
assign rx_udp_hdr_ready = rx_loopb ? ((tx_udp_hdr_ready & match_cond) | no_match) : (match_cond | no_match);

//assign tx_udp_hdr_valid = rx_udp_hdr_valid && match_cond;
//assign rx_udp_hdr_ready = (tx_eth_hdr_ready && match_cond) || no_match;

assign tx_udp_ip_dscp = 0;
assign tx_udp_ip_ecn = 0;
assign tx_udp_ip_ttl = 64;
assign tx_udp_ip_source_ip = local_ip;

assign tx_udp_ip_dest_ip = rx_loopb ? rx_udp_ip_source_ip : tx_udp_ip_dest_ip_reg;
assign tx_udp_source_port = rx_loopb ? rx_udp_dest_port : tx_udp_source_port_reg;
assign tx_udp_dest_port = rx_loopb ? rx_udp_source_port : tx_udp_dest_port_reg;

//assign tx_udp_ip_dest_ip = rx_udp_ip_source_ip;
//assign tx_udp_source_port = rx_udp_dest_port;
//assign tx_udp_dest_port = rx_udp_source_port;

assign tx_udp_length = rx_loopb ? rx_udp_length : (n_bytes + 16'd8);
assign tx_udp_checksum = 0;

assign tx_udp_payload_axis_tdata = rx_loopb ? reg_fifo_udp_payload_axis_tdata : tx_fifo_axis_tdata;
assign tx_udp_payload_axis_tvalid = rx_loopb ? reg_fifo_udp_payload_axis_tvalid : tx_fifo_axis_tvalid;
assign tx_fifo_axis_tready = tx_udp_payload_axis_tready;
assign reg_fifo_udp_payload_axis_tready = rx_loopb ? tx_udp_payload_axis_tready : 1'b1;
assign tx_udp_payload_axis_tlast = rx_loopb ? reg_fifo_udp_payload_axis_tlast : tx_fifo_axis_tlast;
assign tx_udp_payload_axis_tuser = rx_loopb ? reg_fifo_udp_payload_axis_tuser : tx_fifo_axis_tuser;

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
    .TX_FIFO_DEPTH(8192),
    .TX_FRAME_FIFO(1),
    .RX_FIFO_DEPTH(8192),
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
    
    .tx_fifo_overflow(),
    .tx_fifo_bad_frame(),
    .tx_fifo_good_frame(),
    .rx_error_bad_frame(),
    .rx_error_bad_fcs(),
    .rx_fifo_overflow(),
    .rx_fifo_bad_frame(),
    .rx_fifo_good_frame(),
    .speed(),

    .cfg_ifg(8'd12),
    .cfg_tx_enable(1'b1),
    .cfg_rx_enable(1'b1)
);

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
    .error_header_early_termination()
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
    .ip_rx_error_header_early_termination(),
    .ip_rx_error_payload_early_termination(),
    .ip_rx_error_invalid_header(),
    .ip_rx_error_invalid_checksum(),
    .ip_tx_error_payload_early_termination(),
    .ip_tx_error_arp_failed(),
    .udp_rx_error_header_early_termination(),
    .udp_rx_error_payload_early_termination(),
    .udp_tx_error_payload_early_termination(),
    // Configuration
    .local_mac(local_mac),
    .local_ip(local_ip),
    .gateway_ip(gateway_ip),
    .subnet_mask(subnet_mask),
    .clear_arp_cache(0)
	 
);

axis_fifo #(
    .DEPTH(8192),
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
assign led[4] = rx_loopb && sw[4]; //decarctivar indicador con sw
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

//buffer 8 bytes------------------------
reg [63:0] rx_uart_buff;
reg [3:0] nbyte_buff;
always @(posedge clk) begin
    if (rst) begin
        rx_uart_buff <= 64'd0;
		  nbyte_buff <= 4'd0;
    end else begin
			//esperando valid registrar hasta 8BYtes y borrar
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

////////////////////////////////////////////////////////////
reg flood;
reg rx_loopb;
reg rx_trigger;
reg rx_random;
reg rx_constante;

reg mdio_op;
reg [4:0] mdio_phy;
reg [4:0] mdio_reg;
reg [15:0] mdio_wdata;
reg mdio_start;

reg [15:0] n_bytes; 
reg [31:0] off_cycles; 
reg [31:0] pkt_n;


// Configuration
wire [47:0] local_mac = 48'h02_00_00_00_00_00; //direccion fisica de la fpga

reg [31:0] local_ip;
reg [31:0] gateway_ip;
reg [31:0] subnet_mask;

reg [31:0] tx_udp_ip_dest_ip_reg;
reg [15:0] tx_udp_source_port_reg;
reg [15:0] tx_udp_dest_port_reg;

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
		  off_cycles <= 32'd1; // 1 por defecto ~8ns (caracteristica desactivada ya no jau offcycles)
		  pkt_n <= 32'd1;//por defecto 1 mensaje
		  
		  gateway_ip  <= {8'd192, 8'd168, 8'd1,   8'd1};
		  local_ip    <= {8'd192, 8'd168, 8'd1,   8'd12};
		  tx_udp_ip_dest_ip_reg <= {8'd192, 8'd168, 8'd1,   8'd11};
		  
        subnet_mask <= {8'd255, 8'd255, 8'd255, 8'd0};
        tx_udp_source_port_reg <= 16'd1234; //puerto por defecto para envio, source, desde la fpga
        tx_udp_dest_port_reg <= 16'd9999; //puerto por defecto para envio, destination hacia la pc
		  
    end else begin
			//UDP CONTROL/////////////////////////////
        if (rx_uart_buff == 64'h2e2e2e666c6f6f64) begin //"...flood"
				flood <= ~flood;
        end else if (rx_uart_buff == 64'h6c6f6f706261636b) begin //"loopback"
				rx_loopb <= ~rx_loopb;
		  end else if (rx_uart_buff == 64'h2e74726967676572) begin //".trigger"
				rx_trigger <= 1;
		  end else if (rx_uart_buff == 64'h2e2e72616e646f6d) begin //"..random"
				rx_random <= ~rx_random;
		  end else if (rx_uart_buff == 64'h636f6e7374616e74) begin //"constant"
				rx_constante <= ~rx_constante;
				// PHY CONTROLLER/*------------------*//
		  end else if (rx_uart_buff == 64'h2e2e6d64696f5f72) begin //"..mdio_r"
				mdio_op <= 1;
		  end else if (rx_uart_buff == 64'h2e2e6d64696f5f77) begin //"..mdio_w"
				mdio_op <= 0;
		  end else if (rx_uart_buff[63:8] == 56'h70687961646472) begin //"phyaddr"8'bXXXAAAAA
				mdio_phy <= rx_uart_buff[4:0];
		  end else if (rx_uart_buff[63:8] == 56'h72656761646472) begin //"regaddr"8'bXXXRRRRR
				mdio_reg <= rx_uart_buff[4:0];
		  end else if (rx_uart_buff[63:16] == 48'h6d64696f5f64) begin //"mdio_d"16'hDDDD
				mdio_wdata <= rx_uart_buff[15:0];
		  end else if (rx_uart_buff == 64'h6d64696f5f737461) begin //"mdio_sta"
				mdio_start <= 1;
				// UDP Mesagge configurations/*------------------*/
		  end else if (rx_uart_buff[63:16] == 48'h7564706d7475) begin //"udpmtu"16'hBBBB
				n_bytes <= rx_uart_buff[15:0];
		  end else if (rx_uart_buff[63:32] == 32'h6f666663) begin //"offc"32'hOOOOOOOO
				off_cycles <= rx_uart_buff[31:0];
		  end else if (rx_uart_buff[63:32] == 32'h706b746e) begin //"pktn"32'hPPPPPPPP
				pkt_n <= rx_uart_buff[31:0];
		  // ip configuration/*------------------*
		  end else if (rx_uart_buff[63:32] == 32'h69705f67) begin //"ip_g"32'hIIIIIIII
		      gateway_ip <= rx_uart_buff[31:0];
		  end else if (rx_uart_buff[63:32] == 32'h69705f73) begin //"ip_s"32'hIIIIIIII
		      local_ip <= rx_uart_buff[31:0];
		  end else if (rx_uart_buff[63:32] == 32'h69705f64) begin //"ip_d"32'hIIIIIIII
		      tx_udp_ip_dest_ip_reg <= rx_uart_buff[31:0];
		  end else if (rx_uart_buff[63:32] == 32'h7375626d) begin //"subm"32'hMMMMMMMM
		      subnet_mask <= rx_uart_buff[31:0];
	     end else if (rx_uart_buff[63:16] == 48'h7372706f7274) begin //"srport"16'hPPPP
		      tx_udp_source_port_reg <= rx_uart_buff[15:0];
		  end else if (rx_uart_buff[63:16] == 48'h6473706f7274) begin //"dsport"16'hPPPP
		      tx_udp_dest_port_reg <= rx_uart_buff[15:0];
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
				off_cycles <= off_cycles;
				pkt_n <= pkt_n;
				
			  gateway_ip  <= gateway_ip;
			  local_ip    <= local_ip;
			  tx_udp_ip_dest_ip_reg <= tx_udp_ip_dest_ip_reg;
			  
			  subnet_mask <= subnet_mask;
			  tx_udp_source_port_reg <= tx_udp_source_port_reg;
			  tx_udp_dest_port_reg <= tx_udp_dest_port_reg;

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
reg [2:0] state_uart_tx = 2'd0;

always @(posedge clk) begin
    if (rst) begin
		  tx_ena <= 0;
		  tx_data <= 8'd0;
		  state_uart_tx <= 2'd0;
    end else begin
			//estado 0: esperando mdio_read_ready
        if (state_uart_tx == 2'd0) begin
				if (mdio_read_ready) begin
					tx_data <= mdio_rdata_reg[15:8];
					tx_ena <= 1;
					state_uart_tx <= 2'd1;
				end
        end
			//estado 1
		  else if (state_uart_tx == 2'd1) begin
				tx_ena <= 0;
				state_uart_tx <= 2'd2; // pasar a estado 2
        end 
		  //estado 2: esperando a que se envie primero 8 bits
		  else if (state_uart_tx == 2'd2) begin
				if (~tx_busy) begin
					tx_data <= mdio_rdata_reg[7:0];
					tx_ena <= 1;
					state_uart_tx <= 2'd3; // pasar a estado 3
				end
		  end
		  //estado 3: esperar a que se envie segunda palabra para volver a estado 0
		  else begin
				tx_ena <= 0; 
				if (~tx_busy) begin
				state_uart_tx <= 2'd0; // pasar a estado 0
				end
		  end
    end
end

endmodule
`resetall
