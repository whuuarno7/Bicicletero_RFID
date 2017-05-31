`timescale 1ns / 1ps

`define SIMULATION


module top_Teclado_TB;

   reg  clk;
   reg reset;
   reg entrada1;
   reg entrada2;
   reg entrada3;
   reg entrada4;
  
   
   
   wire done;

//(input clk, input int1, input int2, input int3, input int4, input resetg, input resetS, output led, input reset, input init, output, done) -> Son las entradas y salidas del topemision.v

   //mult_32 uut (.clk(clk) , .rst(rst) , .init(start) , .A(in_A) , .B(in_B) , .pp(pp) , .done(done));
	// topmod(clk, led, init, reset, done)
   wb_Teclado uut (.clk(clk), .reset(reset), .done(done), .entrada1(entrada1), .entrada2(entrada2), .entrada3(entrada3), .entrada4(entrada4) );

   parameter PERIOD          = 10;
   parameter real DUTY_CYCLE = 0.5;
   parameter OFFSET          = 0;
   reg [20:0] i=0;
   event reset_trigger;
    




   initial begin  // Initialize Inputs
      clk = 0; 
      reset = 0;
      entrada1 = 0;
      entrada2 = 0;
      entrada3 = 0;
      entrada4 = 0;
      
   end

   initial  begin  // Process for clk
     #OFFSET;
     forever
       begin
         clk = 1'b0;
         #(PERIOD-(PERIOD*DUTY_CYCLE)) clk = 1'b1;
         #(PERIOD*DUTY_CYCLE);
         i = i +10;
         if(i>100)
          entrada1=1;
         if(i>200)
          begin
           entrada1=0;
           entrada2=1;
          end
         if(i>300)
          begin
           entrada2=0;
           entrada3=1;
          end
         if(i>400)
          begin
           entrada3=0;
           entrada4=1;
          end
         if(i>500)
          begin
           entrada4=0;
           i = 0;
          end
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
     $dumpfile("top_Teclado_TB.vcd");
     $dumpvars(-1, uut);
	
     #10 -> reset_trigger;
     #((PERIOD*DUTY_CYCLE)*9000000) $finish;
   end

endmodule

