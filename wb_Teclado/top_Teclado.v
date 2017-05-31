`timescale 1ns / 1ps

module top_Teclado(input clk, input reset, input entrada1, input entrada2, input entrada3, input entrada4, output  [2:0] teclaoprimida, output done);


	wire load1, load2, load3, load4, rtecla;
      
	

	datapath_Teclado datapath (clk, load1, load2, load3, load4, rtecla, teclaoprimida);

        fsm_Teclado fsm (clk, reset, entrada1, entrada2, entrada3, entrada4, load1, load2, load3, load4, rtecla, done);




endmodule
