//-----------------------------------------------------------------
// SPI Master - MODE 0 - Enabling CS or NSS to 0 (choose a slave).
//--------------
module wb_SPI(
	input               clk,
	input               reset,
	// Wishbone bus
	input      [31:0]   wb_adr_i,
	input      [31:0]   wb_dat_i,
	output reg [31:0]   wb_dat_o,
	input      [ 3:0]   wb_sel_i,
	input               wb_cyc_i,
	input               wb_stb_i,
	output              wb_ack_o,
	input               wb_we_i,
	// SPI 
	output              spi_sck,
	output              spi_mosi,
	input               spi_miso,
	//output				  spi_cs
	output reg [2:0]	  CS
);

// SPI engine
reg init;
//reg rst;
reg[7:0] address;
reg[7:0] dataWr;
wire[7:0] dataRd;
reg[7:0] status = 8'h00; //bit 0 registra el estado de done (pero no es assign a wire done). si status[0] = 1, es porque aun o ha terminado la transmisión
reg[7:0] chipSelect = 8'h40; //permite seleccionar a cual RFID se va a escribir. Es la señal de control de un demultiplexor

wire spi_cs;
wire done;

topSPI SPIcore(
	.clk(clk),			//input
	.init(init),			//input 
	.reset(reset),		//input
	.address(address),		//input [7:0]
	.dataWr(dataWr), 		//input [7:0]
	.MISO(spi_miso), 		//input
	.SCKclock(spi_sck), 	//output
	.dataRd(dataRd),		//output [7:0]
	.MOSI(spi_mosi),			//output
	.NSS(spi_cs), 			//output
	.done(done)			//output
);




//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------




wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

always @(posedge clk)
begin
	if(reset)
	begin
		wb_dat_o[31:8] <= 24'b0;
		init <= 0;
		//rst <= 1;
		ack <= 0;
	end
	else
	begin
		wb_dat_o[31:8] <= 24'b0;
		ack <= 0;
		if(done == 1) //podria ser reemplazable con un assign done
		begin
			status <= 8'h00;
			init <= 0;
		end
		else
		begin
			status <= 8'h01;
		end
			
		//posible terminación, mejor dicho, init<-0
		//if(~done) --> meter los dos if(wb_rd y wr). else, init<-0
		if(wb_rd & ~ack)		//Read cycle
		begin
			ack <= 1;
			case(wb_adr_i[4:2])
				3'b000:begin
					wb_dat_o[31:8] <= 24'b0;
					wb_dat_o[7:0] <= dataRd;
					//init <= 1; //No es necesario acá, el periferico no inicia cuando uno hace operaciones de lectura
					//status <= 8'h00;idem - el periferico no cambia su estado - idem
				end
				3'b011: wb_dat_o[7:0] <= status;
				default: begin
					wb_dat_o <= 32'b0;
					//init <= 0; idem otro case
				end
			endcase
		end
		else 
		begin 
			if(wb_wr & ~ack)	//Write cycle
			begin
				ack <= 1;
				case(wb_adr_i[4:2])
					3'b001: begin
						address <= wb_dat_i[7:0];
						if(wb_dat_i[7] == 1'b1)		//permite evaluar si es read or write stream. De esta manera, le dice al SPI que comience
							init <= 1;					//a transmitir solo con la dirección (leer) o sino, se coloca el dato a escribir y se da init
					end
					3'b010: begin
						dataWr <= wb_dat_i[7:0];
						init <= 1; //status <= 8'h00;
					end
					3'b100: chipSelect <= wb_dat_i[7:0];
					default:begin
						address <= 8'b0;
						dataWr <= 8'b0;
						//init <= 0;
					end
				endcase
			end
		end
	end
	
end

always @(*)	//Demultiplexor para escoger el RFID
begin
	case(chipSelect)
		8'b00:begin
		CS[0] = spi_cs;
		CS[1] = 1'b1;
		CS[2] = 1'b1;
		end
		8'b01:begin
		CS[0] = 1'b1;
		CS[1] = spi_cs;
		CS[2] = 1'b1;
		end
		8'b10:begin
		CS[0] = 1'b1;
		CS[1] = 1'b1;
		CS[2] = spi_cs;
		end
		//default: CS = 8'b111;
	endcase
end

endmodule

	
	
	
