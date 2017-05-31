`timescale 1ns / 1ps


module datapath_SPI(clk, work, rstSCK, initRd, initWr, rstRd, rstWr, address, dataWr, dataRd, doneRd, doneWr, SCKclock, MOSI, MISO, NSS, A, activeNSS, Z3);
	 
input	clk;
input	work;
input	rstSCK;
input	initRd;
input	initWr;
input	rstRd;
input	rstWr;
input[7:0]	address;
input[7:0]	dataWr;
output[7:0]	dataRd;
output doneRd;
output doneWr;
output SCKclock;
output MOSI;
input  MISO;
output reg NSS;
input[1:0] A;
input activeNSS;
output reg Z3;

wire SCKclock;
reg[7:0] reg_dataWr = 0; //reg temporal, entra a MOSI para ser enviado (puedeser una direción, un dato o un 0x00)

byteMISO IN(SCKclock, initRd, rstRd, MISO, dataRd, doneRd);
byteMOSI OUT(SCKclock, initWr, rstWr, reg_dataWr, MOSI, doneWr);
SCK generador(clk, work, rstSCK, SCKclock);



always @(negedge clk)
begin
	
	if(address[7] == 1)
		Z3 = 1;
	else
		Z3 = 0;
	
	case(A)
	2'b00:reg_dataWr=address;
	2'b01:reg_dataWr=8'h00;
	2'b10:reg_dataWr=dataWr;
	2'b11:reg_dataWr=reg_dataWr;
	default: reg_dataWr=reg_dataWr;
	endcase
	
	if(activeNSS == 1)
		NSS = 1;
	else
		NSS = 0;
		
end

endmodule
