/*
 *
 * Este teclado is very heavy :v
 */ 

module wb_Teclado(
	   input clk,
	   input reset,
	    
	   input [31:0] wb_adr_i,
	   input [31:0] wb_dat_i,
	   input wb_we_i,
	   input wb_cyc_i,
	   input wb_stb_i,
	    
	   output wb_ack_o,
	   output reg [31:0] wb_dat_o,
	   input entrada1,
	   input entrada2,
	   input entrada3,
	   input entrada4,
	   output [2:0] teclasalida
	);


//Teclado

wire [2:0] teclaoprimida;
wire done;
top_Teclado
Teclado0 (
	.clk(       clk      ),
	.reset(     reset    ),
	//
	.entrada1(  entrada1 ),
	.entrada2(  entrada2 ),
	.entrada3(  entrada3 ),
	.entrada4(  entrada4 ),
	.teclaoprimida( teclaoprimida ),
	.done ( done)
	
);

assign teclasalida=teclaoprimida;

//Wisbone logical Interface

   


   wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
   wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

   reg  ack;
   assign wb_ack_o = wb_stb_i & wb_cyc_i & ack;
    
 
   always @(posedge clk)begin
     if (reset)begin
        wb_dat_o[31:0] <= 0; // All set to in at reset
        ack <= 0;
     end
     else begin 
        ack<=0;
        if (wb_rd & ~ack) begin             //Read cycle
         ack<=1;
         case(wb_adr_i[3:2])
          2'b00:begin  
            wb_dat_o[31:4]<=0;
            wb_dat_o[3:0] <= teclaoprimida;
          end
          default: wb_dat_o <= 32'b0; 
         endcase
        end
     end        
   end   
  
endmodule 
        

















