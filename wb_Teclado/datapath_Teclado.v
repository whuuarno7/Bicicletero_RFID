`timescale 1ns / 1ps

module datapath_Teclado (clk, load1, load2, load3, load4, rtecla, teclaoprimida);
	input clk;
	input load1;
	input load2;
	input load3;
	input load4;
	input rtecla;
	output reg [2:0]  teclaoprimida=0;



always @(negedge clk)
	begin
	
	 if(load1)
	  teclaoprimida=1;
	 if(load2)
	  teclaoprimida=2;
	 if(load3)
	  teclaoprimida=3;
	 if(load4)
	  teclaoprimida=4;
	 if(rtecla)
	  teclaoprimida=0;
	end

endmodule	
