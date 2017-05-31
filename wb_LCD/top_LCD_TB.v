`timescale 1ns / 100ps

`define SIMULATION


module top_LCD_TB;

   reg  clk;
   reg start;
   reg reset;
   reg [10:0]  instruccion0=11'b00000001100;
   reg [10:0]  instruccion1=11'b00000010100;
   reg [10:0]  instruccion2=11'b00001111100;
   reg [10:0]  instruccion3=11'b01000011101;
   reg [10:0]  instruccion4=11'b01010010101;
   reg [10:0]  instruccion5=11'b01001001101;
   reg [10:0]  instruccion6=11'b01010011101;
   reg [10:0]  instruccion7=11'b01010100101;
   reg [10:0]  instruccion8=11'b01001001101;
   reg [10:0]  instruccion9=11'b01000001101;
   wire DONE;
   wire [10:0] salida;
   
   
   
   wire done;

//(input clk, input int1, input int2, input int3, input int4, input resetg, input resetS, output led, input reset, input init, output, done) -> Son las entradas y salidas del topemision.v

   //mult_32 uut (.clk(clk) , .rst(rst) , .init(start) , .A(in_A) , .B(in_B) , .pp(pp) , .done(done));
	// topmod(clk, led, init, reset, done)
   top_LCD uut (.clk(clk), .init(start), .reset(reset), .instruccion0(instruccion0), .instruccion1(instruccion1), .instruccion2(instruccion2), .instruccion3(instruccion3), .instruccion4(instruccion4), .instruccion5(instruccion5), .instruccion6(instruccion6), .instruccion7(instruccion7), .instruccion8(instruccion8), .instruccion9(instruccion9), .DONE(DONE), .salida(salida));

   parameter PERIOD          = 10;
   parameter real DUTY_CYCLE = 0.5;
   parameter OFFSET          = 0;
   reg [20:0] i;
   event reset_trigger;




   initial begin  // Initialize Inputs
      clk = 0; reset = 0; start = 1;
      //int1=1;
      //int2=1;
      //int3=1;
      //int4=1;
   end

   initial  begin  // Process for clk
     #OFFSET;
     forever
       begin
         clk = 1'b0;
         #(PERIOD-(PERIOD*DUTY_CYCLE)) clk = 1'b1;
         #(PERIOD*DUTY_CYCLE);
       end
   end

/*
   initial begin // Reset the system, Start the image capture process
      forever begin 
        @ (reset_trigger);
        @ (posedge clk);
        start = 0;
        @ (posedge clk);
        start = 1;

       for(i=0; i<2; i=i+1) begin
         @ (posedge clk);
       end
          start = 0;
      end
   end
*/	 

   initial begin: TEST_CASE
     $dumpfile("top_LCD_TB.vcd");
     $dumpvars(-1, uut);
	
     #10 -> reset_trigger;
     #((PERIOD*DUTY_CYCLE)*9000000) $finish;
   end

endmodule

