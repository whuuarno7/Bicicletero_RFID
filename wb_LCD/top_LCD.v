`timescale 1ns / 100ps

module top_LCD(input clk, input init, input reset, input [5:0] numeroInstrucciones, input [10:0] instruccion0, input [10:0] instruccion1, input [10:0] instruccion2, input [10:0] instruccion3, input [10:0] instruccion4, input [10:0] instruccion5, input [10:0] instruccion6,  input [10:0] instruccion7, input [10:0] instruccion8, input [10:0] instruccion9, input [10:0] instruccion10, input [10:0] instruccion11, input [10:0] instruccion12, input [10:0] instruccion13, input [10:0] instruccion14, input [10:0] instruccion15, input [10:0] instruccion16, input [10:0] instruccion17, input [10:0] instruccion18, input [10:0] instruccion19,input [10:0] instruccion20, input [10:0] instruccion21, input [10:0] instruccion22, input [10:0] instruccion23, input [10:0] instruccion24, input [10:0] instruccion25, input [10:0] instruccion26,  input [10:0] instruccion27, input [10:0] instruccion28, input [10:0] instruccion29,input [10:0] instruccion30, input [10:0] instruccion31, input [10:0] instruccion32, input [10:0] instruccion33, input [10:0] instruccion34, input [10:0] instruccion35, input [10:0] instruccion36,  input [10:0] instruccion37, input [10:0] instruccion38, input [10:0] instruccion39, output DONE, output [10:0] salida);

	 wire C1,C2,C3,C4,C5;
	 wire ADD1, ADD2, LOAD1, LOAD2, LOAD3, LOAD4, RESET1, RESET2;
	
	 
	datapath_LCD datapath_LCD(clk, ADD1, ADD2, LOAD1, LOAD2, LOAD3, LOAD4, RESET1, RESET2, DONE, numeroInstrucciones, instruccion0, instruccion1, instruccion2, instruccion3, instruccion4, instruccion5, instruccion6, instruccion7, instruccion8, instruccion9,instruccion10, instruccion11, instruccion12, instruccion13, instruccion14, instruccion15, instruccion16, instruccion17, instruccion18,instruccion19, instruccion20, instruccion21, instruccion22, instruccion23, instruccion24, instruccion25, instruccion26, instruccion27,instruccion28,instruccion29, instruccion30, instruccion31, instruccion32, instruccion33, instruccion34, instruccion35, instruccion36, instruccion37,instruccion38,instruccion39, salida, C1, C2, C3, C4, C5);

        fsm_LCD fsm(clk, init, reset, C1, C2, C3, C4, C5, ADD1, ADD2, LOAD1, LOAD2, LOAD3, LOAD4, RESET1, RESET2, DONE);




endmodule
