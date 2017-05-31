module wb_LCD(
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
	// lcd 
	output  [10:0]   salida

);

// lcd engine
reg init;
reg[5:0]  numeroInstrucciones;
reg[10:0] instruccion0;
reg[10:0] instruccion1;
reg[10:0] instruccion2;
reg[10:0] instruccion3;
reg[10:0] instruccion4;
reg[10:0] instruccion5;
reg[10:0] instruccion6;
reg[10:0] instruccion7;
reg[10:0] instruccion8;
reg[10:0] instruccion9;
reg[10:0] instruccion10;
reg[10:0] instruccion11;
reg[10:0] instruccion12;
reg[10:0] instruccion13;
reg[10:0] instruccion14;
reg[10:0] instruccion15;
reg[10:0] instruccion16;
reg[10:0] instruccion17;
reg[10:0] instruccion18;
reg[10:0] instruccion19;
reg[10:0] instruccion20;
reg[10:0] instruccion21;
reg[10:0] instruccion22;
reg[10:0] instruccion23;
reg[10:0] instruccion24;
reg[10:0] instruccion25;
reg[10:0] instruccion26;
reg[10:0] instruccion27;
reg[10:0] instruccion28;
reg[10:0] instruccion29;
reg[10:0] instruccion30;
reg[10:0] instruccion31;
reg[10:0] instruccion32;
reg[10:0] instruccion33;
reg[10:0] instruccion34;
reg[10:0] instruccion35;
reg[10:0] instruccion36;
reg[10:0] instruccion37;
reg[10:0] instruccion38;
reg[10:0] instruccion39;
wire DONE;
//wire RESET2;

top_LCD LCDcore(
	.clk(clk),			//input
	.init(init),			//input 
	.reset(reset),		//input
	.numeroInstrucciones(numeroInstrucciones),
	.instruccion0(instruccion0),
	.instruccion1(instruccion1),
	.instruccion2(instruccion2),
	.instruccion3(instruccion3),
	.instruccion4(instruccion4),
	.instruccion5(instruccion5),
	.instruccion6(instruccion6),
	.instruccion7(instruccion7),
	.instruccion8(instruccion8),
	.instruccion9(instruccion9),
	.instruccion10(instruccion10),
	.instruccion11(instruccion11),
	.instruccion12(instruccion12),
	.instruccion13(instruccion13),
	.instruccion14(instruccion14),
	.instruccion15(instruccion15),
	.instruccion16(instruccion16),
	.instruccion17(instruccion17),
	.instruccion18(instruccion18),
	.instruccion19(instruccion19),
	.instruccion20(instruccion20),
	.instruccion21(instruccion21),
	.instruccion22(instruccion22),
	.instruccion23(instruccion23),
	.instruccion24(instruccion24),
	.instruccion25(instruccion25),
	.instruccion26(instruccion26),
	.instruccion27(instruccion27),
	.instruccion28(instruccion28),
	.instruccion29(instruccion29),
        .instruccion30(instruccion30),
	.instruccion31(instruccion31),
	.instruccion32(instruccion32),
	.instruccion33(instruccion33),
	.instruccion34(instruccion34),
	.instruccion35(instruccion35),
	.instruccion36(instruccion36),
	.instruccion37(instruccion37),
	.instruccion38(instruccion38),
	.instruccion39(instruccion39),
        .DONE(DONE),
	.salida(salida)
	//.RESET2(RESET2)
);

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------




wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

reg  ack;
assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;

   always @(posedge clk)begin
     if (reset)begin
        init <= 0; // All set to in at reset
       //init <= 0;
       // salida[10:0] <= 11'b00000000000;
	//salida = 11'b00000000000;
        ack <= 0;
     end
     else begin 
        ack<=0;
       

         if (wb_wr & ~ack) begin  
            ack <= 1;    
            if(DONE)    
             begin                    //Write cycle
           case(wb_adr_i[6:1]) 
                
		6'd0: init   <= wb_dat_i[10:0];
		6'd1: numeroInstrucciones   <= wb_dat_i[10:0]; 
		6'd2: instruccion0   <= wb_dat_i[10:0]; 
		6'd3: instruccion1   <= wb_dat_i[10:0]; 
		6'd4: instruccion2   <= wb_dat_i[10:0]; 
		6'd5: instruccion3   <= wb_dat_i[10:0]; 
		6'd6: instruccion4   <= wb_dat_i[10:0]; 
		6'd7: instruccion5   <= wb_dat_i[10:0]; 
		6'd8: instruccion6   <= wb_dat_i[10:0]; 
		6'd9: instruccion7   <= wb_dat_i[10:0];
		6'd10: instruccion8   <= wb_dat_i[10:0];
		6'd11: instruccion9   <= wb_dat_i[10:0];
		6'd12: instruccion10   <= wb_dat_i[10:0];
		6'd13: instruccion11   <= wb_dat_i[10:0];
		6'd14: instruccion12   <= wb_dat_i[10:0];
		6'd15: instruccion13   <= wb_dat_i[10:0];
		6'd16: instruccion14   <= wb_dat_i[10:0];
		6'd17: instruccion15   <= wb_dat_i[10:0];
		6'd18: instruccion16   <= wb_dat_i[10:0];
		6'd19: instruccion17   <= wb_dat_i[10:0];
		6'd20: instruccion18   <= wb_dat_i[10:0];
		6'd21: instruccion19   <= wb_dat_i[10:0];
		6'd22: instruccion20   <= wb_dat_i[10:0];
		6'd23: instruccion21   <= wb_dat_i[10:0];
		6'd24: instruccion22   <= wb_dat_i[10:0];
		6'd25: instruccion23   <= wb_dat_i[10:0];
		6'd26: instruccion24   <= wb_dat_i[10:0];
		6'd27: instruccion25   <= wb_dat_i[10:0];
		6'd28: instruccion26   <= wb_dat_i[10:0];
		6'd29: instruccion27   <= wb_dat_i[10:0];
		6'd30: instruccion28   <= wb_dat_i[10:0];
		6'd31: instruccion29   <= wb_dat_i[10:0];
		6'd32: instruccion30   <= wb_dat_i[10:0];
		6'd33: instruccion31   <= wb_dat_i[10:0];
		6'd34: instruccion32   <= wb_dat_i[10:0];
		6'd35: instruccion33   <= wb_dat_i[10:0];
		6'd36: instruccion34   <= wb_dat_i[10:0];
		6'd37: instruccion35   <= wb_dat_i[10:0];
		6'd38: instruccion36   <= wb_dat_i[10:0];
		6'd39: instruccion37   <= wb_dat_i[10:0];
		6'd40: instruccion38   <= wb_dat_i[10:0];
		6'd41: instruccion39   <= wb_dat_i[10:0];
		
		//default: instruccion0 <= 11'b0;
            endcase
            end
            else
            init <=0;
            
            
           
          end
          else
          init <= 0;
         
     end        
   end  

endmodule

	
	
	
